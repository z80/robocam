
#include "irc_peer.h"
#include "libircclient.h"
#include "libirc_rfcnumeric.h"

#include <sstream>

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

//* Static functions declaration.
static void event_connect( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count );
static void event_nick( irc_session_t * session,
		                   const char * event,
		                   const char * origin,
		                   const char ** params,
		                   unsigned int count );
static void event_channel( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count );
static void event_privmsg( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count );
static void event_notice( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count );
static void event_join( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count );
static void event_numeric( irc_session_t * session,
		                      unsigned int event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count );
static void irc_event_dcc_chat( irc_session_t * session, 
                                const char * nick, 
                                const char * addr, 
                                irc_dcc_t dccid );
static void irc_event_dcc_send( irc_session_t * session, 
                                const char * nick, 
                                const char * addr, 
                                const char * filename, 
                                unsigned long size, 
                                irc_dcc_t dccid );
static void dcc_recv_callback( irc_session_t * session, 
                               irc_dcc_t id, 
                               int status, 
                               void * ctx, 
                               const char * data, 
                               unsigned int length );
static void dcc_file_recv_callback( irc_session_t * session, 
                                    irc_dcc_t id, 
                                    int status, 
                                    void * ctx, 
                                    const char * data, 
                                    unsigned int length );

//* Private data class for storaging data which is not convenient to #include <>
//* in destination application.
class IrcPeer::PD
{
public:
	PD() {}
	~PD() {}
	std::string host;
	int port;
	std::string nick, realName;
	std::string userName, password;
	// File data.
	irc_dcc_t dccId;
	std::string fileName;
	std::basic_string<char> fileData;
	unsigned int filePointer;
	std::basic_string<char> dccData;
	
	// Channels list, clients list.
	std::list<std::string> channels, 
	                       clients;
	
	// Status.
	bool connected, 
	     joined, 
	     dccAccepted,
	     dccFileSent, 
	     dccFileFinished, 
	     enumChannelsFinished, 
	     enumClientsFinished;
	std::string channel;
	std::string lastError;
	// IRC session
	irc_session_t * ircS;
	// Thread management.
	boost::thread thread;
	boost::mutex mutex;
	// Message handler.
	TMessageHandler messageHandler;
	TJoinHandler    joinHandler;
	TDccHandler     dccHandler;
	TDccFileHandler dccFileHandler;
	// Separate function which doesn't return.
	void ircRun();
};

void IrcPeer::PD::ircRun()
{
    this->mutex.lock();
    ircS = 0;
    connected = false;
    joined    = false;
    dccFileSent = false;
    dccFileFinished = false;
    enumChannelsFinished = true;
    enumClientsFinished  = true;
	lastError = "";
	
	const char * host = this->host.data();
	int port          = this->port;
	const char * nick = this->nick.data();
	const char * realName = ( this->realName.size() > 0 ) ? this->realName.data() : 0;
	const char * userName = ( this->userName.size() > 0 ) ? this->userName.data() : 0;
	const char * password = ( this->password.size() > 0 ) ? this->password.data() : 0;
	this->mutex.unlock();

	irc_callbacks_t	callbacks;

	// Initialize the callbacks
	memset( &callbacks, 0, sizeof(callbacks) );

	// Set up the callbacks we will use
	callbacks.event_connect = event_connect;
	callbacks.event_channel = event_channel;
   	callbacks.event_privmsg = event_privmsg;
   	callbacks.event_notice  = event_notice;
   	callbacks.event_join    = event_join;
	callbacks.event_nick    = event_nick;
	callbacks.event_numeric = event_numeric;
    callbacks.event_dcc_chat_req = irc_event_dcc_chat;
	callbacks.event_dcc_send_req = irc_event_dcc_send;


	// And create the IRC session; 0 means error
	irc_session_t * s = irc_create_session( &callbacks );
	
	this->mutex.lock();
	this->ircS = s;
	this->mutex.unlock();
	
	// Set context to be able to get in in event handlers.
	irc_set_ctx( s, this );
	
	if ( irc_connect( s, host, port, password, nick, userName, realName ) )
	{
		lastError = std::string( "Could not connect: %s\n" ) + std::string( irc_strerror(irc_errno(s)) );
		return;
	}

	// and run into forever loop, generating events
	if ( irc_run( s ) )
	{
		lastError = std::string( "Could not connect or I/O error: %s\n" ) + std::string( irc_strerror( irc_errno(s) ) );
		return;
	}
	
	this->mutex.lock();
	irc_destroy_session( s );
	ircS = 0;
	connected = false;
	this->mutex.unlock();
}

IrcPeer::IrcPeer()
{
	pd = new PD();
	pd->ircS = 0;
	pd->connected       = false;
	pd->joined          = false;
	pd->dccAccepted     = false;
	pd->dccFileFinished = false;
	pd->dccFileSent     = false;
    pd->enumChannelsFinished = true;
    pd->enumClientsFinished  = true;
}

IrcPeer::~IrcPeer()
{
	delete pd;
}

void IrcPeer::setMessageHandler( const TMessageHandler & handler )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->messageHandler = handler;
}

void IrcPeer::setJoinHandler( const TJoinHandler & handler )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->joinHandler = handler;
}

void IrcPeer::setDccHandler( const TDccHandler & handler )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->dccHandler = handler;
}

void IrcPeer::setDccFileHandler( const TDccFileHandler & handler )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->dccFileHandler = handler;
}

void IrcPeer::setHost( const std::string & host, int port )
{
	pd->host = host;
	pd->port = port;
}

void IrcPeer::setLogin( const std::string & userName, const std::string & password )
{
	pd->userName = userName;
	pd->password = password;
}

void IrcPeer::setNick( const std::string & nick, const std::string & realName )
{
	pd->nick     = nick;
	pd->realName = realName;
}

void IrcPeer::connect( const std::string address, int port )
{
	pd->thread = boost::thread( boost::bind( &IrcPeer::PD::ircRun, pd ) );
}

bool IrcPeer::isRunning()
{
    bool res = pd->thread.joinable();	
    return res;
}

bool IrcPeer::isConnected()
{
    boost::mutex::scoped_lock lock( pd->mutex );

    if ( !pd->ircS )
        return false;
    bool res = pd->connected;
    return res;
}

void IrcPeer::terminate()
{
    boost::mutex::scoped_lock lock( pd->mutex );

    if ( isConnected() )
        irc_disconnect( pd->ircS );
}

const std::string & IrcPeer::lastError()
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->lastError;
}

void IrcPeer::join( const std::string & stri, const std::string & password )
{
	const char * key = ( password.size() > 0 ) ? password.c_str() : 0;
    boost::mutex::scoped_lock lock( pd->mutex );
	int res = irc_cmd_join( pd->ircS, stri.c_str(), key );
	pd->joined = false;	
}

bool IrcPeer::isJoined() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
	return pd->joined;
}

void IrcPeer::send( const std::string & stri )
{
    boost::mutex::scoped_lock lock( pd->mutex );
	irc_cmd_msg( pd->ircS, pd->channel.c_str(), stri.c_str() );
}

void IrcPeer::send( const std::string & nick, const std::string & stri )
{
    boost::mutex::scoped_lock lock( pd->mutex );
	irc_cmd_msg( pd->ircS, nick.c_str(), stri.c_str() );
}

void IrcPeer::requestDcc( const std::string nick )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->dccId       = -1;
    pd->dccAccepted = false;
    irc_dcc_chat( pd->ircS, pd, nick.c_str(), dcc_recv_callback, &pd->dccId );
}

bool IrcPeer::isDccAccepted() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
	return pd->dccAccepted;
}

void IrcPeer::sendDcc( const std::string & data )
{
	irc_dcc_msg( pd->ircS, pd->dccId, data.c_str() );
}

void IrcPeer::sendDccFile( const std::string & fileName )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->dccFileFinished = false;
    pd->dccFileSent     = false;
}

bool IrcPeer::isDccFileFinished() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->dccFileFinished;
}

bool IrcPeer::isDccFileSent() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->dccFileSent;
}

void IrcPeer::enumChannels()
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->enumChannelsFinished = false;
    pd->channels.clear();
    irc_cmd_list( pd->ircS, 0 );
}

bool IrcPeer::isEnumChannelsFinished() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->enumChannelsFinished;
}

const std::list<std::string> & IrcPeer::channels() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->channels;
}

void IrcPeer::enumClients( const std::string channel )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    pd->enumClientsFinished = false;
    pd->clients.clear();
    if ( channel.size() > 0 )
	    irc_cmd_names( pd->ircS, channel.c_str() );
	else
		irc_cmd_names( pd->ircS, pd->channel.c_str() );
}

bool IrcPeer::isEnumClientsFinished() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->enumClientsFinished;
}

const std::list<std::string> & IrcPeer::clients() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->clients;
}










static void event_connect( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count )
{
    IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
    boost::mutex::scoped_lock lock( pd->mutex );
	pd->connected = true;    
}

static void event_nick( irc_session_t * session,
		                   const char * event,
		                   const char * origin,
		                   const char ** params,
		                   unsigned int count )
{
}

static void messageHandler( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count )
{
    const int SZ = 90;
    char nick[ SZ ];
	irc_target_get_nick( origin, nick, SZ );
    std::string snick = std::string( nick );
    std::string text = ( count > 1 ) ? params[1] : "";
    IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
    boost::mutex::scoped_lock lock( pd->mutex );
    if ( !pd->messageHandler.empty() )
        pd->messageHandler( snick, text );
}

static void event_channel( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count )
{
    messageHandler( session, event, origin, params, count );
}

static void event_privmsg( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count )
{
    messageHandler( session, event, origin, params, count );
}

static void event_notice( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count )
{
    messageHandler( session, event, origin, params, count );
}

static void event_join( irc_session_t * session,
		                      const char * event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count )
{
    IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
    boost::mutex::scoped_lock lock( pd->mutex );
	if ( pd->nick == origin )
	{
		pd->joined = true;
		pd->channel = params[0];
	}
	else
	{
		if ( !pd->joinHandler.empty() )
			pd->joinHandler( origin );
	}
}

static void event_numeric( irc_session_t * session,
		                      unsigned int event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count )
{
	switch ( event )
	{
	case  LIBIRC_RFC_RPL_NAMREPLY:
		{
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->clients.push_back( origin );
		}
		break;
    case  LIBIRC_RFC_RPL_ENDOFNAMES:
		{
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->enumClientsFinished = true;
		}
		break;		
	case LIBIRC_RFC_RPL_LIST:
		{
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->channels.push_back( origin );
		}
		break;
	case LIBIRC_RFC_ERR_NOSUCHSERVER:
	case LIBIRC_RFC_RPL_LISTEND:
		{
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->enumChannelsFinished = true;
		}
		break;
	}
	
	if ( event > 400 )
	{
		std::string fulltext;
		for ( unsigned int i=0; i<count; i++ )
		{
			if ( i > 0 )
				fulltext += " ";
			fulltext += params[i];
		}
		std::ostringstream out;
		out << "ERROR ";
		out << event;
		out << " ";
		out << (origin) ? std::string( origin ) : std::string( "?" );
		out << " ";
		out << fulltext.c_str();
		
		IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
		boost::mutex::scoped_lock lock( pd->mutex );
		pd->lastError =  out.str();
	}
}

static void irc_event_dcc_chat( irc_session_t * session, 
                                const char * nick, 
                                const char * addr, 
                                irc_dcc_t dccid )
{
	irc_dcc_accept( session, dccid, 0, dcc_recv_callback );
}

static void irc_event_dcc_send( irc_session_t * session, 
                                const char * nick, 
                                const char * addr, 
                                const char * filename, 
                                unsigned long size, 
                                irc_dcc_t dccid )
{
	IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
	boost::mutex::scoped_lock lock( pd->mutex );
	pd->fileName = filename;
	pd->fileData.resize( size );
	pd->filePointer = 0;
	irc_dcc_accept( session, dccid, pd, dcc_file_recv_callback );
}

static void dcc_recv_callback( irc_session_t * session, 
                               irc_dcc_t id, 
                               int status, 
                               void * ctx, 
                               const char * data, 
                               unsigned int length )
{
	switch ( status )
	{
	case LIBIRC_ERR_CLOSED:
		{
			std::ostringstream out;
			out <<  "DCC ";
			out << id;
			out << ": chat closed";
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( ctx );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->lastError = out.str();
			break;
		}
	case 0:
		{
			if ( !data )
			{
				IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( ctx );
				boost::mutex::scoped_lock lock( pd->mutex );
				pd->dccAccepted = true;
			}
			else 
			{
				IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( ctx );
				boost::mutex::scoped_lock lock( pd->mutex );
				if ( !pd->dccHandler.empty() )
					pd->dccHandler( data );
			}
			break;
		}
	default:
		{
			std::ostringstream out;
			out << "DCC ";
			out << id;
			out << ": error ";
			out << irc_strerror(status);
		
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( ctx );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->lastError = out.str();
			break;
		}
	}
}

static void dcc_file_recv_callback( irc_session_t * session, 
                                    irc_dcc_t id, 
                                    int status, 
                                    void * ctx, 
                                    const char * data, 
                                    unsigned int length )
{
	if ( status == 0 && length == 0 )
	{
		IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( ctx );
		boost::mutex::scoped_lock lock( pd->mutex );
		pd->dccFileSent     = true;
		pd->dccFileFinished = true;
	}
	else if ( status )
	{
		std::ostringstream out;
		out << "File sent error: ";
		out << status;
		IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( ctx );
		boost::mutex::scoped_lock lock( pd->mutex );
		pd->dccFileFinished = true;
		pd->lastError = out.str();
	}
	else
	{
		IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( ctx );
		boost::mutex::scoped_lock lock( pd->mutex );
		memcpy( const_cast<char *>(pd->fileData.data())+pd->filePointer, data, length );
		pd->filePointer += length;
		if ( ( pd->filePointer >= pd->fileData.size() ) && 
			 ( !pd->dccFileHandler.empty() ) )
		{
			pd->dccFileHandler( pd->fileName, pd->fileData );
		}
	}
}





