
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
protected:
	void connect( const std::string address, int port = 6667 );
	void send( const std::string & stri );
private:
    class PD;
	PD * pd;
};



#endif



