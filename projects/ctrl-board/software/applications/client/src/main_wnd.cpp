
#include "main_wnd.h"

#include "lua.hpp"
#include "boost/bind.hpp"
#include "boost/bind/placeholders.hpp"

const std::string MainWnd::CONFIG_FILE = "client.ini";
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
    m_video = new QXmppVideo( m_peer );
    m_lua  = new LuaMachine( m_peer );
    ui.view->setVideo( m_video );


    QSettings ini( CONFIG_FILE.c_str(), QSettings::IniFormat );
    QString selfJid  = ini.value( "selfJid",  "host@xmpp" ).toString();
    QString destJid  = ini.value( "destJid",  "client@xmpp" ).toString();
    QString password = ini.value( "password", "12345" ).toString();
    QString host     = ini.value( "host",     QString() ).toString();
    int     port     = ini.value( "port",     -1 ).toInt();
    bool    tls      = ini.value( "tls",      true ).toBool();
    m_peer->connect( selfJid, password, host, port, tls );
}

MainWnd::~MainWnd()
{
    m_scene->deleteLater();
    m_lua->deleteLater();
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
    std::string sstri = stri.toStdString();
    m_peer->send( sstri );
}

void MainWnd::slotImage()
{
    const std::string cmd = "image()";
    m_peer->send( cmd );
}

void MainWnd::slotVoltages()
{
    const std::string cmd = "volts()";
    m_peer->send( cmd );
}

void MainWnd::slotLight()
{
    if ( ui.lightBtn->isChecked() )
    	m_peer->send( "led( true )" );
    else
    	m_peer->send( "led( false )" );
}

void MainWnd::slotMotoEn()
{
    if ( ui.motoEnBtn->isChecked() )
    	m_peer->send( "motoConfig( true, 10 )" );
    else
    	m_peer->send( "motoConfig( false, 10 )" );
}

void MainWnd::slotPowerEn()
{
    if ( ui.powerEnBtn->isChecked() )
    	m_peer->send( "powerEn( true )" );
    else
    	m_peer->send( "powerEn( false )" );
}

void MainWnd::slotMotoDown()
{
    m_time = QTime::currentTime();
    m_time.start();
    QTimer::singleShot( MOTO_TIME_MAX, this, SLOT(slotTimeout()) );
    QPushButton * b = qobject_cast<QPushButton *>( sender() );
    if ( b )
    {
    	quint8 v = m_motoBtns[ b ];
        m_motoVal |= v;
    }
}

void MainWnd::slotMotoUp()
{
    int msecs = m_time.elapsed();
    if ( msecs < MOTO_TIME_MAX )
    {
    	quint8 v = m_motoVal;
        QString stri = QString( "motoSet( %1, %2, %3, %4, %5 )" )
    			                .arg( (v & MOTO1) ? "true" : "false" )
    			                .arg( (v & MOTO2) ? "true" : "false" )
    			                .arg( (v & MOTO3) ? "true" : "false" )
    			                .arg( (v & MOTO4) ? "true" : "false" )
    			                .arg( msecs );
    	m_peer->send( stri.toStdString() );
    }
    else
        m_peer->send( "motoSet( false, false, false, false )" );
    QPushButton * b = qobject_cast<QPushButton *>( sender() );
    if ( b )
    {
    	quint8 v = m_motoBtns[ b ];
        m_motoVal &= (~v);
    }

}

void MainWnd::slotTimeout()
{
	quint8 v = m_motoVal;
    QString stri = QString( "motoSet( %1, %2, %3, %4, %5 )" )
			                .arg( (v & MOTO1) ? "true" : "false" )
			                .arg( (v & MOTO2) ? "true" : "false" )
			                .arg( (v & MOTO3) ? "true" : "false" )
			                .arg( (v & MOTO4) ? "true" : "false" )
			                .arg( 0 );
	m_peer->send( stri.toStdString() );
}

void MainWnd::updatePixmap( const QImage & img )
{
    if ( !img.isNull() )
        m_pixmap = QPixmap::fromImage( img );
    if ( m_pixmap.isNull() )
        return;

    QSizeF imgSz = m_pixmap.size();
    QSizeF wndSz = ui.view->size();
    
    qreal sc;
    qreal x, y;
    if ( ( imgSz.width() * wndSz.height() ) > ( imgSz.height() * wndSz.width() ) )
    {
        sc = wndSz.width() / imgSz.width();
        x = 0.0;
        y = ( static_cast<qreal>( wndSz.height() ) - 
              static_cast<qreal>( imgSz.height() ) * sc ) * 0.5;
    }
    else
    {
        sc = wndSz.height() / imgSz.height();
        x = ( static_cast<qreal>( wndSz.width() ) - 
              static_cast<qreal>( imgSz.width() ) * sc ) * 0.5;
        y = 0.0;
    }
    m_scene->setSceneRect( QRectF( 0.0, 0.0, wndSz.width(), wndSz.height() ) );
    m_image->setPixmap( m_pixmap );

    QTransform scale;
    scale.scale( sc, sc );

    QTransform tran;
    tran.translate( x, y );

    tran = scale * tran;
    m_image->setTransform( tran );
}

void MainWnd::sceneResizeEvent( QResizeEvent * e )
{
    QSizeF sz = ui.view->size();
    ui.view->setSceneRect( 0.0, 0.0, sz.width() - 10, sz.height() - 10 );
    updatePixmap();
}





