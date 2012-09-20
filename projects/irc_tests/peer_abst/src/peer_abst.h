
#ifndef __PEER_ABST_H_
#define __PEER_ABST_H_

#include <boost/function.hpp>
#include <string>
// Command sender and executor.

struct lua_State;
class  QIODevice;

class PeerAbst
{
public:
	typedef boost::function<void (lua_State *)> TInit;
	typedef boost::function<QIODevice * (const std::string &)>       TInFileHandler;
	typedef boost::function<void (const std::string &, QIODevice *)> TAccFileHandler;

	PeerAbst( TInit init );
	virtual ~PeerAbst();

	// Local command invocation.
	// It is also should be called by remote peer.
	void invokeCmd( const std::string & cmd );
	// File io handlers;
	void setInFileHandler( TInFileHandler handler );
	void setAccFileHandler( TAccFileHandler handler );
protected:
    // Should be called in appropriate places when file comes in and when it is downoaded.
    QIODevice * acceptFile( const std::string & fileName );
    void fileDownloaded( const std::string & fileName, QIODevice * );

public:
	virtual bool isConnected() = 0;
	// Send cmd to another peer.
	virtual bool send( const std::string & cmd ) = 0;
	virtual bool sendFile( const std::string fileName, QIODevice * dev ) = 0;
	//virtual bool sendBinary( const std::string & desc, const std::basic_string<char> & data ) = 0;
public:
	class PD;
	PD * pd;
};


#endif



