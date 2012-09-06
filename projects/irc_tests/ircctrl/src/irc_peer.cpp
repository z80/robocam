
#include "irc_peer.h"
#include "libircclient.h"
#include "libirc_rfcnumeric.h"

#include <sstream>

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

void addlog (const char * fmt, ...)
{
	FILE * fp;
	char buf[1024];
	va_list va_alist;

	va_start (va_alist, fmt);
#if defined (WIN32)
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
#else
	vsnprintf (buf, sizeof(buf), fmt, va_alist);
#endif
	va_end (va_alist);

	printf ("%s\n", buf);

	if ( (fp = fopen ("irctest.log", "ab")) != 0 )
	{
		fprintf (fp, "%s\n", buf);
		fclose (fp);
	}
}


void dump_event (irc_session_t * session, int event, const char * origin, const char ** params, unsigned int count)
{
	char buf[512];
	int cnt;

	buf[0] = '\0';

	for ( cnt = 0; cnt < count; cnt++ )
	{
		if ( cnt )
			strcat (buf, "|");

		strcat (buf, params[cnt]);
	}


	addlog ("Event \"%d\", origin: \"%s\", params: %d [%s]", event, origin ? origin : "NULL", cnt, buf);
}




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
	int timeout;
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
	// Blocking functions management
	boost::timed_mutex waitMutex;
	boost::mutex       waitMutexExclusive;
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
	pd->timeout         = 10000;
	pd->ircS            = 0;
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
	terminate();
	delete pd;
}

void IrcPeer::setTimeout( int ms )
{
	pd->timeout = ms;
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
	boost::mutex::scoped_lock lock( pd->mutex );
	pd->host = host;
	pd->port = port;
}

void IrcPeer::setLogin( const std::string & userName, const std::string & password )
{
	boost::mutex::scoped_lock lock( pd->mutex );
	pd->userName = userName;
	pd->password = password;
}

void IrcPeer::setNick( const std::string & nick, const std::string & realName )
{
	boost::mutex::scoped_lock lock( pd->mutex );
	pd->nick     = nick;
	pd->realName = realName;
}

bool IrcPeer::connect( const std::string address, int port )
{
	terminate();
	// Reset lastError.
	pd->mutex.lock();
	pd->lastError = std::string();
	pd->mutex.unlock();
	pd->thread = boost::thread( boost::bind( &IrcPeer::PD::ircRun, pd ) );
	// Lock.
	pd->timedMutex.lock();
	// Wait till unlocked or timeout.
	pd->timedMutexExclusive.lock();
	bool res = pd->timedMutex.timed_lock( boost::posix_time::milliseconds( pd->timeout ) );
	pd->timedMutex.unlock();
	pd->timedMutexExclusive.unlock();
	pd->mutex.lock();
	res = res && (pd->lastError.size() < 1) && ( pd->connected );
	pd->mutex.unlock();
	return res;
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

void IrcPeer::terminate( const std::string & reason )
{

    if ( isConnected() )
    {
        boost::mutex::scoped_lock lock( pd->mutex );
        const char * rsn = ( reason.size() > 0 ) ? reason.c_str() : 0;
        irc_cmd_quit( pd->ircS, rsn );
        irc_disconnect( pd->ircS );
    }
    pd->thread.join();
}

const std::string & IrcPeer::lastError()
{
    boost::mutex::scoped_lock lock( pd->mutex );
    return pd->lastError;
}

bool IrcPeer::join( const std::string & stri, const std::string & password )
{
	const char * key = ( password.size() > 0 ) ? password.c_str() : 0;
    pd->mutex.lock();
    pd->lastError = std::string()
	pd->joined = false;
	int res = irc_cmd_join( pd->ircS, stri.c_str(), key );
	pd->mutex.unlock();
	// Lock.
	pd->timedMutex.lock();
	// Wait till unlocked or timeout.
	pd->timedMutexExclusive.lock();
	bool res = pd->timedMutex.timed_lock( boost::posix_time::milliseconds( pd->timeout ) );
	pd->timedMutex.unlock();
	pd->timedMutexExclusive.unlock();
	pd->mutex.lock();
	res = res && (pd->lastError.size() < 1) && ( pd->joined );
	pd->mutex.unlock();
	return res;
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

bool IrcPeer::requestDcc( const std::string nick )
{
    pd->mutex.lock();
    pd->dccId       = -1;
    pd->dccAccepted = false;
    irc_dcc_chat( pd->ircS, pd, nick.c_str(), dcc_recv_callback, &pd->dccId );
    pd->mutex.unlock();
	// Lock.
	pd->timedMutex.lock();
	// Wait till unlocked or timeout.
	pd->timedMutexExclusive.lock();
	bool res = pd->timedMutex.timed_lock( boost::posix_time::milliseconds( pd->timeout ) );
	pd->timedMutex.unlock();
	pd->timedMutexExclusive.unlock();
	pd->mutex.lock();
	res = res && (pd->lastError.size() < 1) && ( pd->dccAccepted );
	pd->mutex.unlock();
	return res;
}

bool IrcPeer::isDccAccepted() const
{
    boost::mutex::scoped_lock lock( pd->mutex );
	return pd->dccAccepted;
}

void IrcPeer::sendDcc( const std::string & data )
{
    boost::mutex::scoped_lock lock( pd->mutex );
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

bool IrcPeer::enumChannels( std::list<std::string> & l )
{
    pd->mutex.lock();
    pd->enumChannelsFinished = false;
    pd->channels.clear();
    irc_cmd_list( pd->ircS, 0 );
    pd->mutex.unlock();
	// Wait till unlocked or timeout.
	pd->timedMutexExclusive.lock();
	bool res = pd->timedMutex.timed_lock( boost::posix_time::milliseconds( pd->timeout ) );
	pd->timedMutex.unlock();
	pd->timedMutexExclusive.unlock();
	pd->mutex.lock();
	res = res && (pd->lastError.size() < 1) && ( pd->enumChannelsFinished );
	l = pd->channels;
	pd->mutex.unlock();
	return res;
}

void IrcPeer::enumClients( const std::string channel, std::list<std::string> & l )
{
    pd->mutex.lock();
    pd->enumClientsFinished = false;
    pd->clients.clear();
    if ( channel.size() > 0 )
	    irc_cmd_names( pd->ircS, channel.c_str() );
	else
		irc_cmd_names( pd->ircS, pd->channel.c_str() );
    pd->mutex.unlock();
	// Wait till unlocked or timeout.
	pd->timedMutexExclusive.lock();
	bool res = pd->timedMutex.timed_lock( boost::posix_time::milliseconds( pd->timeout ) );
	pd->timedMutex.unlock();
	pd->timedMutexExclusive.unlock();
	pd->mutex.lock();
	res = res && (pd->lastError.size() < 1) && ( pd->enumClientsFinished );
	l = pd->clients;
	pd->mutex.unlock();
	return res;
}

void IrcPeer::ircRawCmd( const std::string & stri )
{
    boost::mutex::scoped_lock lock( pd->mutex );
    irc_send_raw( pd->ircS, stri.c_str() );
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
	// Unlock timedMutex.
	pd->timedMutexExclusive.lock();
	pd->timedMutex.try_lock();
	pd->timedMutex.unlock();
	pd->timedMutexExclusive.unlock();
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
		// Unlock timedMutex.
		pd->timedMutexExclusive.lock();
		pd->timedMutex.try_lock();
		pd->timedMutex.unlock();
		pd->timedMutexExclusive.unlock();	}
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
	dump_event( session, event, origin, params, count );
	switch ( event )
	{
	case  LIBIRC_RFC_RPL_NAMREPLY:
		{
			if ( count > 3 )
			{
				IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
				boost::mutex::scoped_lock lock( pd->mutex );
				std::string s( params[3] );
				std::istringstream iss(s);
				std::string sub;
				do
				{
				    iss >> sub;
					pd->clients.push_back( sub );
				} while (iss);
			}
		}
		break;
    case  LIBIRC_RFC_RPL_ENDOFNAMES:
		{
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->enumClientsFinished = true;
			// Unlock timedMutex.
			pd->timedMutexExclusive.lock();
			pd->timedMutex.try_lock();
			pd->timedMutex.unlock();
			pd->timedMutexExclusive.unlock();
		}
		break;		
	case LIBIRC_RFC_RPL_LIST:
		{
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
			boost::mutex::scoped_lock lock( pd->mutex );
			if ( count > 1 )
				pd->channels.push_back( params[1] );
		}
		break;
	case LIBIRC_RFC_ERR_NOSUCHSERVER:
	case LIBIRC_RFC_RPL_LISTEND:
		{
			IrcPeer::PD * pd = reinterpret_cast<IrcPeer::PD *>( irc_get_ctx( session ) );
			boost::mutex::scoped_lock lock( pd->mutex );
			pd->enumChannelsFinished = true;
			// Unlock timedMutex.
			pd->timedMutexExclusive.lock();
			pd->timedMutex.try_lock();
			pd->timedMutex.unlock();
			pd->timedMutexExclusive.unlock();
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
		// Unlock timedMutex.
		pd->timedMutexExclusive.lock();
		pd->timedMutex.try_lock();
		pd->timedMutex.unlock();
		pd->timedMutexExclusive.unlock();
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
				// Unlock timedMutex.
				pd->timedMutexExclusive.lock();
				pd->timedMutex.try_lock();
				pd->timedMutex.unlock();
				pd->timedMutexExclusive.unlock();
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





