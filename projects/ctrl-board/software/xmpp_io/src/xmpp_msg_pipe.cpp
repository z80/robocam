
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
};

QXmppMsgPipe::QXmppMsgPipe( QXmppClient * client, int id )
: QObject( client )
{
    pd = new PD();
    pd->client     = client;
    pd->id         = id;
    pd->localPort  = -1;
    pd->remotePort = -1;
    pd->remoteHost = "";
    pd->serv       = 0;
    pd->sock       = 0;

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

void QXmppMsgPipe::qxmppMessageReceived( const QXmppMessage & msg )
{
    pd->data64   = msg.body().toUtf8();
    pd->data     = QByteArray::fromBase64( pd->data64 );

    QDomDocument doc( pd->data );
    QDomElement  root = doc.documentElement();
    if ( root.isNull() )
        return;
    if ( root.tagName() == "config" )
    {
        int id = root.attribute( "ind", "-1" ).toInt();
        if ( id != pd->id )
            return;
        pd->remotePort = root.attribute( "port", "1234" ).toInt();
        pd->remoteHost = root.attribute( "host", "localhost" );
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
            pd->data64 = root.text().toUtf8();
            pd->data   = QByteArray::fromBase64( pd->data64 );

            pd->sock->write( pd->data );
        }
    }

    //sendPacket(QXmppMessage("", from, "Your message: " + msg));
}

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
        stream.writeStartDocument();
        stream.writeStartElement( "config" );
        stream.writeAttribute( "ind", QString( "%1" ).arg( pd->id ) );
        stream.writeAttribute( "port", QString( "%1" ).arg( pd->remotePort ) );
        stream.writeAttribute( "host", QString( "%1" ).arg( pd->remoteHost ) );
        stream.writeEndElement();
        stream.writeEndDocument();

        pd->data64 = pd->data.toBase64();

        pd->client->sendMessage( pd->jidDest, pd->data64 );
    }
}

void QXmppMsgPipe::socketReadyRead()
{
    if ( !pd->sock )
        return;
    pd->data = pd->sock->readAll();
    pd->data64 = pd->data.toBase64();

    pd->data.clear();
    QXmlStreamWriter stream( &pd->data );
    stream.setAutoFormatting( false );
    stream.writeStartDocument();
    stream.writeStartElement( "data" );
    stream.writeAttribute( "ind", QString( "%1" ).arg( pd->id ) );
    stream.writeCharacters( pd->data64 );
    stream.writeEndDocument();

    pd->data64 = pd->data.toBase64();
    pd->client->sendMessage( pd->jidDest, pd->data64 );

    //qDebug() << "#####################>" << pd->stri;
}


