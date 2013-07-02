
#include "main_wnd.h"

#include "lua.hpp"
#include "boost/bind.hpp"
#include "boost/bind/placeholders.hpp"

const std::string MainWnd::CONFIG_FILE = "./client.ini";
const int         MainWnd::LOG_MAX     = 256;
const int         MainWnd::MOTO_TIME_MAX = 1000;
const int         MainWnd::MOTO1         = 1;
const int         MainWnd::MOTO2         = 2;
const int         MainWnd::MOTO3         = 4;
const int         MainWnd::MOTO4         = 8;

MainWnd::MainWnd( QWidget * parent )
: QMainWindow( parent )
{
    ui.setupUi( this );
    connect( this, SIGNAL(sigLog(const QString &)), this, SLOT(slotLog(const QString &)), Qt::QueuedConnection );
    connect( ui.console, SIGNAL(line_validate(const QString &)), this, SLOT(slotSend(const QString &)), Qt::QueuedConnection );

    m_peer = new QXmppPeer( this );
    connect( m_peer, SIGNAL(log(QString)), this, SLOT(slotLog(QString)) );

    m_video = new QXmppVideo( m_peer );
    // It also connects frameReady() signal to an appropriate slot.
    ui.view->setVideo( m_video );
    this->setCentralWidget( ui.view );

    QSettings ini( CONFIG_FILE.c_str(), QSettings::IniFormat );
    ini.beginGroup( "main" );
    QString selfJid  = ini.value( "selfJid",    "client@xmpp" ).toString();
    QString destJid  = ini.value( "destJid",    "host@xmpp" ).toString();
    QString password = ini.value( "password",   "12345" ).toString();
    QString host     = ini.value( "host",       QString() ).toString();
    int     port     = ini.value( "port",       -1 ).toInt();
    bool    tls      = ini.value( "tls",        true ).toBool();
    bool updateDest  = ini.value( "updateDest", true ).toBool();

    m_peer->setTarget( destJid, updateDest );
    m_video->setTarget( destJid );
    m_peer->connect( selfJid, password, host, port, tls );
}

MainWnd::~MainWnd()
{
    m_video->deleteLater();
	m_peer->deleteLater();
}

void MainWnd::slotLog( const QString & stri )
{
    ui.console->print( stri );
    ui.console->print( "\n" );
}

void MainWnd::log( const std::string & stri )
{
	QString qstri = QString::fromStdString( stri );
    emit sigLog( qstri );
}

void MainWnd::slotSend( const QString & stri )
{
    // Preparing message to be accepted by Lua machine on host's side.
    QByteArray data = stri.toUtf8();
    data = data.toBase64();

    QByteArray msg;
    QXmlStreamWriter stream( &msg );
    stream.setAutoFormatting( false );

    stream.writeStartElement( "lua" );
    stream.writeCharacters( data );
    stream.writeEndElement();

    msg = msg.toBase64();

    QString striMsg = QString( msg );
    m_peer->sendMessage( striMsg );
}







