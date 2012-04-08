
#include "client_ice_thread.h"

CClientIceThread::CClientIceThread( const std::string & host,
                                    const std::string & clientName )
    : IceUtil::Thread(),
      m_host( host ),
      m_clientNickname( clientName )
{
}

CClientIceThread::~CClientIceThread()
{
}

void CClientIceThread::run()
{
    bool removeComm = true;
    try
    {
        Ice::InitializationData initData;
        Ice::PropertiesPtr      props;
        props = Ice::createProperties();
        // To make callback possible it is necessary to use tcp connection.
        props->setProperty( "client_adapter.Endpoints", "tcp" );
        initData.properties = props;
        m_comm    = Ice::initialize( initData );
        m_adapter = m_comm->createObjectAdapter( "client_adapter" );
        Ice::ObjectPrx hostBase = m_comm->stringToProxy( "host:" + m_host );
        //m_hostPrx = ::Host::CHostPrx::uncheckedCast( hostBase->ice_twoway()->ice_timeout(-1) );
        m_hostPrx = ::Host::CHostPrx::uncheckedCast( hostBase );

        if ( ( !m_hostPrx ) )
            throw( std::string( "invalid server proxy: " ) + m_host );

        /*
        // ������������ TextClent � ���������� ��������.
        Ice::ObjectAdapterPtr adapter = m_comm->createObjectAdapter( "" );
        Ice::Identity m_ident;
        m_ident.name = IceUtil::generateUUID();
        m_ident.category = "";
        ///Ice::ObjectPtr object = CarCtrl::TextClientPtr( m_owner );
        adapter->add( m_owner, m_ident );
        adapter->activate();
        m_textHost->ice_getConnection()->setAdapter( adapter );
        m_textHost->registerClient( m_ident, m_owner->clientName() );
        */
        m_client = new CClientIce( this );

        //m_client->m_clientPrx = ::Client::CClientPrx::uncheckedCast( m_adapter->addWithUUID( m_client ) );
        m_adapter->activate();
        // ��������� callback ��� m_hostPrx.
        m_hostPrx->ice_getConnection()->setAdapter( m_adapter );
        // ����� ���������� �������.
        if ( !m_hostPrx->registerClient( m_client->m_clientPrx, m_clientNickname, m_clientId ) )
            throw m_clientId;


        m_mutex.lock();
        m_status = "connected";
        m_mutex.unlock();

        m_semaphore.lock();
        m_semaphore.notifyAll();
        m_semaphore.unlock();

        m_comm->waitForShutdown();

        m_mutex.lock();
        m_status = "disconnecting";
        m_mutex.unlock();
        removeComm = false;
    }
    catch ( const Ice::Exception & e )
    {
        m_mutex.lock();
        m_errors.push( e.ice_name() );
        m_mutex.unlock();
        removeComm = false;
    }
    catch ( const std::string & e )
    {
        m_mutex.lock();
        m_errors.push( e );
        m_mutex.unlock();
        removeComm = false;
    }
    catch ( const char * e )
    {
        m_mutex.lock();
        m_errors.push( e );
        m_mutex.unlock();
        removeComm = false;
    }
    if ( removeComm )
    {
        if ( m_comm )
        {
            try
            {
                m_comm->destroy();
            }
            catch ( const Ice::Exception & e )
            {
                m_mutex.lock();
                m_errors.push( e.ice_name() );
                m_mutex.unlock();
            }
        }
    }

    m_mutex.lock();
    m_status = "disconnected";
    m_mutex.unlock();

    m_semaphore.lock();
    m_semaphore.notifyAll();
    m_semaphore.unlock();
}

bool CClientIceThread::connect()
{
    m_semaphore.lock();
    start();
    m_semaphore.wait();
    m_semaphore.unlock();
    return (status() == "connected");
}

void CClientIceThread::shutdown()
{
    if ( m_comm )
    {
        m_hostPrx->removeClient( m_clientId );
        m_semaphore.lock();
        m_comm->shutdown();
        m_semaphore.wait();
        m_semaphore.unlock();
    }
}

std::string CClientIceThread::status()
{
    IceUtil::Mutex::Lock lock( m_mutex );
    return m_status;
}

const std::string & CClientIceThread::clientId() const
{
    IceUtil::Mutex::Lock lock( m_mutex );
    return m_clientId;
}

std::string CClientIceThread::lastError()
{
    m_mutex.lock();
    if ( m_errors.size() )
    {
        std::string res = m_errors.back();
        m_errors.pop();
        m_mutex.unlock();
        return res;
    }
    m_mutex.unlock();
    return std::string();
}

bool CClientIceThread::queryView()
{
    m_motoPrx = ::Host::CMotoPrx::uncheckedCast( m_hostPrx->moto( m_clientId ) );
    m_camPrx  = ::Host::CCamPrx::uncheckedCast( m_hostPrx->cam( m_clientId ) );
    return true;
}

bool CClientIceThread::queryCtrl()
{
    bool res = m_hostPrx->queryCtrl( m_clientId );
    m_motoPrx = ::Host::CMotoPrx::uncheckedCast( m_hostPrx->moto( m_clientId ) );
    m_camPrx  = ::Host::CCamPrx::uncheckedCast( m_hostPrx->cam( m_clientId ) );
    return res;
}

void CClientIceThread::releaseCtrl()
{
    m_hostPrx->releaseCtrl( m_clientId );
}

::Host::CHostPrx CClientIceThread::host()
{
    return m_hostPrx;
}

::Host::CMotoPrx CClientIceThread::moto()
{
    return m_motoPrx;
}

::Host::CCamPrx  CClientIceThread::cam()
{
    return m_camPrx;
}

bool CClientIceThread::querySuper( const std::string & stri )
{
    bool res = m_hostPrx->querySuper( m_clientId, stri );
    m_motoPrx = ::Host::CMotoPrx::uncheckedCast( m_hostPrx->moto( m_clientId ) );
    m_camPrx  = ::Host::CCamPrx::uncheckedCast( m_hostPrx->cam( m_clientId ) );
    return res;
}

void CClientIceThread::setAcceptClientListCb( const TAcceptClientListCb & value )
{
    m_acceptClientListCb = value;
}

void CClientIceThread::setAcceptMessageCb( const TAcceptMessageCb & value )
{
    m_acceptMessageCb = value;
}

void CClientIceThread::setMotoEnCb( const TMotoEnCb & value )
{
    m_motoEnCb = value;
}

void CClientIceThread::setMotoCb( const TMotoCb & value )
{
    m_motoCb = value;
}

void CClientIceThread::setServoEnCb( const TServoEnCb & value )
{
    m_servoEnCb = value;
}

void CClientIceThread::setServoCb( const TServoCb & value )
{
    m_servoCb = value;
}

void CClientIceThread::setAcceptImageCb( const TAcceptImageCb & value )
{
    m_acceptImageCb = value;
}





