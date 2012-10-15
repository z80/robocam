
#include "fsw_process.h"
#include "peer_abst.h"
#include <boost/bind.hpp>

static const char META[] = "LUA_FSW_META";
static const char LIB_NAME[] = "luafsw";


FswProcess::FswProcess()
: QProcess(),
  m_command( "fswebcam" ),
  //m_args(),
  m_peer( 0 ),
  m_interval( 5000 ),
  m_loop( false ),
  m_stop( false ),
  m_running( false )
{
	//qRegisterMetaType<QProcess::ExitStatus>( "QProcess::ExitStatus" );
	//connect( this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotError(QProcess::ProcessError)) );
	//connect( this, SIGNAL(stateChanged(QProcess::ProcessState)),
	//   	     this, SLOT(slotStateChanged(QProcess::ProcessState))/*, Qt::QueuedConnection*/ );
    connect( this, SIGNAL(sigTimeout()), this, SLOT(slotTimeout())/*, Qt::QueuedConnection*/ );
    m_fileName = "image.png";
    setCommand( "fswebcam -d /dev/video0 -q --png 9 --no-banner -" );
    //setCommand( "fswebcam -d /dev/video0 -q --png 9 --no-banner image2.png" );
}

FswProcess::~FswProcess()
{
	m_mutex.lock();
	m_stop = true;
	m_mutex.unlock();
    m_thread.join();
}

void FswProcess::setCommand( const QString & stri )
{
	QStringList l = stri.split( " " );
    m_command = l.at( 0 );
    m_args.clear();
    m_args.reserve( l.size() - 1 );
    for ( int i=1; i<l.size(); i++ )
    	m_args << l.at( i );
}

void FswProcess::setPeer( PeerAbst * peer )
{
    m_peer = peer;
}

void FswProcess::setSendFileName( const QString & fileName )
{
	m_fileName = fileName;
}

void FswProcess::setInterval( int i )
{
    m_interval = i;
}

void FswProcess::setLoop( bool en )
{
	m_mutex.lock();
    m_loop = en;
    m_mutex.unlock();
}

void FswProcess::start()
{
	m_mutex.lock();
	m_stop = false;
	m_running = true;
	m_mutex.unlock();
	//m_thread = boost::thread( boost::bind( &FswProcess::threadProc, this ) );
	emit sigTimeout();

}

void FswProcess::stop()
{
	m_mutex.lock();
    m_stop = true;
    m_mutex.unlock();
}

bool FswProcess::isRunning() const
{
	m_mutex.lock();
    bool running = m_running;
    m_mutex.unlock();
    running = running && ( state() == QProcess::NotRunning );
    return running;
}

void FswProcess::slotError( QProcess::ProcessError err )
{
    qDebug() << "Error: " << err;
}

void FswProcess::slotStateChanged( QProcess::ProcessState state )
{
	if ( ( m_peer ) && ( state == QProcess::NotRunning ) )
        m_peer->sendFile( m_fileName.toStdString(), this );
}

void FswProcess::slotTimeout()
{
	qDebug() << m_command;
	for ( int i=0; i<m_args.size(); i++ )
		qDebug() << m_args.at( i );
	qDebug() << m_fileName;
	QProcess::start( m_command, m_args );
	bool finished = QProcess::waitForFinished( m_interval );
	if ( ( finished ) && ( m_peer ) )
		m_peer->sendFile( m_fileName.toStdString(), this );
    if ( !finished )
    	QProcess::kill();
}

void FswProcess::threadProc()
{
	bool loop, stop;
	do {
        emit sigTimeout();
        m_mutex.lock();
        stop = m_stop;
        m_mutex.unlock();
        if ( stop )
            break;
        boost::this_thread::sleep( boost::posix_time::milliseconds( m_interval ) );
        m_mutex.lock();
        stop = m_stop;
        loop = m_loop;
        m_mutex.unlock();
	} while ( ( loop ) && ( !stop ) );
    m_mutex.lock();
    m_running = false;
    m_mutex.unlock();
}





static int create( lua_State * L )
{
    int cnt = lua_gettop( L );
    FswProcess * p = new FswProcess();
    FswProcess * * pp = reinterpret_cast< FswProcess * * >( lua_newuserdata( L, sizeof( FswProcess * ) ) );
    *pp = p;
    luaL_getmetatable( L, META );
    lua_setmetatable( L, -2 );

    return 1;
}

static int gc( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
    if ( p )
        p->deleteLater();
    return 0;
}

static int setCommand( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	QString stri = lua_tostring( L, 2 );
	p->setCommand( stri );
	return 0;
}

static int setPeer( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	PeerAbst * pa = reinterpret_cast<PeerAbst *>( const_cast<void *>( lua_topointer( L, 2 ) ) );
	p->setPeer( pa );
	return 0;
}

static int setSendFileName( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	QString stri = lua_tostring( L, 2 );
	p->setSendFileName( stri );
	return 0;
}

static int setInterval( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	int interval = static_cast<int>( lua_tonumber( L, 2 ) );
	p->setInterval( interval );
	return 0;
}

static int setLoop( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	bool en = ( lua_toboolean( L, 2 ) > 0 );
	p->setLoop( en );
	return 0;
}

static int start( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	p->start();
	return 0;
}

static int stop( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	p->stop();
	return 0;
}

static int isRunning( lua_State * L )
{
	FswProcess * p = *reinterpret_cast<FswProcess * *>( lua_touserdata( L, 1 ) );
	bool en = p->isRunning();
	lua_pushboolean( L, ( en ) ? 1 : 0 );
	return 1;

}





static const struct luaL_reg META_FUNCTIONS[] = {
	{ "__gc",            gc },
    { "setCommand",      setCommand },
    { "setPeer",         setPeer },
    { "setSendFileName", setSendFileName },
    { "setInterval",     setInterval },
    { "setLoop",         setLoop },
    { "start",           start },
    { "stop",            stop },
    { "isRunning",       isRunning },

    { NULL,              NULL },
};

static void createMeta( lua_State * L )
{
	int top = lua_gettop( L );
    luaL_newmetatable( L, META );  // create new metatable for file handles
    // file methods
    lua_pushliteral( L, "__index" );
    lua_pushvalue( L, -2 );  // push metatable
    lua_rawset( L, -3 );       // metatable.__index = metatable
    luaL_register( L, NULL, META_FUNCTIONS );

    lua_settop( L, top );
}

static const struct luaL_reg FUNCTIONS[] = {
	{ "create",  create },
	{ NULL, NULL },
};

static void registerFunctions( lua_State * L )
{
    luaL_register( L, LIB_NAME, FUNCTIONS );
}

extern "C" int luaopen_luafsw( lua_State * L )
{
    createMeta( L );
    registerFunctions( L );
    return 0;
}


