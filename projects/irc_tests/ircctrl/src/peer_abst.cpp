
#include "peer_abst.h"

#include "lua.hpp"
#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"

static int luaHook( lua_State * L, lua_Debug * ar );

class PeerAbst::PD
{
public:
	PD( PeerAbst * owner )
	: peer( owner ),
	  terminate( false )
	{
	}

	~PD()
	{
		terminate();
	}
private:
	PeerAbst * peer;
	lua_State * L;
	boost::thread luaThread;
	boost::mutex  luaTaskMutex,
	              yieldMutex;
	std::list<std::string> luaCommands;
	bool terminate;

	void luaLoop();
protected:
	const std::string LUA_INITIAL_SETUP;
	const std::string LUA_PD_NAME;

	std::string pendingCmd;
public:
	void invokeCmd( const std::string & cmd );
	bool isIdle();
	void terminate();

	friend static int luaHook( lua_State * L, lua_Debug * ar );
};

const std::string PeerAbst::PD::LUA_INITIAL_SETUP = "./init.lua";
const std::string PeerAbst::PD::LUA_PD_NAME = "PD";

static int luaHook( lua_State * L, lua_Debug * ar );
{
	int n = lua_gettop( L );
	lua_pushstring( L, PD::LUA_PD_NAME );
	lua_gettable( L, LUA_REGISTRYINDEX );
	int n1 = lua_gettop( L );
	PeerAbst::PD * pd = reinterpret_cast<PeerAbst::PD *>( lua_topointer( L, -1 ) );
	pd->luaTaskMutex.lock();
	int cnt = pd->luaCommands.size();
	if ( cnt )
	{
		pd->pendingCommand = pd->luaCommands.front();
		pd->luaCommands.pop_front();
	}
	pd->luaTaskMutex.unlock();
	if ( cnt )
	{
		lua_pushstring( L, pd->luapendingCommand.c_str() );
		lua_pushstring( L, "loadstring" );
		lua_gettable( L, LUA_GLOBALSINDEX );
		int res = lua_pcall( L, 1, 0, 0 );
		if ( res )
		{
			pd->pendingCommand = lua_tostring( L, -1 );
			// Send back an error message.
			peer->send( pd->pendingCommand );
			// And pop that message.
			lua_pop( L, 1 );
		}
	}
}

PeerAbst::PD( PeerAbst * owner )
	: peer( owner ),
	  terminate( false )
{
}

PeerAbst::~PD()
{
	terminate();
}

void PeerAbst::PD::luaLoop()
{
	L = luaL_newstate();
	luaL_openlibs( L );
	lua_pushstring( L, LUA_PD_NAME );
	lua_pushlightuserdata( L, this );
	lua_settable( L, LUA_REGISTRYINDEX );
	lua_sethook( L, lua_hook, LUA_MASKLINE, 0 );
	luaL_dofile( L, LUA_INITIAL_SETUP.c_str() );

	while ( 1 )
	{
		luaMutex.lock();
		int cnt = pd->luaCommands.size();
		luaMutex.unlock();
		if ( cnt )
			lua_hook( L, 0 );
		else
		{
			yieldMutex.lock();
			luaMutex.lock();
			bool term = terminate;
			luaMutex.unlock();
			if ( term )
				break;
		}
	}
	lua_close( L );
}

void PeerAbst::PD::invokeCmd( const std::string & cmd )
{
	luaTaskMutex.lock();
	luaCommands.push_back( cmd );
	yieldMutex.unlock();
	pd->luaTaskMutex.unlock();
}

bool PeerAbst::PD::isIdle()
{
	bool managedToLock = yieldMutex.try_lock();
	if ( managedToLock )
		yieldMutex.unlock();
	return !managedToLock;
}

void PeerAbst::PD::terminate()
{
	luaTaskMutex.lock();
	terminate = true;
	yieldMutex.unlock();
	luaThread.join();
}








PeerAbst::PeerAbst()
{
	pd = new PD( this );

}

PeerAbst::~PeerAbst()
{
	delete pd;
}

void PeerAbst::invokeCmd( const std::string & cmd )
{
	pd->invokeCmd( cmd );
}








