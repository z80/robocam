
#ifndef __PEER_QXMPP_H_
#define __PEER_QXMPP_H_

#include "peer_abst.h"
#include <QImage>

class PeerQxmpp: public PeerAbst
{
public:
    PeerQxmpp( const std::string & iniFile, PeerAbst::TInit );
    ~PeerQxmpp();

    void connect();
	bool isConnected();
	bool send( const std::string & cmd );
    bool sendFile( const std::string & fileName, QIODevice * file );
    void call();
    void endCall();
    void setFrameHandler( TFrameHandler handler );
    bool frame( QImage & image );

private:
    class PD;
    PD * pd;
};




#endif




