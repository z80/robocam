
#ifndef __PEER_IRC_H_
#define __PEER_IRC_H_

#include "peer_abst.h"

class PeerIrc: public PeerAbst
{
public:
	PeerIrc( const std::string & iniFile );
	~PeerIrc();
protected:
	bool connect();
	void terminate();
public:
	bool isConnected();
	bool send( const std::string & cmd );
};





#endif

