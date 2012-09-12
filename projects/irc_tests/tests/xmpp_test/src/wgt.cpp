
#include "wgt.h"

#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>

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

    xmpp.setMessageHandler( boost::bind( &Wgt::messageHandler, this, _1, _2 ) );
    xmpp.setLogHandler( boost::bind( &Wgt::logHandler, this, _1 ) );
}

Wgt::~Wgt()
{
}

void Wgt::log( const std::string & stri )
{
    emit sigLog( QString::fromStdString( stri ) );
}

void Wgt::connectHost()
{
	std::string host     = ui.host->text().toStdString();
	int         port     = ui.port->value();
	std::string nick     = ui.nick->text().toStdString();
	std::string password = ui.password->text().toStdString();
	xmpp.setHost( host, port );
	xmpp.setNick( nick, password );
	bool res = xmpp.connect();
	log( res ? "succeeded" : "failed" );
    if ( !res )
    	log( xmpp.lastError() );
}

void Wgt::registerClient()
{
	std::string host     = ui.host->text().toStdString();
	int         port     = ui.port->value();
	std::string nick     = ui.nick->text().toStdString();
	std::string password = ui.password->text().toStdString();
	xmpp.setHost( host, port );
	xmpp.setNick( nick, password );
	bool res = xmpp.registerClient();
	log( res ? "succeeded" : "failed" );
    if ( !res )
    	log( xmpp.lastError() );
}

void Wgt::send()
{
	std::string to   = ui.to->text().toStdString();
	std::string stri = ui.msg->text().toStdString();
	xmpp.send( to, stri );
}

void Wgt::sendFile()
{
	QString fileName = QFileDialog::getOpenFileName( this,
	     tr("Open File"), "", "" );
	if ( fileName.length() > 0 )
	{
		std::string to   = ui.to->text().toStdString();
		std::string f = fileName.toStdString();
		//bool res = xmpp.sendDccFile( to, f );
		//log( QString( "Sending \'%1\' to %2" ).arg( f.c_str() ).arg( to.c_str() ) );
	}
}

void Wgt::status()
{
    bool conn   = xmpp.isConnected();
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






