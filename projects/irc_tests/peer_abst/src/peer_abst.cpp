
#include "peer_abst.h"
#include <QtCore>

#include <queue>
#include "lua.hpp"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

static void luaHook( lua_State * L, lua_Debug * ar );
static int msleep( lua_State * L );
static int isConnected( lua_State * L );
static int send( lua_State * L );
static int sendFile( lua_State * L );
static int stop( lua_State * L );

class PeerAbst::PD
{
public:
	PD( PeerAbst * owner, TInit init );
	~PD();

public:
	PeerAbst * peer;
	lua_State * L;
	boost::thread luaThread;
	boost::mutex  luaTaskMutex;
	boost::condition luaCond;
	std::queue<std::string> luaCommands;
	bool do_stop, do_terminate;
	
	TInFileHandler  inFileHandler;
	TAccFileHandler accFileHandler;

	void luaLoop( TInit init );
	void stop();
public:
	//static const std::string LUA_INITIAL_SETUP;
	static const std::string LUA_PD_NAME;

	std::string pendingCmd;
public:
	void invokeCmd( const std::string & cmd );
	bool isIdle();
	void terminate();

	friend void luaHook( lua_State * L, lua_Debug * ar );
};

//const std::string PeerAbst::PD::LUA_INITIAL_SETUP = "./init.lua";
const std::string PeerAbst::PD::LUA_PD_NAME = "PD";

static void luaHook( lua_State * L, lua_Debug * ar )
{
	//int n = lua_gettop( L );
	lua_pushstring( L, PeerAbst::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	//int n1 = lua_gettop( L );
	PeerAbst::PD * pd = reinterpret_cast<PeerAbst::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	pd->luaTaskMutex.lock();
	int cnt = pd->luaCommands.size();
	if ( cnt )
	{
		pd->pendingCmd = pd->luaCommands.front();
		pd->luaCommands.pop();
	}
	bool stop = pd->do_stop;
	pd->luaTaskMutex.unlock();
	if ( stop )
	{
		lua_pushstring( L, "print( \"Execution stopped\" )" );
	    lua_error( L );
	}
	if ( cnt )
	{
		lua_pushstring( L, "loadstring" );
		lua_gettable( L, LUA_GLOBALSINDEX );
		lua_pushstring( L, pd->pendingCmd.c_str() );
		int res = lua_pcall( L, 1, 2, 0 );
		if ( lua_isnil( L, -2 ) != 0 )
		{
			pd->pendingCmd = lua_tostring( L, -1 );
			// Send back an error message.
			pd->peer->send( pd->pendingCmd );
			// And pop that message.
			lua_pop( L, 2 );
		}
		else
		{
			res = lua_pcall( L, 1, 0, 0 );
			if ( res )
			{
				pd->pendingCmd = lua_tostring( L, -1 );
				// Send back an error message.
                std::ostringstream out;
                out << "print( \"" << pd->pendingCmd << "\" )";
				pd->peer->send( out.str() );
				// And pop that message.
				lua_pop( L, 1 );
			}
		}
	}
}

PeerAbst::PD::PD( PeerAbst * owner, TInit init )
	: peer( owner ),
	  do_stop( false ),
	  do_terminate( false )
{
	luaThread = boost::thread( boost::bind( &PeerAbst::PD::luaLoop, this, init ) );
}

PeerAbst::PD::~PD()
{
	terminate();
}

void PeerAbst::PD::luaLoop( TInit init )
{
	L = luaL_newstate();
	luaL_openlibs( L );
	lua_pushstring( L, LUA_PD_NAME.c_str() );
	lua_pushlightuserdata( L, this );
	lua_settable( L, LUA_REGISTRYINDEX );
	lua_sethook( L, luaHook, LUA_MASKLINE, 0 );

	// Registering C functions.
	/*luaL_Reg reg[] =
	{
		{ "msleep",      ::msleep },
		{ "isConnected", ::isConnected },
		{ "send",        ::send },
		{ "stop",        ::stop },
		{ 0,             0 }
	};
	luaL_register( L, 0, reg );*/
	lua_register( L, "msleep", ::msleep );
	lua_register( L, "isConnected", ::isConnected );
	lua_register( L, "send", ::send );
	lua_register( L, "stop", ::stop );

	if ( !init.empty() )
		init( L );

	boost::mutex::scoped_lock lock( luaTaskMutex );
	while ( 1 )
	{
		int cnt = luaCommands.size();
		if ( cnt )
		{
			luaTaskMutex.unlock();
			luaHook( L, 0 );
			luaTaskMutex.lock();
		}
		else
		{
			luaCond.wait( lock );
			if ( do_terminate )
				break;
		}
	}
	lua_close( L );
}

void PeerAbst::PD::stop()
{
	boost::mutex::scoped_lock lock( luaTaskMutex );
	do_stop = true;
}

void PeerAbst::PD::invokeCmd( const std::string & cmd )
{
	boost::mutex::scoped_lock lock( luaTaskMutex );
	do_stop = false;
	luaCommands.push( cmd );
	luaCond.notify_one();
}

bool PeerAbst::PD::isIdle()
{
	boost::mutex::scoped_lock lock( luaTaskMutex );
	unsigned int cnt = luaCommands.size();
	return (cnt == 0);
}

void PeerAbst::PD::terminate()
{
	{
		boost::mutex::scoped_lock lock( luaTaskMutex );
		do_terminate = true;
		luaCond.notify_one();
	}
	luaThread.join();
}








PeerAbst::PeerAbst( TInit init )
{
	pd = new PD( this, init );
}

PeerAbst::~PeerAbst()
{
	delete pd;
}

void PeerAbst::invokeCmd( const std::string & cmd )
{
	pd->invokeCmd( cmd );
}

void PeerAbst::setInFileHandler( TInFileHandler handler )
{
    pd->inFileHandler = handler;
}

void PeerAbst::setAccFileHandler( TAccFileHandler handler )
{
    pd->accFileHandler = handler;
}

QIODevice * PeerAbst::inFile( const std::string & fileName )
{
    if ( !pd->inFileHandler.empty() )
        return pd->inFileHandler( fileName );
    return 0;
}

void PeerAbst::accFile( const std::string & fileName, QIODevice * fileData )
{
    if ( !pd->accFileHandler.empty() )
        pd->accFileHandler( fileName, fileData );
    else
        fileData->deleteLater();
}

bool PeerAbst::sendFileInternal( const std::string fileName, const std::string & filePath )
{
    QFile * file = new QFile( filePath.c_str() );
    bool res = sendFile( fileName, file );
    return res;
}







static int msleep( lua_State * L )
{
	int ms;
	if ( lua_gettop( L ) > 0 )
	    ms = static_cast<int>( lua_tonumber( L, 1 ) );
	else
		ms = 1;
	boost::this_thread::sleep( boost::posix_time::milliseconds( ms ) );
	return 0;
}

static int isConnected( lua_State * L )
{
	lua_pushstring( L, PeerAbst::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	PeerAbst::PD * pd = reinterpret_cast<PeerAbst::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	bool res = pd->peer->isConnected();
	lua_pushboolean( L, res ? 1 : 0 );
	return 1;
}

static int send( lua_State * L )
{
	std::string stri = lua_tostring( L, 1 );
	lua_pushstring( L, PeerAbst::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	PeerAbst::PD * pd = reinterpret_cast<PeerAbst::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	bool res = pd->peer->send( stri );
	lua_pushboolean( L, res ? 1 : 0 );
	return 1;
}

static int sendFile( lua_State * L )
{
	std::string fileName = lua_tostring( L, 1 );
	std::string filePath = lua_tostring( L, 2 );
	lua_pushstring( L, PeerAbst::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	PeerAbst::PD * pd = reinterpret_cast<PeerAbst::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	bool res = pd->peer->sendFileInternal( fileName, filePath );
	lua_pushboolean( L, res ? 1 : 0 );
	return 1;
}

static int stop( lua_State * L )
{
	lua_pushstring( L, PeerAbst::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	PeerAbst::PD * pd = reinterpret_cast<PeerAbst::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	pd->stop();
	return 0;
}







