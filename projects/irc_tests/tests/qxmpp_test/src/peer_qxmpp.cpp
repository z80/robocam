
#include "peer_qxmpp.h"

QxmppPeer::QxmppPeer( QObject * parent )
{
	bool check = connect( this, SIGNAL(connected()), SLOT(connected()) );
    Q_ASSERT(check);

    check = connect( this, SIGNAL(disconnected()), SLOT(disconnected()) );
    Q_ASSERT(check);

    check = connect( this, SIGNAL(error(QXmppClient::Error)), SLOT(error(QXmppClient::Error)) );
    Q_ASSERT(check);

    check = connect(this, SIGNAL(messageReceived(QXmppMessage)),
        SLOT(messageReceived(QXmppMessage)));
    Q_ASSERT(check);
    Q_UNUSED(check);
}

QxmppPeer::~QxmppPeer()
{

}

void QxmppPeer::send( const std::string & jid, const std::string & stri )
{

}

bool QxmppPeer::connect( const std::string & jid, const std::string & password )
{
	connectToServer( QString::fromStdString( jid ), QString::fromStdString( password ) );
}

bool QxmppPeer::isConnected() const
{

}

void echoClient::messageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString msg = message.body();

    sendPacket(QXmppMessage("", from, "Your message: " + msg));
}


