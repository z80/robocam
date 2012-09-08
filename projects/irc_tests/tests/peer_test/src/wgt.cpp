
#include "wgt.h"

#include "lua.hpp"
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

const std::string Wgt::WGT_ID = "WGT";

Wgt::Wgt( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
    connect( ui.send,         SIGNAL(clicked()), this, SLOT(send()) );
    connect( ui.invoke,       SIGNAL(clicked()), this, SLOT(invoke()) );
    connect( ui.isConnected,  SIGNAL(clicked()), this, SLOT(isConnected()) );
    connect( ui.clear,        SIGNAL(clicked()), this, SLOT(clear()) );

    connect( this, SIGNAL(sigLog(const QString &)), this, SLOT(slotLog(const QString &)) );

    irc = new PeerIrc( "./config.ini", boost::bind( &Wgt::init, this, _1 ) );
}

Wgt::~Wgt()
{
	delete irc;
}

static int print( lua_State * L )
{
	lua_pushstring( L, Wgt::WGT_ID.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	Wgt * w = reinterpret_cast<Wgt *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	w->print( L );
}

void Wgt::init( lua_State * L )
{
	lua_pushstring( L, Wgt::WGT_ID.c_str() );
	lua_pushlightuserdata( L, this );
	lua_settable( L, LUA_REGISTRYINDEX );

	lua_register( L, "print", ::print );
}

int Wgt::print( lua_State * L )
{
	int n = lua_gettop( L );
	for ( int i=1; i<=n; i++ )
	{
		QString stri = lua_tostring( L, i );
		log( stri );
	}
}

void Wgt::log( const QString & stri )
{
    emit sigLog( stri );
}


void Wgt::isConnected()
{
    bool res = irc->isConnected();
    log( QString( "%1" ).arg( res ? "yes" : "no" ) );
    if ( !res )
    	log( QString( "%1" ).arg( irc->lastError().c_str() ) );
}

void Wgt::send()
{
	std::string stri = ui.msg->text().toStdString();
	irc->send( stri );
}

void Wgt::invoke()
{
	std::string stri = ui.msg->text().toStdString();
	irc->invokeCmd( stri );
}

void Wgt::clear()
{
    ui.log->clear();
}

void Wgt::slotLog( const QString & stri )
{
	ui.log->appendPlainText( stri );
}












