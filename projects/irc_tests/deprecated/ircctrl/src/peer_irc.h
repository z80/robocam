
#ifndef __PEER_IRC_H_
#define __PEER_IRC_H_

#include "peer_abst.h"

class PeerIrc: public PeerAbst
{
public:
	PeerIrc( const std::string & iniFile, PeerAbst::TInit init );
	~PeerIrc();
private:
	bool connect();
	void terminate();
public:
	bool isConnected();
	bool send( const std::string & cmd );
	std::string lastError() const;
private:
	class PD;
	PD * pd;
};





#endif

