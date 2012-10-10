
#include "main_wnd.h"
#include "boost/bind.hpp"
#include "boost/bind/placeholders.hpp"

const std::string MainWnd::CONFIG_FILE = "client.ini";

MainWnd::MainWnd( QWidget * parent )
: QMainWindow( parent )
{
    ui.setupUi( this );
    connect( this, SIGNAL(sigLog(const QString &)), this, SLOT(slotLog(const QString &)), Qt::QueuedConnection );
    m_peer = new PeerQxmpp( CONFIG_FILE, boost::bind( &MainWnd::init, this, _1 ) );
}

MainWnd::~MainWnd()
{
	delete m_peer;
}

void MainWnd::slotLog( const QString & )
{
    // TODO: add text data putput here!!!
}

static int print( lua_State * L )
{
	lua_pushstring( L, "MainWnd" );
	lua_gettable( L, LUA_REGISTRYINDEX );
	MainWnd * mw = reinterpret_cast<MainWnd *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	return mw->print( L );
}

void MainWnd::init( lua_State * L )
{
	lua_pushlightuserdata( L, reinterpret_cast<void *>( this ) );
	lua_pushstring( L, "MainWnd" );
	lua_settable( L, LUA_REGISTRYINDEX );

    lua_pushcfunction( L, ::print );
    lua_pushstring( L, "print" );
    lua_settable( L, LUA_GLOBALSINDEX );
}

QIODevice * MainWnd::inFileHandler( const std::string & fileName )
{
    return 0;
}

void MainWnd::accFileHandler( const std::string & fileName, QIODevice * file )
{
    if ( file->isOpen() )
    	file->close();
}

int MainWnd::print( lua_State * L )
{
	int top = lua_gettop( L );
	for ( int i=1; i<=top; i++ )
	{
        std::string stri = lua_tostring( L, i );
        log( stri );
	}
	lua_settop( L, 0 );
	return 0;
}

void MainWnd::log( const std::string & stri )
{
	QString qstri = QString::fromStdString( stri );
    emit sigLog( qstri );
}






