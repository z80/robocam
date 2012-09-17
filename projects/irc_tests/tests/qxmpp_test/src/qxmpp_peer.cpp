
#include "qxmpp_peer.h"
#include "QXmppMessage.h"
#include <sstream>

QxmppPeer::QxmppPeer( QObject * parent )
{
    bool check = QObject::connect( this, SIGNAL(connected()), SLOT(connected()) );
    Q_ASSERT(check);

    check = QObject::connect( this, SIGNAL(disconnected()), SLOT(disconnected()) );
    Q_ASSERT(check);

    check = QObject::connect( this, SIGNAL(error(QXmppClient::Error)), SLOT(error(QXmppClient::Error)) );
    Q_ASSERT(check);

    check = QObject::connect(this, SIGNAL(messageReceived(QXmppMessage)),
        SLOT(messageReceived(QXmppMessage)));
    Q_ASSERT(check);
    Q_UNUSED(check);
}

QxmppPeer::~QxmppPeer()
{

}

void QxmppPeer::setLogHandler( TLogHandler handler )
{
    m_logHandler = handler;
}

void QxmppPeer::setMessageHandler( TMessageHandler handler )
{
    m_messageHandler = handler;
}

void QxmppPeer::send( const std::string & jid, const std::string & stri )
{
    sendMessage( QString::fromStdString( jid ), QString::fromStdString( stri ) );
}

void QxmppPeer::connect( const std::string & jid, const std::string & password )
{
	connectToServer( QString::fromStdString( jid ), QString::fromStdString( password ) );
}

void QxmppPeer::terminate()
{
    disconnectFromServer();
}

void QxmppPeer::connected()
{
    QXmppPresence pr;
    setClientPresence( pr );
    if ( !m_logHandler.empty() )
        m_logHandler( "Connected" );
}

void QxmppPeer::disconnected()
{
    if ( !m_logHandler.empty() )
        m_logHandler( "Disconnected" );
}

void QxmppPeer::error( QXmppClient::Error err )
{
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Error: ";
        out << err;
        m_logHandler( out.str() );
    }
}

void QxmppPeer::messageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString msg  = message.body();

    //sendPacket( QXmppMessage("", from, "Your message: " + msg) );
    if ( !m_messageHandler.empty() )
        m_messageHandler( from.toStdString(), msg.toStdString() );
}


