
#include "luactrlboard.h"
#include "ctrlboard.h"
#include <string>

class CtrlBoardIo: public CtrlBoard
{
public:
    CtrlBoardIo() {}
    ~CtrlBoardIo() {}

    std::basic_string<unsigned char> data;
};

static const char META[] = "LUA_CTRLBOARD_META";
static const char LIB_NAME[] = "luactrlboard";

static int create( lua_State * L )
{
    int cnt = lua_gettop( L );
    CtrlBoardIo * io = new CtrlBoardIo();
    CtrlBoardIo * * p = reinterpret_cast< CtrlBoardIo * * >( lua_newuserdata( L, sizeof( CtrlBoardIo * ) ) );
    *p = dynamic_cast<CtrlBoardIo *>( io );
    luaL_getmetatable( L, META );
    lua_setmetatable( L, -2 );
    return 1;
}

static int gc( lua_State * L )
{
    CtrlBoardIo * io = *reinterpret_cast<CtrlBoardIo * *>( lua_touserdata( L, 1 ) );
    if ( io )
        delete io;
    return 0;
}

static int self( lua_State * L )
{
    CtrlBoardIo * io = *reinterpret_cast<CtrlBoardIo * *>( lua_touserdata( L, 1 ) );
    lua_pushlightuserdata( L, reinterpret_cast< void * >(io) );
    return 1;
}

static int open( lua_State * L )
{
    CtrlBoardIo * io = *reinterpret_cast<CtrlBoardIo * *>( lua_touserdata( L, 1 ) );
    bool res = io->open();
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int close( lua_State * L )
{
    CtrlBoardIo * io = *reinterpret_cast<CtrlBoardIo * *>( lua_touserdata( L, 1 ) );
    io->close();
    return 0;
}

static int isOpen( lua_State * L )
{
    CtrlBoardIo * io = *reinterpret_cast<CtrlBoardIo * *>( lua_touserdata( L, 1 ) );
    bool res = io->isOpen();
    lua_pushboolean( L, ( res ) ? 1 : 0 );
    return 1;
}

static int write( lua_State * L )
{
    CtrlBoardIo * io = *reinterpret_cast<CtrlBoardIo * *>( lua_touserdata( L, 1 ) );
    unsigned char addr = static_cast<unsigned char>( lua_tonumber( L, 2 ) );
    if ( !lua_istable( L, 3 ) )
    {
        lua_pushboolean( L, 0 );
        return 1;
    }
    int ind = 1;
    while ( true )
    {
        lua_pushnumber( L, static_cast<lua_Number>( ind ) );
        lua_gettable( L, -2 );
        if ( lua_isnil( L, -1 ) )
            break;
        // pop number from stack.
        lua_pop( L, 1 );
        ind++;
    }
    // pop nil from stack.
    lua_pop( L, 1 );
    io->data.resize( ind );
    for ( int i=0; i<ind; i++ )
    {
        lua_pushnumber( L, i+1 );
        lua_gettable( L, -2 );
        io->data[i] = static_cast<unsigned char>( lua_tonumber( L, -1 ) );
        lua_pop( L, 1 );
    }
    bool res = io->write( addr, io->data.data(), ind );
    lua_pushboolean( L, res ? 1 : 0 );
    return 1;
}

static int read( lua_State * L )
{
    CtrlBoardIo * io = *reinterpret_cast<CtrlBoardIo * *>( lua_touserdata( L, 1 ) );
    unsigned char addr = static_cast<unsigned char>( lua_tonumber( L, 2 ) );
    int cnt = static_cast<int>( lua_tonumber( L, 3 ) );
    io->data.resize( cnt );
    bool res = io->read( addr, const_cast<unsigned char *>( io->data.data() ), cnt );
    if ( !res )
    {
        lua_pushboolean( L, 0 );
        return 1;
    }
    lua_newtable( L );
    for ( int i=0; i<cnt; i++ )
    {
        lua_pushnumber( L, static_cast<lua_Number>( i+1 ) );
        lua_pushnumber( L, io->data[i] );
        lua_settable( L, -3 );
    }
    return 1;
}


static const struct luaL_reg META_FUNCTIONS[] = {
    { "pointer",       self },
    // Open/close routines
    { "open",          open },
    { "close",         close },
    { "isOpen",        isOpen },
    // The lowest possible level
    { "write",         write },
    { "read",          read },

    { NULL,            NULL },
};

static void createMeta( lua_State * L )
{
    int top = lua_gettop( L );
    luaL_newmetatable( L, META );  // create new metatable for file handles
    // file methods
    lua_pushliteral( L, "__index" );
    lua_pushvalue( L, -2 );  // push metatable
    lua_rawset( L, -3 );     // metatable.__index = metatable

    lua_pushliteral( L, "__gc" );
    lua_pushcfunction( L, gc );
    lua_rawset( L, -3 );

    luaL_register( L, NULL, META_FUNCTIONS );
    // Очищаем стек.
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

extern "C" int DECLSPEC luaopen_luactrlboard( lua_State * L )
{
    createMeta( L );
    registerFunctions( L );
    return 0;
}





