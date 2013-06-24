
#include "QXmppClient.h"
#include "xmpp_packet_iq.h"
#include "xmpp_config_pipe_iq.h"
#include <QtNetwork>
#include <QtXml>

#include "xmpp_tcp_proxy.h"

class QXmppTcpProxy::PD
{
public:
    PD() {}
    ~PD() {}

    QString jidDest;
    bool outgoing;
    int id;
    int localPort,
        remotePort;
    QString remoteHost;
    QTcpServer * serv;
    QTcpSocket * sock;
    QByteArray   stri;
    QXmppPacketIq     packetIq;
    QXmppConfigPipeIq configIq;

    bool skipData;
};

QXmppTcpProxy::QXmppTcpProxy( int id )
    : QXmppClientExtension()
{
    pd = new PD();
    pd->id   = id;
    pd->localPort = 0;
    pd->remotePort = 0;
    pd->remoteHost = "localhost";
    pd->sock = 0;
    pd->serv = 0;
    pd->skipData = false;
}

QXmppTcpProxy::~QXmppTcpProxy()
{
    delete pd;
}

void QXmppTcpProxy::setInPipe( int id )
{
    pd->outgoing = false;
    if ( id >= 0 )
        pd->id = id;
    clearPipe();
}

void QXmppTcpProxy::setOutPipe( const QString & jidDest, int localPort, int remotePort, const QString & remoteHost, int id )
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

void QXmppTcpProxy::clearPipe()
{
    if ( pd->sock )
        pd->sock->deleteLater();
    if ( pd->serv )
        pd->serv->deleteLater();
    pd->sock = 0;
    pd->serv = 0;
}

bool QXmppTcpProxy::handleStanza(const QDomElement &element)
{
    //qDebug() << "==========================\r\n";
    // QByteArray a;
    // QXmlStreamWriter xmlStream(&a);
    //pd->packetIq.parse( element );
    //const QByteArray & stri = pd->packetIq.data();
    //qDebug() << stri;
    //qDebug() << pd->packetIq.id();
    //qDebug() << element.text();
    //qDebug() << "==========================\r\n";

    if ( element.tagName() == "iq")
    {
        if ( QXmppPacketIq::isPacketIq( element, pd->id ) )
        {
            pd->packetIq.parse( element );
            const QByteArray & stri = pd->packetIq.data();
            if ( pd->sock )
            {
                pd->skipData = true;
                pd->sock->write( stri );

                qDebug() << "#####################<" << stri;
            }
            return true;
        }
        else if ( ( !pd->outgoing ) && ( QXmppConfigPipeIq::isConfigPipeIq( element, pd->id ) ) )
        {
            // Only if configured as not outgoing.
            pd->configIq.parse( element );
            pd->remotePort = pd->configIq.port();
            pd->remoteHost = pd->configIq.host();
            pd->jidDest    = pd->configIq.from();

            clearPipe();
            QTcpSocket * sock = new QTcpSocket( this );
            pd->skipData = false;
            connect( sock, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
            sock->connectToHost( pd->remoteHost, pd->remotePort );
            sock->waitForConnected();
            pd->sock = sock;
            return true;
        }
    }
    return false;
}

void QXmppTcpProxy::serverNewConnection()
{
    if ( !pd->serv )
        return;
    QTcpSocket * sock = pd->serv->nextPendingConnection();
    if ( pd->sock )
        pd->sock->deleteLater();
    pd->skipData = false;
    connect( sock, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
    pd->sock = sock;
    // On local new connection there should be new connection on other side
    // in the case of outgoing pipe direction.
    if ( pd->outgoing )
    {
        pd->configIq.setId( pd->id );
        pd->configIq.setPort( pd->remotePort );
        pd->configIq.setHost( pd->remoteHost );
        pd->configIq.setTo( pd->jidDest );
        pd->configIq.setFrom( client()->configuration().jidBare() );
        client()->sendPacket( pd->configIq );
    }
}

void QXmppTcpProxy::socketReadyRead()
{
    /*if ( pd->skipData )
    {
        pd->skipData = false;
        return;
    }*/
    if ( !pd->sock )
        return;
    pd->stri = pd->sock->readAll();
    pd->packetIq.setId( pd->id );
    pd->packetIq.setData( pd->stri );
    pd->packetIq.setTo( pd->jidDest );
    pd->packetIq.setFrom( client()->configuration().jidBare() );
    client()->sendPacket( pd->packetIq );

    qDebug() << "#####################>" << pd->stri;
}






