
#include "xmpp_peer.h"

XmppPeer::XmppPeer()
{

}

XmppPeer::~XmppPeer()
{

}

void XmppPeer::setMessageHandler( TMessageHandler handler )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_mesageHandler = handler;
}

void XmppPeer::setLogHandler( TLogHandler handler )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_logHandler = handler;
}

void XmppPeer::setHost( const std::string & host, int port )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_host = host;
	m_port = port;
}

void XmppPeer::setNick( const std::string & jid, const std::string & password )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_jid = jid;
	m_password = password;
}

bool XmppPeer::connect()
{
	terminate();
	boost::mutex::scoped_lock lock( m_mutex );
	m_thread = boost::thread( boost::bind( &XmppPeer::run, this ) );
	m_cond.wait();
	return m_connected;
}

bool XmppPeer::isConnected() const
{
	boost::mutex::scoped_lock lock( m_mutex );
	return m_connected;
}

void XmppPeer::terminate()
{
	m_client->disconnect();
	m_thread.join();
	boost::mutex::scoped_lock lock( m_mutex );
	m_connected = false;
}

bool XmppPeer::send( const std::string & to, const std::string & msg )
{
	return true;
}

const std::string XmppPeer::lastError() const
{
	boost::mutex::scoped_lock lock( m_mutex );
	return m_lastError;
}

void XmppPeer::onConnect()
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_connected = true;
	m_cond.notify_one();
	if ( !m_logHandler.empty() )
		m_logHandler( "Connected" );
}

void XmppPeer::onDisconnect( ConnectionError e )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_connected = false;
	m_cond.notify_one();
	if ( !m_logHandler.empty() )
	{
		std::ostringstream out;
		out << "Disconnected";
		if ( e == ConnAuthenticationFailed )
			out << ", authentication failed";
		m_logHandler( out.str() );
	}
}

bool XmppPeer::onTLSConnect( const CertInfo & info )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_connected = true;
	m_cond.notify_one();
	if ( !m_logHandler.empty() )
		m_logHandler( "TLS Connected" );
	return true;
}

void XmppPeer::handleMessage( const Message & msg, MessageSession * s )
{
	boost::mutex::scoped_lock lock( m_mutex );
	if ( !m_messageHandler.empty() )
		m_messageHandler( s->target(), msg.body() );
}

void XmppPeer::handleMessageEvent( const & JID & from, MessageEventType type )
{
	boost::mutex::scoped_lock lock( m_mutex );
	if ( !m_logHandler.empty() )
	{
		std::ostringstream out;
		out << from.bare() << ", msg type: ";
		out << type;
		m_logHandler( out.str() );
	}
}

void XmppPeer::handlerChatState( const JID & from, ChatStateType type )
{

}

void XmppPeer::handleMessageSession( MessageSession * s )
{

}

void XmppPeer::handleLog( LogLevel level, LogArea area, const std::string & msg )
{
	boost::mutex::scoped_lock lock( m_mutex );
	if ( !m_logHandler.empty() )
	{
		std::ostringstream out;
		out << "LVL: " << level;
		out << ", AREA: " << area;
		out << ", MSG: \"" << msg << "\"";
		m_logHandler( out.str() );
	}
}

void run()
{
	boost::mutex::scoped_lock lock( m_mutex );
	std::ostringstream out;
	out << m_jid << "@" << m_host;
	JID jid( out.str() );
	m_client = new Client( jid, m_password, m_port );
	m_client->registerConnectionListener( this );
	m_client->registerMessageSessionHandler( this, 0 );
	m_client->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );

	m_client->connect();
	delete m_client;
}


