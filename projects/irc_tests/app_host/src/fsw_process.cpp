
#include "fsw_process.h"
#include "peer_abst.h"
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
    connect( this, SIGNAL(finished(int, QProcess::ExitStatus)),
    		 this, SLOT(slotFinished( int, QProcess::ExitStatus)) );
    m_fileName = "image.png";
    setCommand( "fswebcam -d /dev/video0 -q --png 9 --no-banner -" );
}

FswProcess::~FswProcess()
{

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
    m_loop = en;
}

void FswProcess::start()
{
	m_stop = false;
	m_running = true;
	QTimer::singleShot( 0, this, SLOT(frame()) );
}

void FswProcess::stop()
{
    m_stop = true;
}

bool FswProcess::isRunning() const
{
	return m_running;
}

void FswProcess::timeout()
{
	if ( m_stop )
	{
		m_running = false;
		return;
	}
	if ( m_peer )
        QProcess::start( m_command, m_args );
}

void FswProcess::slotFinished( int exitCode, QProcess::ExitStatus exitStatus )
{
	if ( ( m_peer ) && ( exitStatus == QProcess::NormalExit ) )
	{
        m_peer->sendFile( m_fileName.toStdString(), this );
        if ( m_loop )
        {
            QTimer::singleShot( m_interval, this, SLOT(timeout()) );
            return;
        }
	}
    m_running = false;
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


