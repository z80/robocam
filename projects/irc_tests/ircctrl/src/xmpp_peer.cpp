
#include "xmpp_peer.h"

XmppPeer::XmppPeer()
    : m_session( 0 ), 
      m_client( 0 ), 
      m_reg( 0 ), 
      m_connected( false ), 
      m_doRegister( false );
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

void XmppPeer::setRegistering( bool reg )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_doRegister = reg;
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
    if ( m_session )
    {
        if ( m_session->target().bare() != to )
        {
            m_client->disposeMessageSession( m_session );
            JID jid( to );
            m_session = new MessageSesion( m_client, jid );
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

void XmppPeer::handleMessageSession( MessageSession * s )
{
    m_client->disposeMessageSession( m_session );
    m_session = s;
    m_session->registerMessageHandler( this );
}

void XmppPeer::handleRegistrationFields( const JID& from, int fields, std::string instructions )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "fields: " >> fields;
        out << ", instructions: \"" << instrunctions << "\"";
        m_logHandler( out.str() );
    }
    RegistrationFields vals;
    vals.username = m_jid;
    vals.password = m_password;
    m_reg->createAccount( fields, vals );
}

void XmppPeer::handleRegistrationResult( const JID& from, RegistrationResult result )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "result: " >> result;
        m_logHandler( out.str() );
    }
    j->disconnect();
}

void XmppPeer::handleAlreadyRegistered( const JID& from )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "The account already exists";
        m_logHandler( out.str() );
    }
}

void XmppPeer::handleDataForm( const JID & from, const DataForm & form )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "DataForm received";
        m_logHandler( out.str() );
    }
}

void XmppPeer::handleOOB( const JID& from, const OOB& oob )
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

void XmppPeer::run()
{
    boost::mutex::scoped_lock lock( m_mutex );
    std::ostringstream out;
    out << m_jid << "@" << m_host;
    JID jid( out.str() );
    m_client = new Client( jid, m_password, m_port );
    m_client->registerConnectionListener( this );
    m_client->registerMessageSessionHandler( this, 0 );
    
    if ( m_doRegister )
    {
        m_reg = new Registration( j );
        m_reg->registerRegistrationHandler( this );
    }
    
    m_client->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );
    
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



















