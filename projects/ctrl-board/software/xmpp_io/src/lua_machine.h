
#ifndef __LUA_MACHINE_H_
#define __LUA_MACHINE_H_

#include <boost/function.hpp>
#include <string>
#include <QtCore>
#include "xmpp_io.h"
// Command sender and executor.

struct lua_State;

class LuaMachine: public QObject
{
    Q_OBJECT
public:
	typedef boost::function<void (lua_State *)> TInit;

    LuaMachine( QXmppPeer * parent, TInit init = TInit() );
	virtual ~LuaMachine();

	// Block current thread till undergound thread exit.
	void join();

	// Local command invocation.
	// It is also should be called by remote peer.
	void invokeCmd( const std::string & cmd );

public:
	// Send cmd to another peer.
	void print( const QString & stri );
    void status( const QString & stri );
    void data( const QString & stri );

signals:
    void sigPrint( const QString & stri );
    void sigStatus( const QString & stri );
    void sigData( const QString & stri );

private slots:
    void qxmppMessageReceived( const QString & );
    void slotPrint( const QString & stri );
    void slotStatus( const QString & stri );
    void slotData( const QString & stri );

public:
	class PD;
	PD * pd;
};


#endif



