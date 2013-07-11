
#include <QtGui>
#include "lua.hpp"
#include "bit.h"
#include <boost/bind.hpp>

#include "xmpp_io.h"
#include "xmpp_msg_pipe.h"
#include "xmpp_video.h"
#include "lua_machine.h"

#ifdef LUA_CTRL_BOARD
    #include "luactrlboard.h"
#endif

static void init( lua_State * L );


QXmppPeer * peer;

int main( int argc, char ** argv )
{
    QCoreApplication a( argc, argv );
    QSettings ini( "host.ini", QSettings::IniFormat );
    ini.beginGroup( "main" );
    QString selfJid  = ini.value( "selfJid",    "host@xmpp" ).toString();
    QString destJid  = ini.value( "destJid",    "client@xmpp" ).toString();
    QString password = ini.value( "password",   "12345" ).toString();
    QString host     = ini.value( "host",       QString() ).toString();
    int     port     = ini.value( "port",       -1 ).toInt();
    bool    tls      = ini.value( "tls",        true ).toBool();
    bool updateDest  = ini.value( "updateDest", true ).toBool();

    peer = new QXmppPeer();
    peer->setTarget( destJid, updateDest );
    peer->connect( selfJid, password, host, port, tls );

    QXmppMsgPipe * pipe = new QXmppMsgPipe( peer, 1 );

    QXmppVideo   * video = new QXmppVideo( peer );
    video->setTarget( destJid );

    LuaMachine  * lua = new LuaMachine( peer, boost::bind( init, _1 ) );

    int res = a.exec();
    return res;
}


static int isConnected( lua_State * L );
static int send( lua_State * L );
static int shutdown( lua_State * L );
static int process( lua_State * L );

static void init( lua_State * L )
{
    lua_register( L, "isConnected", ::isConnected );
    lua_register( L, "send",        ::send );
    lua_register( L, "shutdown",    ::shutdown );
    lua_register( L, "process",     ::process );

    luaopen_bit( L );
    #ifdef LUA_CTRL_BOARD
        // Board I2C io.
        luaopen_luactrlboard( L );
    #endif

    // Execute file.
    luaL_dofile( L, "./host.lua" );
}

static int isConnected( lua_State * L )
{
    bool res = peer->isConnected();
    lua_pushboolean( L, res ? 1 : 0 );
    return 1;
}

static int send( lua_State * L )
{
    int cnt = lua_gettop( L );
    for ( int i=1; i<=cnt; i++ )
    {
        if ( ( lua_isstring( L, i ) ) || ( lua_isnumber( L, i ) ) )
        {
            QString stri = lua_tostring( L, i );
            peer->sendMessage( stri );
        }
    }
    return 0;
}

static int shutdown( lua_State * L )
{
    bool res = QProcess::startDetached( "sudo halt -p" );
    lua_pushboolean( L, res ? 1 : 0 );
    return 1;
}

static int process( lua_State * L )
{
    if ( ( lua_gettop( L ) == 0 ) || ( !lua_isstring( L, 1 ) ) )
    {
        lua_pushnil( L );
        return 1;
    }
    QString cmd = lua_tostring( L, 1 );
    bool res = QProcess::startDetached( cmd );
    lua_pushboolean( L, res ? 1 : 0 );
    return 1;
}







