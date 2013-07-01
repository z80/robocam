
#include <QtGui>
#include "lua.hpp"
#include <boost/bind.hpp>

#include "xmpp_io.h"
#include "xmpp_msg_pipe.h"
#include "xmpp_video.h"
#include "lua_machine.h"

#ifdef LUA_CTRL_BOARD
    #include "luactrlboard.h"
#endif

static void init( lua_State * L );

int main( int argc, char ** argv )
{
    QCoreApplication a( argc, argv );
    QSettings ini( "host.ini", QSettings::IniFormat );
    QString selfJid  = ini.value( "selfJid",  "host@xmpp" ).toString();
    QString destJid  = ini.value( "destJid",  "client@xmpp" ).toString();
    QString password = ini.value( "password", "12345" ).toString();
    QString host     = ini.value( "host",     QString() ).toString();
    int     port     = ini.value( "port",     -1 ).toInt();
    bool    tls      = ini.value( "tls",      true ).toBool();

    QXmppPeer peer;
    peer.connect( selfJid, password, host, port, tls );
    QXmppMsgPipe pipe( &peer, 1 );
    LuaMachine   lua( &peer, boost::bind( init, _1 ) );

    int res = a.exec();
    return res;
}


static void init( lua_State * L )
{
    #ifdef LUA_CTRL_BOARD
        // Board I2C io.
        luaopen_luactrlboard( L );
    #endif
    // Execute file.
    luaL_dofile( L, "./host.lua" );
}






