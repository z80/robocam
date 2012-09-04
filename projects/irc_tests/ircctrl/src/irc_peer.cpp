
#include "irc_peer.h"
#include "libircclient.h"

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
static void event_numeric( irc_session_t * session,
		                      unsigned int event,
		                      const char * origin,
		                      const char ** params,
		                      unsigned int count );

//* Private data class for storaging data which is not convenient to #include
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
	std::string lastError;
	// IRC session
	irc_session_t * ircS;
	// Thread management.
	boost::thread thread;
	boost::mutex mutex;
	// Separate function which doesn't return.
	void ircRun();
};

void IrcPeer::PD::ircRun()
{
    this->mutex.lock();
    ircS = 0;
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
	callbacks.event_nick    = event_nick;
	callbacks.event_numeric = event_numeric;

	// And create the IRC session; 0 means error
	irc_session_t * s = irc_create_session( &callbacks );
	
	this->mutex.lock();
	this->ircS = s;
	this->mutex.unlock();
	
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
	this->mutex.unlock();
}

IrcPeer::IrcPeer()
{
	pd = new PD();
	pd->ircS = 0;
}

IrcPeer::~IrcPeer()
{
	delete pd;
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
    bool res = ( irc_is_connected( pd->ircS ) == 1 );
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

void IrcPeer::send( const std::string & stri )
{

}




