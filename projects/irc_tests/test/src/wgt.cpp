
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
	irc.connect();
}

void Wgt::join()
{
	std::string channel = ui.channel->text().toStdString();
	irc.join( channel );
}

void Wgt::channelList()
{
    irc.enumChannels();
}

void Wgt::clientList()
{
    irc.enumClients();
}

void Wgt::isConnected()
{
    bool res = irc.isConnected();
    log( QString( "%1" ).arg( res ? "yes" : "no" ) );
    if ( res )
    {
    	irc.ircRawCmd( "CJOIN chan1" );
    	irc.ircRawCmd( "CJOIN chan2" );
    }
}

void Wgt::isJoined()
{
    bool res = irc.isJoined();
    log( QString( "%1" ).arg( res ? "yes" : "no" ) );
}

void Wgt::listChannels()
{
    const std::list<std::string> & l = irc.channels();
    for ( std::list<std::string>::const_iterator i=l.begin(); i!=l.end(); i++ )
    {
    	log( QString::fromStdString( *i ) );
	}
}

void Wgt::listClients()
{
    const std::list<std::string> & l = irc.clients();
    for ( std::list<std::string>::const_iterator i=l.begin(); i!=l.end(); i++ )
    {
    	log( QString::fromStdString( *i ) );
	}
}

void Wgt::status()
{
    bool conn   = irc.isConnected();
    bool joined = irc.isJoined();
}

void Wgt::clear()
{
    ui.log->clear();
}







