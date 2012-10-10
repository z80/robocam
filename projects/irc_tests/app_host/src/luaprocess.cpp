
#include "luaprocess.h"
#include "lua.hpp"
#include <QtCore>

static const char META[] = "LUA_PROCESS_META";
static const char LIB_NAME[] = "luaprocess";

static int create( lua_State * L )
{
    int cnt = lua_gettop( L );
    QProcess * p = new QProcess();
    QProcess * * pp = reinterpret_cast< QProcess * * >( lua_newuserdata( L, sizeof( QProcess * ) ) );
    *pp = p;
    luaL_getmetatable( L, META );
    lua_setmetatable( L, -2 );

    p->setProcessChannelMode( QProcess::MergedChannels );
    return 1;
}

static int gc( lua_State * L )
{
    QProcess * p = *reinterpret_cast<QProcess * *>( lua_touserdata( L, 1 ) );
    if ( p )
        p->deleteLater();
    return 0;
}

static int start( lua_State * L )
{
    QProcess * p = *reinterpret_cast<QProcess * *>( lua_touserdata( L, 1 ) );
    QString app = lua_tostring( L, 2 );
    int n = lua_gettop( L );
    QStringList args;
    args.reserve( n - 2 );
    for ( int i=3; i<=n; i++ )
    {
    	QString arg = lua_tostring( L, i );
    	args << arg;
    }
    p->start( app, args );
    return 0;
}

static int waitForFinished( lua_State * L )
{
    QProcess * p = *reinterpret_cast<QProcess * *>( lua_touserdata( L, 1 ) );
    bool res = p->waitForFinished();
    lua_pushboolean( L, res ? 1 : 0 );
	return 1;
}

static int waitForStarted( lua_State * L )
{
    QProcess * p = *reinterpret_cast<QProcess * *>( lua_touserdata( L, 1 ) );
    bool res = p->waitForStarted();
    lua_pushboolean( L, res ? 1 : 0 );
	return 1;
}

static int readAll( lua_State * L )
{
    QProcess * p = *reinterpret_cast<QProcess * *>( lua_touserdata( L, 1 ) );
    QByteArray res = p->readAll();
    if ( res.size() > 0 )
    	lua_pushstring( L, res.data() );
    else
    	lua_pushnil( L );
    return 1;
}






static const struct luaL_reg META_FUNCTIONS[] = {
	{ "__gc",            gc },
    { "start",           start },
    { "waitForFinished", waitForFinished },
    { "waitForStarted",  waitForStarted },
    { "readAll",         readAll },

    { NULL,           NULL },
};

static void createMeta( lua_State * L )
{
	int top = lua_gettop( L );
    luaL_newmetatable( L, META );  // create new metatable for file handles
    // file methods
    lua_pushliteral( L, "__index" );
    lua_pushvalue( L, -2 );  // push metatable
    lua_rawset( L, -3 );       // metatable.__index = metatable
    luaL_register( L, NULL, META_FUNCTIONS );
    // ������� ����.
    lua_settop( L, top );
}

static const struct luaL_reg FUNCTIONS[] = {
	{ "create",  create },
	{ NULL, NULL },
};

static void registerFunctions( lua_State * L )
{
    luaL_register( L, LIB_NAME, FUNCTIONS );
}

extern "C" int luaopen_luaprocess( lua_State * L )
{
    createMeta( L );
    registerFunctions( L );
    return 0;
}



