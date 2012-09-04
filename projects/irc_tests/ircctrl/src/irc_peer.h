
#ifndef __IRC_PEER_H_
#define __IRC_PEER_H_

#include <string>

/**
 *  IrcPeer a C++ envelope for libircclient library.
 */
class IrcPeer
{
public:
	IrcPeer();
	~IrcPeer();
	void setHost( const std::string & host, int port = 6667 );
	void setLogin( const std::string & userName, const std::string & password );
	void setNick( const std::string & nick, const std::string & realName );
	void connect( const std::string address = std::string(), int port = 6667 );
protected:
	void send( const std::string & stri );
private:
    class PD;
	PD * pd;
};



#endif



