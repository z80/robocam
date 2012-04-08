
#include "moto_ctrl_ice.h"
#include "host_ice_thread.h"
#include "moto_ctrl.h"

CMotoCtrlIce::CMotoCtrlIce( CHostIceThread * owner )
: CMotoViewIce( owner )
{
}

CMotoCtrlIce::~CMotoCtrlIce()
{
}


void CMotoCtrlIce::setMoto(::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period, const ::Ice::Current & c )
{
    m_owner->m_moto->setMoto( dir1, dir2, period );
}

void CMotoCtrlIce::setServo(::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Current & c )
{
    m_owner->m_moto->setServo( servo1, servo2 );
}

