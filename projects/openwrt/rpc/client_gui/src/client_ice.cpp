
#include "client_ice.h"
#include "camera_ctrl.h"

CClientIce::CClientIce( CCameraCtrl * owner )
    : IceUtil::Thread(),
      m_owner( owner )
{
    m_props = Ice::createProperties();
    // Чтобы работал callback.
    m_props->setProperty( "Ice.ACM.Client", "0" );
}

CClientIce::~CClientIce()
{
}

void CClientIce::run()
{
    bool removeComm = true;
    try
    {
        Ice::InitializationData initData;
        initData.properties = m_props;
        m_comm   = Ice::initialize( initData );
        m_camera = Demo::CameraPrx::checkedCast( m_comm->stringToProxy( "camera:" + m_server ) );

        if ( ( !m_camera ) )
            throw( std::string( "invalid server proxy: " ) + m_server );

        /*
        // Прикрепление TextClent к локальному адаптеру.
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

void CClientIce::shutdown()
{
    if ( m_comm )
        m_comm->shutdown();
}

std::string CClientIce::status()
{
    m_mutex.lock();
    std::string res = m_status;
    m_mutex.unlock();
    return res;
}

std::string CClientIce::lastError()
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



