
#include <QtGui>
#include "lua.hpp"
#include "peer_qxmpp.h"
#include "luactrlboard.h"
#include "luaprocess.h"
#include "fsw_process.h"
#include <boost/bind.hpp>

bool g_acceptFiles = false;
static const char config[] = "host.ini";

static void init( lua_State * L );
static int setAcceptFiles( lua_State * L );
static QIODevice * inFileHandler(const std::string &);
static void accFileHandler(const std::string &, QIODevice *);


int main( int argc, char ** argv )
{
    QCoreApplication a( argc, argv );
	PeerQxmpp peer( config, boost::bind( init, _1 ) );
	peer.setInFileHandler( boost::bind<QIODevice *>( inFileHandler, _1 ) );
	peer.setAccFileHandler( boost::bind( accFileHandler, _1, _2 ) );

	int res = a.exec();
    return res;
}


static void init( lua_State * L )
{
	// Board USB io.
    luaopen_luactrlboard( L );
	// QProcess management.
	luaopen_luaprocess( L );
	// FswProcess management.
	luaopen_luafsw( L );
	// File acceptance function registration.
	lua_register( L, "setAcceptFiles", ::setAcceptFiles );
	// Execute file.
	luaL_dofile( L, "./host.lua" );
}

static int setAcceptFiles( lua_State * L )
{
	bool en = (lua_toboolean( L, 1 ) > 0);
	g_acceptFiles = en;
	return 0;
}

static QIODevice * inFileHandler(const std::string & fname )
{
	if ( !g_acceptFiles )
		return 0;
	QFile * file = new QFile( QString::fromStdString( fname ) );
	if ( !file->open( QIODevice::WriteOnly ) )
	{
		file->deleteLater();
		return 0;
	}
	return file;
}


static void accFileHandler(const std::string & fname, QIODevice * file )
{
	if ( file->isOpen() )
		file->close();
}





