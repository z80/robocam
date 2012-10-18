
#include "luamcuctrl.h"
#include "mcu_ctrl.h"

static const char META[] = "LUA_MCUCTRL_META";
static const char LIB_NAME[] = "luamcuctrl";

static int create( lua_State * L )
{
    int cnt = lua_gettop( L );
    McuCtrl * io = new McuCtrl();
    McuCtrl * * p = reinterpret_cast< McuCtrl * * >( lua_newuserdata( L, sizeof( McuCtrl * ) ) );
    *p = dynamic_cast<McuCtrl *>( io );
    luaL_getmetatable( L, META );
    lua_setmetatable( L, -2 );
    return 1;
}

static int gc( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    if ( io )
        delete io;
    return 0;
}

static int self( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    lua_pushlightuserdata( L, reinterpret_cast< void * >(io) );
    return 1;
}

static int open( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    bool res;
    if ( ( lua_gettop( L ) > 1 ) && ( lua_type( L, 2 ) == LUA_TSTRING ) )
    {
        std::string arg = lua_tostring( L, 2 );
        res = io->open( arg );
    }
    else
        res = io->open();
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int close( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    io->close();
    return 0;
}

static int isOpen( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    bool res = io->isOpen();
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int write( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    std::string stri = lua_tostring( L, 2 );
    bool res = io->write( stri );
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int read( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	std::string stri;
    bool res = io->read( stri );
    if ( res )
        lua_pushstring( L, stri.c_str() );
    else
    	lua_pushnil( L );
    return 1;
}

static int led( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	bool en = ( lua_toboolean( L , 2 ) > 0 );

    bool res = io->led( en );
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int powerOffReset( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	bool res = io->powerOffReset();
	lua_pushboolean( L, ( res ) ? 1 : 0 );
	return 1;
}

static int powerConfig( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	int onFirst = static_cast<int>( lua_tonumber( L, 2 ) );
	int onRegular = static_cast<int>( lua_tonumber( L, 3 ) );
	int off = static_cast<int>( lua_tonumber( L, 4 ) );
    bool res = io->powerConfig( onFirst, onRegular, off );
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int powerEn( lua_State * L )
{
    McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    bool en = static_cast<int>( lua_toboolean( L, 2 ) > 0 );
    bool res = io->powerEn( en );
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int motoConfig( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	bool en = ( lua_toboolean( L, 2 ) > 0 );
	int offSec = static_cast<int>( lua_tonumber( L, 3 ) );
	bool res = io->motoConfig( en, offSec );
	lua_pushboolean( L, ( res ) ? 1 : 0 );
	return 1;
}

static int moto( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	bool moto1 = ( lua_toboolean( L, 2 ) > 0 );
	bool moto2 = ( lua_toboolean( L, 3 ) > 0 );
	bool moto3 = ( lua_toboolean( L, 4 ) > 0 );
	bool moto4 = ( lua_toboolean( L, 5 ) > 0 );
	bool res = io->moto( moto1, moto2, moto3, moto4 );
	lua_pushboolean( L, res ? 1 : 0 );
	return 1;
}

static int motoReset( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	bool res = io->motoReset();
	lua_pushboolean( L, ( res ) ? 1 : 0 );
	return 1;
}

static int adcConfig( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
    bool en = ( lua_toboolean( L, 2 ) > 0 );
    bool res = io->adcConfig( en );
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int adc( lua_State * L )
{
	McuCtrl * io = *reinterpret_cast<McuCtrl * *>( lua_touserdata( L, 1 ) );
	int val1, val2;
	bool res = io->adc( val1, val2 );
	lua_pushboolean( L, ( res ) ? 1 : 0 );
	if ( res )
	{
		lua_pushnumber( L, static_cast<lua_Number>( val1 ) );
		lua_pushnumber( L, static_cast<lua_Number>( val2 ) );
		return 3;
	}
	return 1;
}

static const struct luaL_reg META_FUNCTIONS[] = {
	{ "__gc",          gc },
    { "pointer",       self },
    // Open/close routines
    { "open",          open },
    { "close",         close },
    { "isOpen",        isOpen },
    // The lowest possible level
    { "write",         write },
    { "read",          read },
    { "led",           led },
    { "powerConfig",   powerConfig },
    { "powerOffReset", powerOffReset },
    { "powerEn",       powerEn },
    { "motoConfig",    motoConfig },
    { "moto",          moto },
    { "motoReset",     motoReset },
    { "adcConfig",     adcConfig },
    { "adc",           adc },

    { NULL,            NULL },
};

static void createMeta( lua_State * L )
{
    luaL_newmetatable( L, META );  // create new metatable for file handles
    // file methods
    lua_pushliteral( L, "__index" );
    lua_pushvalue( L, -2 );  // push metatable
    lua_rawset( L, -3 );       // metatable.__index = metatable
    luaL_register( L, NULL, META_FUNCTIONS );
    // ������� ����.
    lua_pop( L, lua_gettop( L ) );
}

static const struct luaL_reg FUNCTIONS[] = {
	{ "create",  create }, 
	{ NULL, NULL },
};

static void registerFunctions( lua_State * L )
{
    luaL_register( L, LIB_NAME, FUNCTIONS );
}

extern "C" int DECLSPEC luaopen_luamcuctrl( lua_State * L )
{
    createMeta( L );
    registerFunctions( L );
    return 0;
}





