
#include "moto_view_ice.h"
#include "host_ice_thread.h"
#include "moto_ctrl.h"

CMotoViewIce::CMotoViewIce( CHostIceThread * owner )
: ::Host::CMoto(),
  m_owner( owner )
{
    //m_motoEn  = false;
    //m_servoEn = false;
    //m_dir1    = 0;
    //m_dir1    = 0;
    //m_servo1  = 0.0;
    //m_servo2  = 0.0;
}

CMotoViewIce::~CMotoViewIce()
{
}

bool CMotoViewIce::isOpen(const ::Ice::Current& c )
{
    return m_owner->m_moto->isOpen();
}

bool CMotoViewIce::motoEn(const ::Ice::Current& c )
{
    return m_owner->m_moto->motoEn();
}

void CMotoViewIce::moto(::Ice::Int & dir1, ::Ice::Int & dir2, const ::Ice::Current& c )
{
    m_owner->m_moto->moto( dir1, dir2 );
}

bool CMotoViewIce::servoEn(const ::Ice::Current& c )
{
    return m_owner->m_moto->servoEn();
}

void CMotoViewIce::servo( ::Ice::Double & servo1, ::Ice::Double & servo2, const ::Ice::Current& c )
{
    m_owner->m_moto->servo( servo1, servo2 );
}

void CMotoViewIce::setMoto( ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period, const ::Ice::Current& c )
{
}

void CMotoViewIce::setServo( ::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Current& c )
{
}


bool CMotoViewIce::open(const ::Ice::Current& c )
{
    return false;
}

void CMotoViewIce::close(const ::Ice::Current& c )
{
}

void CMotoViewIce::setMotoEn(bool en, const ::Ice::Current& c )
{
}

void CMotoViewIce::setServoEn(bool en, const ::Ice::Current& c )
{
}




