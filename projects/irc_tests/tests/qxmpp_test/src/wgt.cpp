
#include "wgt.h"

#include "lua.hpp"
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

const std::string Wgt::WGT_ID = "WGT";

Wgt::Wgt( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
    connect( ui.connect,        SIGNAL(clicked()), this, SLOT(connectHost()) );
    connect( ui.registerClient, SIGNAL(clicked()), this, SLOT(registerClient()) );
    connect( ui.send,           SIGNAL(clicked()), this, SLOT(send()) );
    connect( ui.sendFile,       SIGNAL(clicked()), this, SLOT(sendFile()) );
    connect( ui.status,         SIGNAL(clicked()), this, SLOT(status()) );
    connect( ui.clear,          SIGNAL(clicked()), this, SLOT(clear()) );

    connect( this, SIGNAL(sigLog(const QString &)), this, SLOT(slotLog(const QString &)), Qt::QueuedConnection );

    xmpp = new PeerQxmpp( "./config.ini", boost::bind( &Wgt::init, this, _1 ) );
    xmpp->setInFileHandler( boost::bind<QIODevice *>( &Wgt::inFileHandler, this, _1 ) );
    xmpp->setAccFileHandler( boost::bind( &Wgt::accFileHandler, this, _1, _2 ) );
}

Wgt::~Wgt()
{
}

static int print( lua_State * L )
{
	lua_pushstring( L, Wgt::WGT_ID.c_str() );
	lua_gettable( L, LUA_REGISTRYINDEX );
	Wgt * w = reinterpret_cast<Wgt *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	int res = w->print( L );
    return res;
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
		log( stri.toStdString() );
	}
    return 0;
}

void Wgt::log( const std::string & stri )
{
    emit sigLog( QString::fromStdString( stri ) );
}

void Wgt::connectHost()
{
}

void Wgt::registerClient()
{
	//std::string host     = ui.host->text().toStdString();
	//int         port     = ui.port->value();
	//std::string nick     = ui.nick->text().toStdString();
	//std::string password = ui.password->text().toStdString();
	//xmpp.setHost( host, port );
	//xmpp.setNick( nick, password );
	//bool res = xmpp.registerClient();
	//log( res ? "succeeded" : "failed" );
 //   if ( !res )
 //   	log( xmpp.lastError() );
}

void Wgt::send()
{
	std::string stri = ui.msg->text().toStdString();
	xmpp->send( stri );
}

void Wgt::sendFile()
{
	QString fileName = QFileDialog::getOpenFileName( this,
	     tr("Open File"), "", "" );
	if ( fileName.length() > 0 )
	{
		std::string to   = ui.to->text().toStdString();
        QFile * f = new QFile( fileName );
        if ( f->open( QIODevice::ReadOnly ) )
        {
            xmpp->sendFile( fileName.toStdString(), f );
        }
        else
            log( "ERROR: failed to open file!" );
	}
}

void Wgt::status()
{
    bool conn   = xmpp->isConnected();
    log( conn ?   "connected" : "NOT connected" );
}

void Wgt::clear()
{
    ui.log->clear();
}

void Wgt::slotLog( const QString & stri )
{
	ui.log->appendPlainText( stri );
}

void Wgt::messageHandler( const std::string & client, const std::string & stri )
{
	QString msg = QString( "%1: \"%2\"" ).arg( client.c_str() ).arg( stri.c_str() );
    std::string smsg = msg.toStdString();
    log( smsg );
}

void Wgt::logHandler( const std::string & stri )
{
	log( stri );
}

QIODevice * Wgt::inFileHandler( const std::string & fileName )
{
    QString msg = QString( "Incoming file: %1" ).arg( fileName.c_str() );
    std::string smsg = msg.toStdString();
    log( smsg );
    QBuffer * b = new QBuffer();
    b->open( QIODevice::WriteOnly );
    return b;
}

void Wgt::accFileHandler( const std::string & fileName, QIODevice * device )
{
    QString msg = QString( "file \"%1\" finished, size: " ).arg( fileName.c_str() ).arg( device->size() );
    std::string smsg = msg.toStdString();
    log( smsg );
}






