
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
    connect( this, SIGNAL(sigImageAccepted()), this, SLOT(slotImageAccepted()), Qt::QueuedConnection );

    m_peer = new PeerQxmpp( CONFIG_FILE, boost::bind( &MainWnd::init, this, _1 ) );
	m_peer->setInFileHandler( boost::bind<QIODevice *>( &MainWnd::inFileHandler, this, _1 ) );
	m_peer->setAccFileHandler( boost::bind( &MainWnd::accFileHandler, this, _1, _2 ) );

    connect( ui.clearBtn,  SIGNAL(clicked()), this, SLOT(slotClear()) );
    connect( ui.sendBtn,   SIGNAL(clicked()), this, SLOT(slotSend()) );
    connect( ui.imgBtn,    SIGNAL(clicked()), this, SLOT(slotImage()) );
    connect( ui.voltsBtn,  SIGNAL(clicked()), this, SLOT(slotVoltages()) );
    connect( ui.motoEnBtn, SIGNAL(clicked()), this, SLOT(slotMotoEn()) );
    connect( ui.lightBtn,  SIGNAL(clicked()), this, SLOT(slotLight()) );

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
	delete m_peer;
}

void MainWnd::slotLog( const QString & stri )
{
	while ( m_logList.size() > LOG_MAX )
		m_logList.pop_front();
	m_logList.push_back( stri );
	ui.log->clear();
    for ( QStringList::const_iterator it=m_logList.begin(); it!=m_logList.end(); it++ )
    	ui.log->append( *it );
    ui.log->verticalScrollBar()->setSliderPosition( ui.log->verticalScrollBar()->maximum() );
}

void MainWnd::slotImageAccepted()
{
	ui.imageLbl->setPixmap( QPixmap::fromImage( m_img ) );
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

void MainWnd::slotSend()
{
    std::string stri = ui.cmd->toPlainText().toUtf8().data();
    m_peer->send( stri );
}

void MainWnd::slotClear()
{
    ui.log->clear();
    m_logList.clear();
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
    	QString stri = QString( "moto( %1, %2, %3, %4, %5 )" )
    			                .arg( (v & MOTO1) ? "true" : "false" )
    			                .arg( (v & MOTO2) ? "true" : "false" )
    			                .arg( (v & MOTO3) ? "true" : "false" )
    			                .arg( (v & MOTO4) ? "true" : "false" )
    			                .arg( msecs );
    	m_peer->send( stri.toStdString() );
    }
    else
    	m_peer->send( "moto( false, false, false, false )" );
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
	QString stri = QString( "moto( %1, %2, %3, %4, %5 )" )
			                .arg( (v & MOTO1) ? "true" : "false" )
			                .arg( (v & MOTO2) ? "true" : "false" )
			                .arg( (v & MOTO3) ? "true" : "false" )
			                .arg( (v & MOTO4) ? "true" : "false" )
			                .arg( 0 );
	m_peer->send( stri.toStdString() );
}






