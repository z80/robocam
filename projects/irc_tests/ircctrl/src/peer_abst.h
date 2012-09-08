
#ifndef __PEER_ABST_H_
#define __PEER_ABST_H_

#include <boost/function.hpp>
#include <string>
// Command sender and executor.

struct lua_State;

class PeerAbst
{
public:
	typedef boost::function<void (lua_State *)> TInit;

	PeerAbst( TInit init );
	virtual ~PeerAbst();

	// Local command invocation.
	// It is also should be called by remote peer.
	void invokeCmd( const std::string & cmd );

public:
	virtual bool isConnected() = 0;
	// Send cmd to another peer.
	virtual bool send( const std::string & cmd ) = 0;
	//virtual bool sendBinary( const std::string & desc, const std::basic_string<char> & data ) = 0;
public:
	class PD;
	PD * pd;
};


#endif



