
#include "peer_abst.h"

#include <queue>
#include "lua.hpp"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

static void luaHook( lua_State * L, lua_Debug * ar );

class PeerAbst::PD
{
public:
	PD( PeerAbst * owner, TInit init );
	~PD();

private:
	PeerAbst * peer;
	lua_State * L;
	boost::thread luaThread;
	boost::mutex  luaTaskMutex;
	boost::condition luaCond;
	std::queue<std::string> luaCommands;
	bool do_terminate;

	void luaLoop( TInit init );
protected:
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
	int n = lua_gettop( L );
	lua_pushstring( L, PeerAbst::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	int n1 = lua_gettop( L );
	PeerAbst::PD * pd = reinterpret_cast<PeerAbst::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	pd->luaTaskMutex.lock();
	int cnt = pd->luaCommands.size();
	if ( cnt )
	{
		pd->pendingCmd = pd->luaCommands.front();
		pd->luaCommands.pop();
	}
	pd->luaTaskMutex.unlock();
	if ( cnt )
	{
		lua_pushstring( L, pd->pendingCmd.c_str() );
		lua_pushstring( L, "loadstring" );
		lua_gettable( L, LUA_GLOBALSINDEX );
		int res = lua_pcall( L, 1, 0, 0 );
		if ( res )
		{
			pd->pendingCmd = lua_tostring( L, -1 );
			// Send back an error message.
			pd->peer->send( pd->pendingCmd );
			// And pop that message.
			lua_pop( L, 1 );
		}
	}
}

PeerAbst::PD::PD( PeerAbst * owner, TInit init )
	: peer( owner ),
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
	//luaL_dofile( L, LUA_INITIAL_SETUP.c_str() );
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

void PeerAbst::PD::invokeCmd( const std::string & cmd )
{
	boost::mutex::scoped_lock lock( luaTaskMutex );
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
	connect();
}

PeerAbst::~PeerAbst()
{
	terminate();
	delete pd;
}

void PeerAbst::invokeCmd( const std::string & cmd )
{
	pd->invokeCmd( cmd );
}








