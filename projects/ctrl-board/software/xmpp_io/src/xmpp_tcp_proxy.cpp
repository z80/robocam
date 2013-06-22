
#include "QXmppClient.h"
#include "xmpp_pipe_packet_iq.h"
#include "xmpp_config_pipe_iq.h"
#include <QtNetwork>
#include <QtXml>

#include "xmpp_tcp_proxy.h"

class QXmppTcpProxy::PD
{
public:
    PD() {}
    ~PD() {}

    int id;
    int localPort;
    QTcpServer * serv;
    QTcpSocket * sock;
    QByteArray   stri;
    QXmppPacketIq packetIq;
};

QXmppTcpProxy::QXmppTcpProxy( int id )
    : QXmppClientExtension()
{
    pd = new PD();
    pd->id   = id;
    pd->localPort = 0;
    pd->sock = 0;
    pd->serv = 0;
}

QXmppTcpProxy::~QXmppTcpProxy()
{
    delete pd;
}

void QXmppTcpProxy::setPipe( int localPort, bool outgoing, int id )
{
    if ( id >= 0 )
        pd->id = id;
    clearPipe();
    if ( outgoing )
    {
        QTcpServer * serv = new QTcpServer( this );
        connect( serv, SIGNAL(newConnection()), this, SLOT(serverNewConnection()) );
        serv->listen( QHostAddress::Any, localPort );
        pd->serv = serv;
    }
    else
    {
        QTcpSocket * sock = new QTcpSocket( this );
        sock->connectToHost( "localhost", localPort );
        pd->localPort = localPort;
        pd->sock      = sock;
    }
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

    if ( ( element.tagName() == "iq") && ( QXmppPacketIq::isPacketIq( element, pd->id ) ) )
    {
        pd->packetIq.parse( element );
        const QByteArray & stri = pd->packetIq.data();
        if ( pd->sock )
        {
            if ( pd->sock->state() == QAbstractSocket::UnconnectedState )
            {
                pd->sock->connectToHost( "localhost", pd->localPort );
                pd->sock->waitForConnected();
            }
            pd->sock->write( stri );
        }
        return true;
    }
    return false;
}

void QXmppTcpProxy::serverNewConnection()
{
    if ( !pd->serv )
        return;
    QTcpSocket * sock = pd->serv->nextPendingConnection();
    connect( sock, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
}

void QXmppTcpProxy::socketReadyRead()
{
    if ( !pd->sock )
        return;
    pd->stri = pd->sock->readAll();
    pd->packetIq.setData( pd->stri );
    client()->sendPacket( pd->packetIq );
}






