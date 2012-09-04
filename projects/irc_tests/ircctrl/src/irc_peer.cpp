
#include "irc_peer.h"
#include "libircclient.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <boost/thread.hpp>

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
};

IrcPeer::IrcPeer()
{
	pd = new PD();
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
	irc_set_ctx( s, &pd );
    /*
	if ( irc_connect( s, host.data(), port, 0, nick, 0, 0 ) )
	{
		printf( "Could not connect: %s\n", irc_strerror(irc_errno(s)) );
		return 1;
	}

	// and run into forever loop, generating events
	if ( irc_run( s ) )
	{
		printf ( "Could not connect or I/O error: %s\n", irc_strerror( irc_errno(s) ) );
		return 2;
	}*/

}

void IrcPeer::send( const std::string & stri )
{

}

