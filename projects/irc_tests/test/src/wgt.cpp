
#include "wgt.h"

#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

Wgt::Wgt( QWidget * parent )
: QWidget( parent )
{
    ui.setupUi( this );
    connect( ui.connect,      SIGNAL(clicked()), this, SLOT(connectHost()) );
    connect( ui.join,         SIGNAL(clicked()), this, SLOT(join()) );
    connect( ui.channelList,  SIGNAL(clicked()), this, SLOT(channelList()) );
    connect( ui.clientList,   SIGNAL(clicked()), this, SLOT(clientList()) );
    connect( ui.send,         SIGNAL(clicked()), this, SLOT(send()) );
    connect( ui.dccRequest,   SIGNAL(clicked()), this, SLOT(dccRequest()) );
    connect( ui.dccSend,      SIGNAL(clicked()), this, SLOT(dccSend()) );
    connect( ui.dccFile,      SIGNAL(clicked()), this, SLOT(dccFile()) );
    connect( ui.isConnected,  SIGNAL(clicked()), this, SLOT(isConnected()) );
    connect( ui.isJoined,     SIGNAL(clicked()), this, SLOT(isJoined()) );
    connect( ui.status,       SIGNAL(clicked()), this, SLOT(status()) );
    connect( ui.clear,        SIGNAL(clicked()), this, SLOT(clear()) );

    connect( this, SIGNAL(sigLog(const QString &)), this, SLOT(slotLog(const QString &)) );

    irc.setMessageHandler( boost::bind( &Wgt::messageHandler, this, _1, _2 ) );
    irc.setDccHandler( boost::bind( &Wgt::dccHandler, this, _1 ) );
    irc.setDccFileHandler( boost::bind( &Wgt::dccFileHandler, this, _1, _2 ) );
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

void Wgt::send()
{
	std::string to   = ui.to->text().toStdString();
	std::string stri = ui.msg->text().toStdString();
	irc.send( to, stri );
}

void Wgt::dccRequest()
{
	std::string to   = ui.to->text().toStdString();
	bool res = irc.requestDcc( to );
    log( QString( "%1" ).arg( res ? "succeeded" : "failed" ) );
    if ( !res )
    	log( QString::fromStdString( irc.lastError() ) );

}

void Wgt::dccSend()
{
	std::string stri = ui.msg->text().toStdString();
	irc.sendDcc( stri );
}

void Wgt::dccFile()
{
	QString fileName = QFileDialog::getOpenFileName( this,
	     tr("Open File"), "", "" );
	if ( fileName.length() > 0 )
	{
		std::string to   = ui.to->text().toStdString();
		std::string f = fileName.toStdString();
		bool res = irc.sendDccFile( to, f );
		log( QString( "Sending \'%1\' to %2" ).arg( f.c_str() ).arg( to.c_str() ) );
	}
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

void Wgt::slotLog( const QString & stri )
{
	log( stri );
}

void Wgt::messageHandler( const std::string & client, const std::string & stri )
{
	QString msg = QString( "%1: \"%2\"" ).arg( client.c_str() ).arg( stri.c_str() );
	emit sigLog( msg );
}

void Wgt::dccHandler( const std::string & stri )
{
	QString msg = QString( "DCC message: \"%1\"" ).arg( stri.c_str() );
	emit sigLog( msg );
}

void Wgt::dccFileHandler( const std::string & fileName, const std::basic_string<char> & fileData )
{
	QString msg = QString( "File accepted: \"%1\", size = %2" ).arg( fileName.c_str() ).arg( fileData.size() );
	emit sigLog( msg );
}






