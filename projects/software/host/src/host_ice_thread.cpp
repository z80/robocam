
#include "host_ice_thread.h"
#include "IceE/IceE.h"
#include "cam_ctrl_hdw.h"
#include "cam_ctrl_eml.h"
#include "moto_ctrl_hdw.h"
#include "moto_ctrl_eml.h"
#include <sstream>

#include "QsLog.h"

CHostIceThread::CHostIceThread( const std::string & listen,
                                const std::string & connect,
                                const std::string & passwd )
: IceUtil::Thread(),
  m_listen( listen ),
  m_connect( connect ),
  m_passwd( passwd )
{
    m_moto = 0;
    m_cam  = 0;
}

CHostIceThread::~CHostIceThread()
{
}

void CHostIceThread::shutdown()
{
    if ( m_comm )
    {
        m_semaphore.lock();
        m_comm->shutdown();
        m_semaphore.wait();
        m_semaphore.unlock();
    }
}

std::string CHostIceThread::lastError()
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

std::string CHostIceThread::status() const
{
    m_mutex.lock();
    std::string res = m_status;
    m_mutex.unlock();
    return res;
}

bool CHostIceThread::listen()
{
    QLOG_TRACE() << "listen() dispatch started";
    m_semaphore.lock();
    start();
    m_semaphore.wait();
    m_semaphore.unlock();
    bool res = ( status() == "connected" );
    QLOG_TRACE() << "listen() result: " << ( res ? "true" : "false" );
    return res;
}

bool CHostIceThread::connect( bool emulation )
{
    QLOG_TRACE() << "connect() dispatch started";
    IceUtil::Mutex::Lock lock( m_mutex );
    bool res;
    if ( m_moto )
        delete m_moto;
    if ( m_cam )
        delete m_cam;
    if ( emulation )
    {
            QLOG_TRACE() << "emulation is used";
            m_moto = new CMotoCtrlEml( this );
            m_cam  = new CCamCtrlEml( this );
            res = true;
    }
    else
    {
        try
        {
            QLOG_TRACE() << "trying to connect to hardware";
            // �������� ������ ������ �� Hdw
            std::ostringstream os;
            os << "hdw: " << m_connect;
            std::string hdwAddr = os.str();
            m_hdw = ::Hdw::CHdwPrx::uncheckedCast( m_comm->stringToProxy( hdwAddr ) );
            if ( !m_hdw )
                throw ::Ice::Exception( "Failed to connect to hardware", 0 );
            m_moto = new CMotoCtrlHdw( this, m_hdw );
            m_cam  = new CCamCtrlHdw( this, m_hdw );
            res = true;
        }
        catch ( ::Ice::Exception & /*ex*/ )
        {
            QLOG_TRACE() << "failed to connect to hardware, emulation is used instead";
            m_moto = new CMotoCtrlEml( this );
            m_cam  = new CCamCtrlEml( this );
            res = false;
        }
    }
    QLOG_TRACE() << "connect() result: " << ( res ? "true" : "false" );
    return res;
}

bool CHostIceThread::hdwAttached()
{
    bool res;
    m_mutex.lock();
    try
    {
        m_hdw->ice_ping();
        res = true;
    }
    catch ( ::Ice::Exception & /*ex*/ )
    {
        res = false;
    }
    m_mutex.unlock();
    return res;
}

void CHostIceThread::run()
{
    try
    {
        Ice::PropertiesPtr   props = Ice::createProperties();
        Ice::InitializationData initData;
        initData.properties = props;
        m_comm = Ice::initialize( initData );

        m_adapter = m_comm->createObjectAdapterWithEndpoints( "host_adapter", m_listen );
        m_host = new CHostIce( this );
        m_adapter->add( m_host, m_comm->stringToIdentity( "host" ) );
        m_adapter->activate();

        m_mutex.lock();
        m_status = "connected";
        m_mutex.unlock();

        m_semaphore.lock();
        m_semaphore.notifyAll();
        m_semaphore.unlock();
        m_comm->waitForShutdown();
        m_comm->destroy();
    }
    catch(const Ice::Exception& ex)
    {
        m_errors.push( ex.ice_name() );
        if( m_comm )
        {
            try
            {
                m_comm->destroy();
            }
            catch(const Ice::Exception& ex)
            {
                m_errors.push( ex.ice_name() );
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

