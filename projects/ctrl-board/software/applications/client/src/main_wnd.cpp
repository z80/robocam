
#include "main_wnd.h"
#include "pipe_setup.h"
#include <QtXml>

#include "lua.hpp"
#include "boost/bind.hpp"
#include "boost/bind/placeholders.hpp"

const QString     MainWnd::CONFIG_FILE = ":client.ini";
const int         MainWnd::LOG_MAX       = 256;
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
    QObject::connect( ui.dontSleep,   SIGNAL(triggered()), this, SLOT(slotDontSleep()) );

    QObject::connect( ui.showFullLog, SIGNAL(triggered()), this, SLOT(slotShowFullLog()) );
    QObject::connect( ui.queryStatus, SIGNAL(triggered()), this, SLOT(slotStatus()) );
    QObject::connect( ui.queryOsc,    SIGNAL(triggered()), this, SLOT(slotOsc()) );
    QObject::connect( ui.shutdown,    SIGNAL(triggered()), this, SLOT(slotShutdown()) );
    QObject::connect( ui.setupPipe,   SIGNAL(triggered()), this, SLOT(slotSetupPipe()) );

    QObject::connect( ui.lightBtn,    SIGNAL(clicked()),   this, SLOT(slotLight()) );
    QObject::connect( ui.motoEnBtn,   SIGNAL(clicked()),   this, SLOT(slotMotoEn()) );

    QObject::connect( ui.fwdBtn,      SIGNAL(pressed()),   this, SLOT(slotForward()) );
    QObject::connect( ui.bwdBtn,      SIGNAL(pressed()),   this, SLOT(slotBackward()) );
    QObject::connect( ui.leftBtn,     SIGNAL(pressed()),   this, SLOT(slotLeft()) );
    QObject::connect( ui.rightBtn,    SIGNAL(pressed()),   this, SLOT(slotRight()) );

    QObject::connect( ui.fwdBtn,      SIGNAL(released()),  this, SLOT(slotStop()) );
    QObject::connect( ui.bwdBtn,      SIGNAL(released()),  this, SLOT(slotStop()) );
    QObject::connect( ui.leftBtn,     SIGNAL(released()),  this, SLOT(slotStop()) );
    QObject::connect( ui.rightBtn,    SIGNAL(released()),  this, SLOT(slotStop()) );


    QObject::connect( ui.showFullLog, SIGNAL(triggered()), this, SLOT(slotShowFullLog()) );

    m_peer = new QXmppPeer( this );
    QObject::connect( m_peer, SIGNAL(connected()),      this, SLOT(slotConnected()) );
    QObject::connect( m_peer, SIGNAL(disconnected()),   this, SLOT(slotDisconnected()) );
    QObject::connect( m_peer, SIGNAL(textmsg(QString)), this, SLOT(qxmppMessageReceived(QString)) );

    m_video = new QXmppVideo( m_peer );
    // It also connects frameReady() signal to an appropriate slot.
    ui.view->setVideo( m_video );
    this->setCentralWidget( ui.view );

    QSettings ini( CONFIG_FILE, QSettings::IniFormat );
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
    m_jidDest = destJid;

    m_pipe = new QXmppMsgPipe( m_peer, 1 );
    m_pipe->setOutPipe( m_jidDest, 1234, 22, "localhost" );

    m_dontSleepTimer = new QTimer( this );
    m_dontSleepTimer->setInterval( 15000 );
    QObject::connect( m_dontSleepTimer, SIGNAL(timeout()), 
                      this,             SLOT(slotDontSleepTimeout()) );
}

MainWnd::~MainWnd()
{
    m_video->deleteLater();
	m_peer->deleteLater();
}

void MainWnd::slotLog( const QString & stri )
{
    ui.log->append( stri );
    if ( stri == "Host is online" )
    {
        ui.dontSleep->setChecked( true );
        slotDontSleep();
    }
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

void MainWnd::slotDontSleep()
{
    if ( ui.dontSleep->isChecked() )
        m_dontSleepTimer->start();
    else
        m_dontSleepTimer->stop();
}

void MainWnd::slotDontSleepTimeout()
{
    if ( m_peer->isConnected() )
        slotSend( "timeoutReset()" );
}

void MainWnd::slotSetupPipe()
{
    PipeSetup ps( this );
    int res = ps.exec();
    if ( res == QDialog::Accepted )
    {
        int localPort, 
            remotePort;
        QString remoteHost;
        ps.pipe( localPort, remotePort, remoteHost );
        m_pipe->setOutPipe( m_jidDest, localPort, remotePort, remoteHost );
    }
}

void MainWnd::slotStatus()
{
    slotSend( "sendStatus()" );
}

void MainWnd::slotOsc()
{
    slotSend( "sendOsc()" );
}

void MainWnd::slotShutdown()
{
    slotSend( "shutdown()" );
}

void MainWnd::slotLight()
{
    bool en = ui.lightBtn->isChecked();
    QString stri;
    if ( en )
        stri = "setLight( true )";
    else
        stri = "setLight( false )";
    slotSend( stri );
}

void MainWnd::slotMotoEn()
{
    QString stri;
    bool en = ui.motoEnBtn->isChecked();
    if ( en )
    {
        stri = "setMotoEn( true )";
        grabKeyboard();
    }
    else
    {
        stri = "setMotoEn( false )";
        releaseKeyboard();
    }
    ui.fwdBtn->setEnabled( en );
    ui.bwdBtn->setEnabled( en );
    ui.leftBtn->setEnabled( en );
    ui.rightBtn->setEnabled( en );

    slotSend( stri );
}

void MainWnd::slotForward()
{
    if ( ui.motoEnBtn->isChecked() )
        slotSend( "motoForward()" );
}

void MainWnd::slotBackward()
{
    if ( ui.motoEnBtn->isChecked() )
        slotSend( "motoBackward()" );
}

void MainWnd::slotLeft()
{
    if ( ui.motoEnBtn->isChecked() )
        slotSend( "motoLeft()" );
}

void MainWnd::slotRight()
{
    if ( ui.motoEnBtn->isChecked() )
        slotSend( "motoRight()" );
}

void MainWnd::slotStop()
{
    slotSend( "motoStop()" );
}

void MainWnd::keyPressEvent( QKeyEvent * event )
{
    switch(  event->key() )
    {
    case Qt::Key_W:
        slotForward();
        break;
    case Qt::Key_S:
        slotBackward();
        break;
    case Qt::Key_A:
        slotLeft();
        break;
    case Qt::Key_D:
        slotRight();
        break;
    }
}

void MainWnd::keyReleaseEvent( QKeyEvent * event )
{
    switch(  event->key() )
    {
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        slotStop();
        break;
    }

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







