
#include <QtNetwork>
#include <QtXml>
#include "xmpp_msg_pipe.h"

class QXmppMsgPipe::PD
{
public:
    PD() {}
    ~PD() {}

    QXmppClient * client;
    QString jidDest;
    bool outgoing;
    int id;
    int localPort,
        remotePort;
    QString remoteHost;
    QTcpServer * serv;
    QTcpSocket * sock;
    QByteArray   data64;
    QByteArray   data;
    QByteArray   dataToWrite;
    QByteArray   dataToRead;
    int          maxPacketSize;
    int          messageDelay;
};

QXmppMsgPipe::QXmppMsgPipe( QXmppClient * client, int id )
: QObject( client )
{
    pd = new PD();
    pd->client     = client;
    pd->id         = id;
    pd->localPort  = 1234;
    pd->remotePort = 22;
    pd->remoteHost = "localhost";
    pd->serv       = 0;
    pd->sock       = 0;
    pd->maxPacketSize = 1024;
    pd->messageDelay  = 0;

    connect( client, SIGNAL(messageReceived(QXmppMessage)),
             this,     SLOT(qxmppMessageReceived(QXmppMessage)));
}

QXmppMsgPipe::~QXmppMsgPipe()
{
    delete pd;
}

void QXmppMsgPipe::setInPipe( int id )
{
    pd->outgoing = false;
    if ( id >= 0 )
        pd->id = id;
    clearPipe();
}

void QXmppMsgPipe::setOutPipe( const QString & jidDest, int localPort, int remotePort, const QString & remoteHost, int id )
{
    pd->jidDest = jidDest;
    pd->outgoing = true;
    if ( id >= 0 )
        pd->id = id;
    clearPipe();

    QTcpServer * serv = new QTcpServer( this );
    connect( serv, SIGNAL(newConnection()), this, SLOT(serverNewConnection()) );
    serv->listen( QHostAddress::Any, localPort );
    pd->serv = serv;
    pd->remotePort = remotePort;
    pd->remoteHost = remoteHost;
}

void QXmppMsgPipe::clearPipe()
{
    if ( pd->sock )
        pd->sock->deleteLater();
    if ( pd->serv )
        pd->serv->deleteLater();
    pd->sock = 0;
    pd->serv = 0;
}

void QXmppMsgPipe::setMaxPacketSize( int sz )
{
    pd->maxPacketSize = sz;
    if ( pd->maxPacketSize < 0 )
        pd->maxPacketSize = 1;
}

void QXmppMsgPipe::setMessageDelay( int ms )
{
    pd->messageDelay = ms;
}

void QXmppMsgPipe::qxmppMessageReceived( const QXmppMessage & msg )
{
    pd->data64   = msg.body().toAscii();
    pd->data     = QByteArray::fromBase64( pd->data64 );

    QDomDocument doc;
    QString errorMsg;
    bool res = doc.setContent( pd->data, &errorMsg );
    if ( !res )
        return;
    QDomElement  root = doc.documentElement();
    if ( root.tagName() == "config" )
    {
        int id = root.attribute( "ind", "-1" ).toInt();
        if ( id != pd->id )
            return;
        pd->remotePort    = root.attribute( "port", "1234" ).toInt();
        pd->remoteHost    = root.attribute( "host", "localhost" );
        pd->maxPacketSize = root.attribute( "packet", QString( "%1" ).arg( pd->maxPacketSize ) ).toInt();
        pd->messageDelay  = root.attribute( "delay",  QString( "%1" ).arg( pd->messageDelay ) ).toInt();
        pd->jidDest    = msg.from();

        clearPipe();
        QTcpSocket * sock = new QTcpSocket( this );
        connect( sock, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
        sock->connectToHost( pd->remoteHost, pd->remotePort );
        sock->waitForConnected();
        pd->sock = sock;
    }
    else if ( root.tagName() == "data" )
    {
        int id = root.attribute( "ind", "-1" ).toInt();
        if ( id != pd->id )
            return;
        if ( pd->sock )
        {
            bool doWrite = ( root.attribute( "wr", "-1" ).toInt() > 0 );
            pd->data64 = root.text().toUtf8();
            pd->dataToRead.append( pd->data64 );
            if ( doWrite )
            {
                pd->data = QByteArray::fromBase64( pd->dataToRead );

                qDebug() << "#####################<<<" << pd->data;

                pd->sock->write( pd->data );
                pd->dataToRead.clear();
            }
        }
    }
}

class Sleep: public QThread
{
public:
    static void msleep( int ms )
    {
        QThread::msleep( ms );
    }
};

void QXmppMsgPipe::serverNewConnection()
{
    if ( !pd->serv )
        return;
    QTcpSocket * sock = pd->serv->nextPendingConnection();
    if ( pd->sock )
        pd->sock->deleteLater();
    connect( sock, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
    pd->sock = sock;

    // On local new connection there should be new connection on other side
    // in the case of outgoing pipe direction.
    if ( pd->outgoing )
    {
        pd->data.clear();
        QXmlStreamWriter stream( &pd->data );
        stream.setAutoFormatting( false );

        stream.writeStartElement( "config" );
        stream.writeAttribute( "ind",    QString( "%1" ).arg( pd->id ) );
        stream.writeAttribute( "port",   QString( "%1" ).arg( pd->remotePort ) );
        stream.writeAttribute( "host",   QString( "%1" ).arg( pd->remoteHost ) );
        stream.writeAttribute( "packet", QString( "%1" ).arg( pd->maxPacketSize ) );
        stream.writeAttribute( "delay",  QString( "%1" ).arg( pd->messageDelay ) );
        stream.writeEndElement();

        pd->data64 = pd->data.toBase64();

        pd->client->sendMessage( pd->jidDest, pd->data64 );
        Sleep::msleep( pd->messageDelay );
    }
}

void QXmppMsgPipe::socketReadyRead()
{
    if ( !pd->sock )
        return;
    pd->dataToWrite = pd->sock->readAll();

    qDebug() << "#####################>>> " << pd->dataToWrite;

    pd->data64 = pd->dataToWrite.toBase64();
    pd->dataToWrite = pd->data64;

    for ( int i=0; i<pd->dataToWrite.size(); i+=pd->maxPacketSize )
    {
        pd->data.clear();
        QXmlStreamWriter stream( &pd->data );
        stream.setAutoFormatting( false );

        stream.writeStartElement( "data" );
        stream.writeAttribute( "ind", QString( "%1" ).arg( pd->id ) );
        if ( pd->dataToWrite.size() - i > pd->maxPacketSize )
            stream.writeAttribute( "wr", QString( "%1" ).arg( -1 ) );
        else
            stream.writeAttribute( "wr", QString( "%1" ).arg( 1 ) );
        pd->data64 = pd->dataToWrite.mid( i, pd->maxPacketSize );
        stream.writeCharacters( pd->data64 );
        stream.writeEndElement();

        pd->data64 = pd->data.toBase64();
        pd->client->sendMessage( pd->jidDest, pd->data64 );

        // Delay between messages.
        /*QTime t;
        t.start();
        while ( t.elapsed() < pd->messageDelay )
            qApp->processEvents();*/
        Sleep::msleep( pd->messageDelay );
    }
    pd->dataToWrite.clear();
}


