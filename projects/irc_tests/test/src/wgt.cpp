
#include "wgt.h"

Wgt::Wgt( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
    connect( ui.connect,      SIGNAL(clicked()), this, SLOT(connectHost()) );
    connect( ui.join,         SIGNAL(clicked()), this, SLOT(join()) );
    connect( ui.channelList,  SIGNAL(clicked()), this, SLOT(channelList()) );
    connect( ui.clientList,   SIGNAL(clicked()), this, SLOT(clientList()) );
    connect( ui.isConnected,  SIGNAL(clicked()), this, SLOT(isConnected()) );
    connect( ui.isJoined,     SIGNAL(clicked()), this, SLOT(isJoined()) );
    connect( ui.listChannels, SIGNAL(clicked()), this, SLOT(listChannels()) );
    connect( ui.listClients,  SIGNAL(clicked()), this, SLOT(listClients()) );
    connect( ui.status,       SIGNAL(clicked()), this, SLOT(status()) );
    connect( ui.clear,        SIGNAL(clicked()), this, SLOT(clear()) );
}

Wgt::~Wgt()
{
}

void Wgt::log( const QString & stri )
{
    ui.log->appendPlainText( stri );
}

void Wgt::connectHost()
{
	std::string host = ui.host->text().toStdString();
	int         port = ui.port->value();
	std::string nick = ui.nick->text().toStdString();
	irc.setHost( host, port );
	irc.setNick( nick );
	bool res = irc.connect();
	log( QString( "%1" ).arg( res ? "succeeded" : "failed" ) );
    if ( !res )
    	log( QString::fromStdString( irc.lastError() ) );
}

void Wgt::join()
{
	std::string channel = ui.channel->text().toStdString();
	bool res = irc.join( channel );
	log( QString( "%1" ).arg( res ? "succeeded" : "failed" ) );
    if ( !res )
    	log( QString::fromStdString( irc.lastError() ) );
}

void Wgt::channelList()
{
    std::list<std::string> l;
    bool res = irc.channels( l );
    log( QString( "%1" ).arg( res ? "succeeded" : "failed" ) );
    if ( !res )
    	log( QString::fromStdString( irc.lastError() ) );
    for ( std::list<std::string>::const_iterator i=l.begin(); i!=l.end(); i++ )
    	log( QString::fromStdString( *i ) );
}

void Wgt::clientList()
{
	std::string channel = ui.channel->text().toStdString();
    std::list<std::string> l;
    bool res = irc.clients( channel, l );
    log( QString( "%1" ).arg( res ? "succeeded" : "failed" ) );
    if ( !res )
    	log( QString::fromStdString( irc.lastError() ) );
    for ( std::list<std::string>::const_iterator i=l.begin(); i!=l.end(); i++ )
    	log( QString::fromStdString( *i ) );
}

void Wgt::isConnected()
{
    bool res = irc.isConnected();
    log( QString( "%1" ).arg( res ? "yes" : "no" ) );
    if ( !res )
    	log( QString::fromStdString( irc.lastError() ) );
    if ( res )
    {
    	irc.ircRawCmd( "CJOIN #chan1" );
    	irc.ircRawCmd( "CJOIN #chan2" );
    }
}

void Wgt::isJoined()
{
    bool res = irc.isJoined();
    log( QString( "%1" ).arg( res ? "yes" : "no" ) );
    if ( !res )
    	log( QString::fromStdString( irc.lastError() ) );
}

void Wgt::listChannels()
{
}

void Wgt::listClients()
{
}

void Wgt::status()
{
    bool conn   = irc.isConnected();
    bool joined = irc.isJoined();
    log( QString( "%1" ).arg( conn ?   "connected" : "NOT connected" ) );
    log( QString( "%1" ).arg( joined ? "joined"    : "NOT joined" ) );
}

void Wgt::clear()
{
    ui.log->clear();
}







