
#include "wgt.h"

#include "lua.hpp"
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

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

void Wgt::init( lua_State * L )
{

}

void Wgt::log( const QString & stri )
{
    emit sigLog( stri );
}


void Wgt::isConnected()
{
    bool res = irc->isConnected();
    log( QString( "%1" ).arg( res ? "yes" : "no" ) );
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












