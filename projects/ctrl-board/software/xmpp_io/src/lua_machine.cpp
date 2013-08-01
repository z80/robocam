
#include "lua_machine.h"
#include <QtCore>
#include <QtXml>

#include <queue>
#include "lua.hpp"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

static void luaHook( lua_State * L, lua_Debug * ar );
static int peer( lua_State * L );
static int msleep( lua_State * L );
static int print( lua_State * L );
static int status( lua_State * L );
static int data( lua_State * L );
static int stop( lua_State * L );

static int enterCritical( lua_State * L );
static int leaveCritical( lua_State * L );

class LuaMachine::PD
{
public:
	PD( LuaMachine * owner, TInit init );
	~PD();

public:
    QXmppPeer  * client;
	LuaMachine * peer;
	lua_State * L;
	boost::thread luaThread;
	boost::mutex  luaTaskMutex;
	boost::condition luaCond;
	std::queue<std::string> luaCommands;
	bool do_stop, do_terminate;
	
	void luaLoop( TInit init );
	void stop();
public:
	static const std::string LUA_PD_NAME;
	static const int         MAX_SLEEP_INTERVAL;

	std::string pendingCmd;
public:
	void invokeCmd( const std::string & cmd );
	bool isIdle();
	void terminate();

	friend void luaHook( lua_State * L, lua_Debug * ar );
};

const std::string LuaMachine::PD::LUA_PD_NAME = "PD";
const int LuaMachine::PD::MAX_SLEEP_INTERVAL = 10000;

static void luaHook( lua_State * L, lua_Debug * ar )
{
	int top = lua_gettop( L );
	lua_pushstring( L, LuaMachine::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	
	LuaMachine::PD * pd = reinterpret_cast<LuaMachine::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
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
            std::ostringstream out;
            out << pd->pendingCmd;
            pd->peer->print( out.str().c_str() );
		}
		else
		{
			res = lua_pcall( L, 1, 0, 0 );
			if ( res )
			{
				pd->pendingCmd = lua_tostring( L, -1 );
				// Send back an error message.
                std::ostringstream out;
                out << pd->pendingCmd;
                pd->peer->print( out.str().c_str() );
			}
		}
	}
	lua_settop( L, top );
}

LuaMachine::PD::PD( LuaMachine * owner, TInit init )
	: peer( owner ),
	  do_stop( false ),
	  do_terminate( false )
{
	luaThread = boost::thread( boost::bind( &LuaMachine::PD::luaLoop, this, init ) );
}

LuaMachine::PD::~PD()
{
	terminate();
}

void LuaMachine::PD::luaLoop( TInit init )
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
    lua_register( L, "peer",   ::peer );
    lua_register( L, "msleep", ::msleep );
    lua_register( L, "print",  ::print );
    lua_register( L, "status", ::status );
    lua_register( L, "data",   ::data );
    lua_register( L, "stop",   ::stop );

    // For noninterruptable Lua code such as read after write I2C.
    lua_register( L, "enterCritical",   ::enterCritical );
    lua_register( L, "leaveCritical",   ::leaveCritical );

    if ( !init.empty() )
        init( L );

	boost::mutex::scoped_lock lock( luaTaskMutex );
	// There is expected to be "main" function which may not return.
	// If not there just will be an error message but the rest should work!
	// luaCommands.push_back( "main()" )
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

void LuaMachine::PD::stop()
{
	boost::mutex::scoped_lock lock( luaTaskMutex );
	do_stop = true;
}

void LuaMachine::PD::invokeCmd( const std::string & cmd )
{
	boost::mutex::scoped_lock lock( luaTaskMutex );
	do_stop = false;
	luaCommands.push( cmd );
	luaCond.notify_one();
}

bool LuaMachine::PD::isIdle()
{
	boost::mutex::scoped_lock lock( luaTaskMutex );
	unsigned int cnt = luaCommands.size();
	return (cnt == 0);
}

void LuaMachine::PD::terminate()
{
	{
		boost::mutex::scoped_lock lock( luaTaskMutex );
		do_terminate = true;
		luaCond.notify_one();
	}
	luaThread.join();
}








LuaMachine::LuaMachine( QXmppPeer * parent, TInit init )
    : QObject( parent )
{
	pd = new PD( this, init );
    pd->client = parent;

    connect( this,       SIGNAL(sigPrint(QString)), 
             this,       SLOT(slotPrint(QString)), 
             Qt::QueuedConnection );
    connect( this,       SIGNAL(sigStatus(QString)), 
             this,       SLOT(slotStatus(QString)), 
             Qt::QueuedConnection );
    connect( this,       SIGNAL(sigData(QString)),
             this,       SLOT(slotData(QString)),
             Qt::QueuedConnection );
    connect( pd->client, SIGNAL(textmsg(QString)),
             this,       SLOT(qxmppMessageReceived(QString)), 
             Qt::QueuedConnection );
}

LuaMachine::~LuaMachine()
{
	delete pd;
}

void LuaMachine::join()
{
	pd->luaThread.join();
}

void LuaMachine::invokeCmd( const std::string & cmd )
{
	pd->invokeCmd( cmd );
}

void LuaMachine::print( const QString & stri )
{
    emit sigPrint( stri );
}

void LuaMachine::status( const QString & stri )
{
    emit sigStatus( stri );
}

void LuaMachine::data( const QString & stri )
{
    emit sigData( stri );
}

void LuaMachine::qxmppMessageReceived( const QString & stri )
{
    QByteArray data = QByteArray::fromBase64( stri.toUtf8() );

    QDomDocument doc;
    QString errorMsg;
    bool res = doc.setContent( data, &errorMsg );
    if ( !res )
        return;
    QDomElement  root = doc.documentElement();
    if ( root.tagName() == "lua" )
    {
        QByteArray cmd = QByteArray::fromBase64( root.text().toUtf8() );
        invokeCmd( cmd.data() );
    }
}

void LuaMachine::slotPrint( const QString & stri )
{
    QByteArray data;
    QXmlStreamWriter stream( &data );
    stream.setAutoFormatting( false );

    stream.writeStartElement( "msg" );
    stream.writeAttribute( "type",   "print" );
    stream.writeCharacters( stri );
    stream.writeEndElement();

    data = data.toBase64();

    pd->client->sendMessage( data );
}

void LuaMachine::slotStatus( const QString & stri )
{
    QByteArray data;
    QXmlStreamWriter stream( &data );
    stream.setAutoFormatting( false );

    stream.writeStartElement( "msg" );
    stream.writeAttribute( "type",   "status" );
    stream.writeCharacters( stri );
    stream.writeEndElement();

    data = data.toBase64();

    pd->client->sendMessage( data );
}

void LuaMachine::slotData( const QString & stri )
{
    QByteArray data;
    QXmlStreamWriter stream( &data );
    stream.setAutoFormatting( false );

    stream.writeStartElement( "msg" );
    stream.writeAttribute( "type",   "data" );
    stream.writeCharacters( stri );
    stream.writeEndElement();

    data = data.toBase64();

    pd->client->sendMessage( data );
}




static int peer( lua_State * L )
{
	lua_pushstring( L, LuaMachine::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	LuaMachine::PD * pd = reinterpret_cast<LuaMachine::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	lua_pushlightuserdata( L, reinterpret_cast<void *>( pd->peer ) );
	return 1;
}

static int msleep( lua_State * L )
{
	int ms;
	if ( lua_gettop( L ) > 0 )
	{
	    ms = static_cast<int>( lua_tonumber( L, 1 ) );
	    if ( ms > LuaMachine::PD::MAX_SLEEP_INTERVAL )
	    	ms = LuaMachine::PD::MAX_SLEEP_INTERVAL;
	}
	else
		ms = 1;
	boost::this_thread::sleep( boost::posix_time::milliseconds( ms ) );
	return 0;
}

static int print( lua_State * L )
{
    if ( ( lua_gettop( L ) > 0 ) && ( ( lua_isstring( L, 1 ) ) || ( lua_isnumber( L, 1 ) ) ) )
    {
        QString stri = lua_tostring( L, 1 );
        lua_pushstring( L, LuaMachine::PD::LUA_PD_NAME.c_str() );
        lua_gettable( L, LUA_REGISTRYINDEX );
        LuaMachine::PD * pd = reinterpret_cast<LuaMachine::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
        lua_pop( L, 1 );
        pd->peer->print( stri );
        lua_pushboolean( L, 1 );
        return 1;
    }
    else
    {
        lua_pushnil( L );
        lua_pushstring( L, "String expected, got no arguments" );
        return 2;
    }
}

static int status( lua_State * L )
{
    if ( ( lua_gettop( L ) > 0 ) && ( ( lua_isstring( L, 1 ) ) || ( lua_isnumber( L, 1 ) ) ) )
    {
        QString stri = lua_tostring( L, 1 );
        lua_pushstring( L, LuaMachine::PD::LUA_PD_NAME.c_str() );
        lua_gettable( L, LUA_REGISTRYINDEX );
        LuaMachine::PD * pd = reinterpret_cast<LuaMachine::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
        lua_pop( L, 1 );
        pd->peer->status( stri );
        lua_pushboolean( L, 1 );
        return 1;
    }
    else
    {
        lua_pushnil( L );
        lua_pushstring( L, "String expected, got no arguments" );
        return 2;
    }
}

static int data( lua_State * L )
{
    if ( ( lua_gettop( L ) > 0 ) && ( ( lua_isstring( L, 1 ) ) || ( lua_isnumber( L, 1 ) ) ) )
    {
        QString stri = lua_tostring( L, 1 );
        lua_pushstring( L, LuaMachine::PD::LUA_PD_NAME.c_str() );
        lua_gettable( L, LUA_REGISTRYINDEX );
        LuaMachine::PD * pd = reinterpret_cast<LuaMachine::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
        lua_pop( L, 1 );
        pd->peer->data( stri );
        lua_pushboolean( L, 1 );
        return 1;
    }
    else
    {
        lua_pushnil( L );
        lua_pushstring( L, "String expected, got no arguments" );
        return 2;
    }
}

static int stop( lua_State * L )
{
	lua_pushstring( L, LuaMachine::PD::LUA_PD_NAME.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	LuaMachine::PD * pd = reinterpret_cast<LuaMachine::PD *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	pd->stop();
	return 0;
}

static int enterCritical( lua_State * L )
{
    lua_sethook( L, 0, LUA_MASKLINE, 0 );
    return 0;
}

static int leaveCritical( lua_State * L )
{
    lua_sethook( L, luaHook, LUA_MASKLINE, 0 );
    return 0;
}








