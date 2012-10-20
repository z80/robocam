
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
	m_motoVal = 0;
    ui.setupUi( this );
    connect( this, SIGNAL(sigLog(const QString &)), this, SLOT(slotLog(const QString &)), Qt::QueuedConnection );
    connect( ui.console, SIGNAL(line_validate(const QString &)), this, SLOT(slotSend(const QString &)), Qt::QueuedConnection );

    connect( this, SIGNAL(sigImageAccepted()), this, SLOT(slotImageAccepted()), Qt::QueuedConnection );

    m_scene = new QGraphicsScene( ui.view );
    m_scene->setBackgroundBrush( QBrush( Qt::gray ) );
    ui.view->setScene( m_scene );
    ui.view->installEventFilter( this );

    m_image = new QGraphicsPixmapItem( 0, m_scene );
    m_image->setPos( 0.0, 0.0 );

    m_peer = new PeerQxmpp( CONFIG_FILE, boost::bind( &MainWnd::init, this, _1 ) );
	m_peer->setInFileHandler( boost::bind<QIODevice *>( &MainWnd::inFileHandler, this, _1 ) );
	m_peer->setAccFileHandler( boost::bind( &MainWnd::accFileHandler, this, _1, _2 ) );

    connect( ui.imgBtn,     SIGNAL(clicked()), this, SLOT(slotImage()) );
    connect( ui.voltsBtn,   SIGNAL(clicked()), this, SLOT(slotVoltages()) );
    connect( ui.motoEnBtn,  SIGNAL(clicked()), this, SLOT(slotMotoEn()) );
    connect( ui.powerEnBtn, SIGNAL(clicked()), this, SLOT(slotPowerEn()) );
    connect( ui.lightBtn,   SIGNAL(clicked()), this, SLOT(slotLight()) );

    // Connecting GUI slots.
    m_motoBtns[ ui.fwdBtn ] = MOTO1 | MOTO3;
    m_motoBtns[ ui.bwdBtn ] = MOTO2 | MOTO4;
    m_motoBtns[ ui.ccwBtn ] = MOTO1 | MOTO4;
    m_motoBtns[ ui.cwBtn ]  = MOTO2 | MOTO3;
    m_motoBtns[ ui.leftFwdBtn ]  = MOTO1;
    m_motoBtns[ ui.leftBwdBtn ]  = MOTO2;
    m_motoBtns[ ui.rightFwdBtn ] = MOTO3;
    m_motoBtns[ ui.rightBwdBtn ] = MOTO4;
    for ( QHash<QPushButton *, quint8>::iterator it=m_motoBtns.begin(); it!=m_motoBtns.end(); it++ )
    {
    	QPushButton * b = it.key();
        connect( b, SIGNAL(pressed()),  this, SLOT(slotMotoDown()) );
        connect( b, SIGNAL(released()), this, SLOT(slotMotoUp()) );
    }
}

MainWnd::~MainWnd()
{
    m_scene->deleteLater();
    delete m_image;
	delete m_peer;
}

bool MainWnd::eventFilter( QObject * o, QEvent * e )
{
    if ( e->type() == QEvent::Resize )
    {
        QResizeEvent * re = dynamic_cast<QResizeEvent *>( e );
        if ( re )
            sceneResizeEvent( re );
    }
    return false;
}

void MainWnd::slotLog( const QString & stri )
{
    ui.console->print( stri );
    ui.console->print( "\n" );
}

void MainWnd::slotImageAccepted()
{
	updatePixmap( m_img );
}

static int print( lua_State * L )
{
	lua_pushstring( L, "MainWnd" );
	lua_gettable( L, LUA_REGISTRYINDEX );
	MainWnd * mw = reinterpret_cast<MainWnd *>( const_cast<void *>( lua_topointer( L, -1 ) ) );
	lua_pop( L, 1 );
	return mw->print( L );
}

void MainWnd::init( lua_State * L )
{
	lua_pushstring( L, "MainWnd" );
	lua_pushlightuserdata( L, reinterpret_cast<void *>( this ) );
	lua_settable( L, LUA_REGISTRYINDEX );

    lua_pushstring( L, "print" );
    lua_pushcfunction( L, ::print );
    lua_settable( L, LUA_GLOBALSINDEX );

	// Execute file.
	luaL_dofile( L, "./client.lua" );
}

QIODevice * MainWnd::inFileHandler( const std::string & fileName )
{
	QString fn = QString::fromStdString( fileName );
	if ( fn.toLower().right( 4 ) == ".png" )
	{
		QBuffer * buf = new QBuffer();
		buf->open( QIODevice::WriteOnly );
		return buf;
	}
    return 0;
}

void MainWnd::accFileHandler( const std::string & fileName, QIODevice * file )
{
    if ( file->isOpen() )
    	file->close();
    if ( !file->open( QIODevice::ReadOnly ) )
    	return;
    if ( m_img.load( file, "PNG" ) )
    	emit sigImageAccepted();
}

int MainWnd::print( lua_State * L )
{
	int top = lua_gettop( L );
	for ( int i=1; i<=top; i++ )
	{
        std::string stri = lua_tostring( L, i );
        log( stri );
	}
	lua_settop( L, 0 );
	return 0;
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
    if ( ui.motoEnBtn->isChecked() )
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





