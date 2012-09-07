
#ifndef __PEER_ABST_H_
#define __PEER_ABST_H_

// Command sender and executor.

class PeerAbst
{
public:
	PeerAbst();
	virtual ~PeerAbst();

	// Local or remote commands invocation.
	void invokeCmd( const std::string & cmd );

protected:
	virtual bool connect() = 0;
	virtual void terminate() = 0;
public:
	virtual bool isConnected() = 0;
	// Send cmd to another peer.
	virtual bool send( const std::string & cmd ) = 0;
	//virtual bool sendBinary( const std::string & desc, const std::basic_string<char> & data ) = 0;
private:
	class PD;
	PD * pd;
};


#endif



