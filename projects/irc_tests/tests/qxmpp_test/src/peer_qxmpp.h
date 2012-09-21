
#ifndef __PEER_QXMPP_H_
#define __PEER_QXMPP_H_

#include "peer_abst.h"

class PeerQxmpp: public PeerAbst
{
public:
    PeerQxmpp( PeerAbst::TInit );
    ~PeerQxmpp();

	bool isConnected();
	bool send( const std::string & cmd );
    bool sendFile( const std::string & fileName, QIODevice * file );
private:
    class PD;
    PD * pd;
};




#endif




