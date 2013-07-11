
#include "main_wnd.h"
#include <QtXml>

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

    QObject::connect( ui.clearLog,    SIGNAL(triggered()), this, SLOT(slotClearLog()) );

    QObject::connect( ui.showFullLog, SIGNAL(triggered()), this, SLOT(slotShowFullLog()) );
    QObject::connect( ui.queryStatus, SIGNAL(triggered()), this, SLOT(slotStatus()) );
    QObject::connect( ui.shutdown,    SIGNAL(triggered()), this, SLOT(slotShutdown()) );
    QObject::connect( ui.forward,     SIGNAL(changed()),   this, SLOT(slotForward()) );
    QObject::connect( ui.backward,    SIGNAL(changed()),   this, SLOT(slotBackward()) );
    QObject::connect( ui.left,        SIGNAL(changed()),   this, SLOT(slotLeft()) );
    QObject::connect( ui.right,       SIGNAL(changed()),   this, SLOT(slotRight()) );


    QObject::connect( ui.showFullLog, SIGNAL(triggered()), this, SLOT(slotShowFullLog()) );

    m_peer = new QXmppPeer( this );
    QObject::connect( m_peer, SIGNAL(connected()),      this, SLOT(slotConnected()) );
    QObject::connect( m_peer, SIGNAL(disconnected()),   this, SLOT(slotDisconnected()) );
    QObject::connect( m_peer, SIGNAL(textmsg(QString)), this, SLOT(qxmppMessageReceived(QString)) );

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
    ui.log->append( stri );
}

void MainWnd::slotShowFullLog()
{
    bool en = ui.showFullLog->isChecked();
    if ( en )
        QObject::connect( m_peer, SIGNAL(log(QString)), this, SLOT(slotLog(QString)) );
    else
        QObject::disconnect( m_peer, SIGNAL(log(QString)), this, SLOT(slotLog(QString)) );
}

void MainWnd::slotConnected()
{
    log( "Connected" );
}

void MainWnd::slotDisconnected()
{
    log( "Disconnected" );
}

void MainWnd::slotClearLog()
{
    ui.log->clear();
}

void MainWnd::slotStatus()
{
    slotSend( "sendStatus()" );
}

void MainWnd::slotShutdown()
{
    slotSend( "shutdown()" );
}

void MainWnd::slotForward()
{
    if( ui.forward->isChecked() )
        slotSend( "motoForward()" );
    else
        slotSend( "motoStop()" );
}

void MainWnd::slotBackward()
{
    if( ui.backward->isChecked() )
        slotSend( "motoBackward()" );
    else
        slotSend( "motoStop()" );
}

void MainWnd::slotLeft()
{
    if( ui.left->isChecked() )
        slotSend( "motoLeft()" );
    else
        slotSend( "motoStop()" );
}

void MainWnd::slotRight()
{
    if( ui.right->isChecked() )
        slotSend( "motoRight()" );
    else
        slotSend( "motoStop()" );
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

void MainWnd::qxmppMessageReceived( const QString & stri )
{
    QByteArray data = QByteArray::fromBase64( stri.toUtf8() );

    QDomDocument doc;
    QString errorMsg;
    bool res = doc.setContent( data, &errorMsg );
    if ( !res )
    {
        slotLog( stri );
        return;
    }
    QDomElement  root = doc.documentElement();
    if ( root.tagName() == "msg" )
    {
        if ( root.hasAttribute( "type" ) )
        {
            QString cmd = root.text();
            if ( root.attribute( "type" ) == "status" )
                ui.status->setText( cmd );
            else
                slotLog( cmd );
        }
    }
}







