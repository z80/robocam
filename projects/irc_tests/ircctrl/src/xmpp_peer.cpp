
#include "xmpp_peer.h"

XmppPeer::XmppPeer()
    : m_session( 0 ), 
      m_client( 0 ), 
      m_reg( 0 ), 
      m_connected( false ), 
      m_doRegister( false )
{
    
}

XmppPeer::~XmppPeer()
{

}

void XmppPeer::setMessageHandler( TMessageHandler handler )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_messageHandler = handler;
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

void XmppPeer::setRegistering( bool reg )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_doRegister = reg;
}

bool XmppPeer::connect()
{
    //terminate();
    boost::mutex::scoped_lock lock( m_mutex );
    m_thread = boost::thread( boost::bind( &XmppPeer::run, this ) );
    m_cond.wait( lock );
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
    if ( m_session )
    {
        if ( m_session->target().bare() != to )
        {
            m_client->disposeMessageSession( m_session );
            gloox::JID jid( to );
            m_session = new gloox::MessageSession( m_client, jid );
            m_session->registerMessageHandler( this );
        }
    }
    if ( m_session )
    {
        m_session->send( msg );
        return true;
    }
    return false;
}

const std::string XmppPeer::lastError() const
{
    boost::mutex::scoped_lock lock( m_mutex );
    return m_lastError;
}

void XmppPeer::onConnect()
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( m_doRegister )
    	m_reg->fetchRegistrationFields();
    m_connected = true;
    m_cond.notify_one();
    if ( !m_logHandler.empty() )
        m_logHandler( "Connected" );
}

void XmppPeer::onDisconnect( gloox::ConnectionError e )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_connected = false;
    m_cond.notify_one();
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "Disconnected";
        if ( e != gloox::ConnNoError )
            out << ", error: " << e;
        m_logHandler( out.str() );
    }
}

bool XmppPeer::onTLSConnect( const gloox::CertInfo & info )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_connected = true;
    m_cond.notify_one();
    if ( !m_logHandler.empty() )
        m_logHandler( "TLS Connected" );
    return true;
}

void XmppPeer::handleMessage( const gloox::Message & msg, gloox::MessageSession * s )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_messageHandler.empty() )
        m_messageHandler( s->target().bare(), msg.body() );
}

void XmppPeer::handleMessageEvent( const gloox::JID & from, gloox::MessageEventType type )
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

void XmppPeer::handlerChatState( const gloox::JID & from, gloox::ChatStateType type )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << from.bare() << "chat state chage: origin: ";
        out << from.bare();
        out << ", type: " << type;
        m_logHandler( out.str() );
    }
}

void XmppPeer::handleMessageSession( gloox::MessageSession * s )
{
    m_client->disposeMessageSession( m_session );
    m_session = s;
    m_session->registerMessageHandler( this );
}

void XmppPeer::handleRegistrationFields( const gloox::JID & from, int fields, std::string instructions )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "fields: " << fields;
        out << ", instructions: \"" << instructions << "\"";
        m_logHandler( out.str() );
    }
    gloox::RegistrationFields vals;
    vals.username = m_jid;
    vals.password = m_password;
    m_reg->createAccount( fields, vals );
}

void XmppPeer::handleRegistrationResult( const gloox::JID & from, gloox::RegistrationResult result )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "result: " << result;
        m_logHandler( out.str() );
    }
//    if ( result != gloox::RegistrationSuccess )
//    	m_client->disconnect();
}

void XmppPeer::handleAlreadyRegistered( const gloox::JID & from )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "The account already exists";
        m_logHandler( out.str() );
    }
}

void XmppPeer::handleDataForm( const gloox::JID & from, const gloox::DataForm & form )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "DataForm received";
        m_logHandler( out.str() );
    }
}

void XmppPeer::handleOOB( const gloox::JID & from, const gloox::OOB & oob )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "OOB registration requested: \"";
        out << oob.desc() << "\", ";
        out << "\"" << oob.url() << "\"";
        m_logHandler( out.str() );
    }
}

void XmppPeer::handleLog( gloox::LogLevel level,gloox:: LogArea area, const std::string & msg )
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

void XmppPeer::run()
{
	{
		boost::mutex::scoped_lock lock( m_mutex );
		if ( !m_doRegister )
		{
			std::ostringstream out;
			out << m_jid << "@" << m_host;
			gloox::JID jid( out.str() );
			m_client = new gloox::Client( jid, m_password );
		}
		else
			m_client = new gloox::Client( m_host );
		if ( m_port > 0 )
			m_client->setPort( m_port );
		m_client->registerConnectionListener( this );
		m_client->registerMessageSessionHandler( this, 0 );

		if ( m_doRegister )
		{
			m_reg = new gloox::Registration( m_client );
			m_reg->registerRegistrationHandler( this );
		}

		m_client->logInstance().registerLogHandler( gloox::LogLevelDebug, gloox::LogAreaAll, this );
	}
    m_client->connect();

    if ( m_session )
    {
        m_client->disposeMessageSession( m_session );
        m_session = 0;
    }
    if ( m_reg )
    {
        delete m_reg;
        m_reg = 0;
    }
    delete m_client;
}



















