
#ifndef __IRC_PEER_H_
#define __IRC_PEER_H_

#include <string>
#include <list>
#include <boost/function.hpp>

/**
 *  IrcPeer a C++ envelope for libircclient library.
 */
class IrcPeer
{
public:
	typedef boost::function<void ( const std::string &, const std::string & )> TMessageHandler;
	typedef boost::function<void ( const std::string & )> TJoinHandler;
	typedef boost::function<void ( const std::string & )> TDccHandler;
	typedef boost::function<void ( const std::string &, const std::basic_string<char> & )> TDccFileHandler;

	IrcPeer();
	~IrcPeer();
	void setTimeout( int ms = 30000 );
	void setMessageHandler( const TMessageHandler & handler );
	void setJoinHandler( const TJoinHandler & handler );
	void setDccHandler( const TDccHandler & handler );
	void setDccFileHandler( const TDccFileHandler & handler );
	void setHost( const std::string & host, int port = 6667 );
	void setLogin( const std::string & userName, const std::string & password = std::string() );
	void setNick( const std::string & nick, const std::string & realName = std::string() );
	bool connect( const std::string address = std::string(), int port = 6667 );
	bool isRunning();
	bool isConnected();
	void terminate( const std::string & reason = std::string() );
	const std::string & lastError();
	bool join( const std::string & stri, const std::string & password = std::string() );
	bool isJoined() const;
	void send( const std::string & stri );
	void send( const std::string & nick, const std::string & stri );
	bool requestDcc( const std::string nick );
	bool isDccAccepted() const;
	void sendDcc( const std::basic_string<char> & data );
	bool sendDccFile( const std::string & nick, const std::string & fileName );
	bool isDccFileFinished() const;
	bool isDccFileSent() const;
	
	// List channels.
	bool channels( std::list<std::string> & l );
	// List clients.
	bool clients( const std::string channel, std::list<std::string> & l );
	// Client info.
	bool clientInfo( const std::string & nick );
	// Raw command.
	void ircRawCmd( const std::string & stri );
protected:
public:
    class PD;
	PD * pd;
};



#endif



