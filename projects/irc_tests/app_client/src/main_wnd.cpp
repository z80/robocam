
#include "main_wnd.h"
#include "lua.hpp"
#include "boost/bind.hpp"
#include "boost/bind/placeholders.hpp"

const std::string MainWnd::CONFIG_FILE = "client.ini";
const int         MainWnd::LOG_MAX     = 256;
const int         MainWnd::MOTO_TIME_MAX = 1000;

MainWnd::MainWnd( QWidget * parent )
: QMainWindow( parent )
{
    ui.setupUi( this );
    connect( this, SIGNAL(sigLog(const QString &)), this, SLOT(slotLog(const QString &)), Qt::QueuedConnection );
    m_peer = new PeerQxmpp( CONFIG_FILE, boost::bind( &MainWnd::init, this, _1 ) );

    // Connecting GUI slots.

}

MainWnd::~MainWnd()
{
	delete m_peer;
}

void MainWnd::slotLog( const QString & stri )
{
	while ( m_logList.size() > LOG_MAX )
		m_logList.pop_front();
	m_logList.push_back( stri );
	ui.log->clear();
    for ( QStringList::const_iterator it=m_logList.begin(); it!=m_logList.end(); it++ )
    	ui.log->append( *it );
    ui.log->verticalScrollBar()->setSliderPosition( ui.log->verticalScrollBar()->maximum() );
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

void MainWnd::slotSend()
{
    std::string stri = ui.cmd->toPlainText().toUtf8();
    m_peer->send( stri );
}

void MainWnd::slotClear()
{
    ui.log->clear();
    m_logList.clear();
}

void MainWnd::slotImage()
{
    const std::string cmd = "send( image() )";
    m_peer->send( cmd );
}

void MainWnd::slotVoltages()
{


}

void MainWnd::slotLight()
{

}

void MainWnd::slotMotoEn()
{

}

void MainWnd::slotMoto()
{

}

void MainWnd::slotTimeout()
{

}






