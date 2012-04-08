
#include "moto_super_ice.h"
#include "host_ice_thread.h"
#include "moto_ctrl.h"

CMotoSuperIce::CMotoSuperIce( CHostIceThread * owner )
: CMotoCtrlIce( owner )
{
}

CMotoSuperIce::~CMotoSuperIce()
{
}

bool CMotoSuperIce::open( const ::Ice::Current& c )
{
    return m_owner->m_moto->open();
}

void CMotoSuperIce::close( const ::Ice::Current& c )
{
    m_owner->m_moto->close();
}

void CMotoSuperIce::setMotoEn(bool en, const ::Ice::Current& c )
{
    m_owner->m_moto->setMotoEn( en );
}

void CMotoSuperIce::setServoEn(bool en, const ::Ice::Current& c )
{
    m_owner->m_moto->setServoEn( en );
}


