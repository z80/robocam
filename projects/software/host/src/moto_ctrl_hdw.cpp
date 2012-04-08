
#include "moto_ctrl_hdw.h"
#include "host_ice_thread.h"
#include "moto_thread_hdw.h"

CMotoCtrlHdw::CMotoCtrlHdw( CHostIceThread * owner, Hdw::CHdwPrx hdwPrx )
: CMotoCtrl( owner )
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    m_motoPrx = hdwPrx->moto();
    m_powerState = false;
    bool open = m_motoPrx->isOpen();
    if ( !open )
        open = m_motoPrx->open();
    if ( open )
    {
        m_motoPrx->setServoEn( false );
        m_motoPrx->setMotoEn( false );
    }
    m_motoThread = new CMotoThreadHdw( 0, this );
    m_motoPrx->setWatchdog( m_motoThread->interval() + 3000 );
}

CMotoCtrlHdw::~CMotoCtrlHdw()
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    m_motoThread->deleteLater();
    m_motoPrx->setServoEn( false );
    m_motoPrx->setMotoEn( false );
}

bool CMotoCtrlHdw::isOpen()
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    bool res = m_motoPrx->isOpen();
    return res;
}

bool CMotoCtrlHdw::motoEn()
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    bool res = m_motoPrx->motoEn();
    return res;
}

void CMotoCtrlHdw::moto( ::Ice::Int & dir1, ::Ice::Int & dir2 )
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    m_motoPrx->moto( dir1, dir2 );
}

bool CMotoCtrlHdw::servoEn()
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    bool res = m_motoPrx->servoEn();
    return res;
}

void CMotoCtrlHdw::servo( ::Ice::Double & servo1, ::Ice::Double & servo2 )
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    ::Ice::Int s1, s2;
    m_motoPrx->servo( s1, s2 );
    servo1 = static_cast< ::Ice::Double >( s1 - 250 ) / ( 500.0 - 250.0 ) * 90.0 - 45.0;
    servo2 = static_cast< ::Ice::Double >( s2 - 250 ) / ( 500.0 - 250.0 ) * 90.0 - 45.0;
}

void CMotoCtrlHdw::setMoto( ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period )
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    m_motoPrx->setMoto( dir1, dir2, 0 );
}

void CMotoCtrlHdw::setServo( ::Ice::Double servo1, ::Ice::Double servo2 )
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    int s1 = static_cast<int>( ( servo1 + 45.0 ) / 90.0 * (500.0 - 250.0) ) + 250;
    int s2 = static_cast<int>( ( servo2 + 45.0 ) / 90.0 * (500.0 - 250.0) ) + 250;
    m_motoPrx->setServo( s1, s2 );
}

bool CMotoCtrlHdw::open()
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    bool res = m_motoPrx->open();
    return res;
}

void CMotoCtrlHdw::close()
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    m_motoPrx->close();
}

void CMotoCtrlHdw::setMotoEn( bool en )
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    m_motoPrx->setMotoEn( en );
}

void CMotoCtrlHdw::setServoEn( bool en )
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    m_motoPrx->setServoEn( en );
}

void CMotoCtrlHdw::checkPowerState()
{
    ::IceUtil::Mutex::Lock lock( m_mut );
    // Reset moto watchdog first of all.
    m_motoPrx->resetWatchdog();

    // Depending on client cnt and curent power state turn power on or off.
    int cnt = m_owner->m_host->clientCnt();
    if ( m_powerState )
    {
        if ( cnt < 1 )
        {
            m_motoPrx->setMoto( 0, 0, 0 );
            m_motoPrx->setMotoEn( false );
            m_motoPrx->setServoEn( false );
            m_powerState = false;
        }
    }
    else
    {
        if ( cnt > 0 )
        {
            m_motoPrx->setMotoEn( true );
            m_motoPrx->setServoEn( true );
            m_motoPrx->setMoto( 0, 0, 0 );
            m_powerState = true;
        }
    }
}



