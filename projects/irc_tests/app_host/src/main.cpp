
#include <QtCore>
#include "lua.hpp"
#include "peer_qxmpp.h"
#include "luamcuctrl.h"
#include <boost/bind.hpp>

static void init( lua_State * L );
static const char config[] = "config.ini";

int main( int argc, char ** argv )
{
	QCoreApplication a( argc, argv );
	PeerQxmpp peer( config, boost::bind( init, _1 ) );

	int res = a.exec();
    return res;
}


static void init( lua_State * L )
{
	// Board USB io.
	luaopen_luamcuctrl( L );
}

