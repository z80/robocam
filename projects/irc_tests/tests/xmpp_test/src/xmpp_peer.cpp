
#include "xmpp_peer.h"
#include "disco.h"

XmppPeer::XmppPeer()
    : m_session( 0 ), 
      m_client( 0 ), 
      m_reg( 0 ), 
      m_connected( false ), 
      m_registered( false ), 
      m_ibbManager( 0 ), 
      m_ibb( 0 ), 
      m_fileSession( 0 ), 
      m_filePieceSize( 2048 ), 
      m_isFileFinished( false ),
      m_isFileSucceeded( false )
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

bool XmppPeer::connect()
{
    //terminate();
    boost::mutex::scoped_lock lock( m_mutex );
    m_connected = false;
    m_doRegister = false;
    m_thread = boost::thread( boost::bind( &XmppPeer::run, this, false ) );
    m_cond.wait( lock );
    return m_connected;
}

bool XmppPeer::registerClient()
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_registered = false;
    m_doRegister = true;
    m_thread = boost::thread( boost::bind( &XmppPeer::run, this, true ) );
    m_cond.wait( lock );
    return m_registered;
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
}

bool XmppPeer::send( const std::string & to, const std::string & msg )
{
    //boost::mutex::scoped_lock lock( m_mutex );
    if ( m_session )
    {
        if ( m_session->target().bare() != to )
        {
            m_client->disposeMessageSession( m_session );
            m_session = 0;
        }
    }
    if ( !m_session )
    {
		std::ostringstream out;
		out << to << "@" << m_host;
        gloox::JID jid( out.str() );
        m_session = new gloox::MessageSession( m_client, jid );
        m_session->registerMessageHandler( this );
    }

    if ( m_session )
    {
        m_session->send( msg );
        return true;
    }
    return false;
}

void XmppPeer::setPieceSize( int bytes )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_filePieceSize = bytes;
}

void XmppPeer::sendFile( const std::string & to, const char * data, int sz )
{
    //boost::mutex::scoped_lock lock( m_mutex );
    std::ostringstream out;
    out << to << "@" << m_host;
    gloox::JID jid( out.str() );
    if ( !m_ibbManager )
    {
        m_ibbManager = new gloox::InBandBytestreamManager( m_client );
        m_ibbManager->registerInBandBytestreamHandler( this );
    }
    m_isFileFinished  = false;
    m_isFileSucceeded = false;
    m_fileData = data;
    m_fileSize = sz;
    m_filePointer = 0;
    m_ibbManager->requestInBandBytestream( jid, this );
}

bool XmppPeer::isFileFinished() const
{
    boost::mutex::scoped_lock lock( m_mutex );
    return m_isFileFinished;
}

bool XmppPeer::isFileSucceeded() const
{
    boost::mutex::scoped_lock lock( m_mutex );
    return m_isFileSucceeded;
}

void XmppPeer::reserveFileBuffer( int size )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_fileReceived.reserve( size );
}

const std::string XmppPeer::lastError() const
{
    boost::mutex::scoped_lock lock( m_mutex );
    return m_lastError;
}

void XmppPeer::onConnect()
{
    if ( m_doRegister )
    	m_reg->fetchRegistrationFields();
    else
    {
        boost::mutex::scoped_lock lock( m_mutex );
        m_connected = true;
        m_cond.notify_one();
    }
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
    if ( !m_logHandler.empty() )
        m_logHandler( "TLS Connected" );
    return true;
}

void XmppPeer::handleMessage( gloox::Stanza *stanza, gloox::MessageSession * )
{
    boost::mutex::scoped_lock lock( m_mutex );
    if ( !m_messageHandler.empty() )
        m_messageHandler( stanza->from().bare(), stanza->body() );
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
    gloox::RegistrationFields vals;
    {
        boost::mutex::scoped_lock lock( m_mutex );
        if ( !m_logHandler.empty() )
        {
            std::ostringstream out;
            out << "fields: " << fields;
            out << ", instructions: \"" << instructions << "\"";
            m_logHandler( out.str() );
        }
        vals.username = m_jid;
        vals.password = m_password;
    }
    m_reg->createAccount( fields, vals );
}

void XmppPeer::handleRegistrationResult( const gloox::JID & from, gloox::RegistrationResult result )
{
    {
        boost::mutex::scoped_lock lock( m_mutex );
        if ( !m_logHandler.empty() )
        {
            std::ostringstream out;
            out << "result: " << result;
            m_logHandler( out.str() );
        }
        m_registered = (result == gloox::RegistrationSuccess);
        m_cond.notify_one();
    }
  	m_client->disconnect();
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
    m_registered = true;
  	m_client->disconnect();
    m_cond.notify_one();
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

void XmppPeer::handleLog( gloox::LogLevel level, gloox::LogArea area, const std::string & msg )
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

bool XmppPeer::handleIncomingInBandBytestream( const gloox::JID & from, gloox::InBandBytestream * ibb )
{
	boost::mutex::scoped_lock lock( m_mutex );
    m_ibb = ibb;
    if ( m_fileSession )
    	delete m_fileSession;
    m_fileSession = new gloox::MessageSession( m_client, from );
    m_ibb->attachTo( m_fileSession );
    m_ibb->registerInBandBytestreamDataHandler( this );
    m_fileReceived.clear();
    return true;
}

void XmppPeer::handleOutgoingInBandBytestream( const gloox::JID & to,   gloox::InBandBytestream * ibb )
{
    m_ibb = ibb;
    if ( m_fileSession )
    	delete m_fileSession;
    m_fileSession = new gloox::MessageSession( m_client, to );
    m_ibb->attachTo( m_fileSession );
    m_ibb->registerInBandBytestreamDataHandler( this );
    std::string stri;
    stri.resize( m_filePieceSize );
    for ( int i=0; i<m_fileSize; i+=m_filePieceSize )
    {
        int sz = m_fileSize - i;
        sz = ( m_filePieceSize <= sz ) ? m_filePieceSize : sz;
        stri.resize( sz );
        memcpy( const_cast<char *>( stri.c_str() ), m_fileData+i, sizeof( char ) * sz );
        if ( !m_ibb->sendBlock( stri ) )
        {
        	boost::mutex::scoped_lock lock( m_mutex );
            m_isFileFinished = true;
            m_isFileSucceeded = false;
            return;
        }
    }
    m_ibbManager->dispose( m_ibb );
    m_ibb = 0;
    boost::mutex::scoped_lock lock( m_mutex );
    m_isFileFinished = true;
    m_isFileSucceeded = true;
}

void XmppPeer::handleInBandBytestreamError( const gloox::JID& /*remote*/, gloox::StanzaError /*se*/ )
{
	boost::mutex::scoped_lock lock( m_mutex );
    m_isFileFinished = true;
    m_isFileSucceeded = false;
    m_ibbManager->dispose( m_ibb );
    m_ibb = 0;
}

void XmppPeer::handleInBandData( const std::string& data, const std::string& sid )
{
	boost::mutex::scoped_lock lock( m_mutex );
	m_fileReceived.append( data );
}

void XmppPeer::handleInBandError( const std::string& /*sid*/, const gloox::JID& /*remote*/, gloox::StanzaError /*se*/ )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_isFileFinished = true;
    m_isFileSucceeded = false;
    m_ibbManager->dispose( m_ibb );
    m_ibb = 0;
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "In band error";
        m_logHandler( out.str() );
    }
}

void XmppPeer::handleInBandClose( const std::string& /*sid*/, const gloox::JID& /*from*/ )
{
    boost::mutex::scoped_lock lock( m_mutex );
    m_ibbManager->dispose( m_ibb );
    m_ibb = 0;
    m_isFileFinished = true;
    m_isFileSucceeded = true;
    if ( !m_logHandler.empty() )
    {
        std::ostringstream out;
        out << "In band close";
        m_logHandler( out.str() );
    }
}











void XmppPeer::run( bool reg )
{
	//boost::mutex::scoped_lock lock( m_mutex );
	if ( !reg )
	{
		std::ostringstream out;
		out << m_jid << "@" << m_host;
		gloox::JID jid( out.str() );
		m_client = new gloox::Client( jid, m_password );
		//m_client->setServer( m_host );
        //m_client->setForceNonSasl();
	    //m_client->disco()->setVersion( "messageTest", gloox::GLOOX_VERSION, "Linux" );
	    //m_client->disco()->setIdentity( "client", "bot" );
	    //m_client->disco()->addFeature( gloox::XMLNS_CHAT_STATES );
	}
	else
	{
		m_client = new gloox::Client( m_host );
		m_client->disableRoster();
	}
	if ( m_port > 0 )
		m_client->setPort( m_port );
	m_client->registerConnectionListener( this );
	m_client->registerMessageSessionHandler( this, 0 );
	if ( reg )
	{
		m_reg = new gloox::Registration( m_client );
		m_reg->registerRegistrationHandler( this );
	}
	m_client->logInstance().registerLogHandler( gloox::LogLevelDebug, gloox::LogAreaAll, this );

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



















