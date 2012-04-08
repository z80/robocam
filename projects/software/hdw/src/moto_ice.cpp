
#include "moto_ice.h"
#include "moto_ctrl.h"

//#include <stdio.h>
//#define debug printf

CMotoIce::CMotoIce( CMotoCtrl * moto )
: Hdw::CMoto(), 
  m_motoCtrl( moto )
{
    m_dir1 = m_dir2 = m_servo1 = m_servo2 = 0;
    //debug( "constructor()\n" );
}

CMotoIce::~CMotoIce()
{
    m_motoCtrl->close();
    //debug( "destructor()\n" );
}

bool CMotoIce::open(const ::Ice::Current & c )
{
    bool res = m_motoCtrl->open();
    //debug( "open()->%s\n", res ? "true" : "false" );
    return res;
}

bool CMotoIce::isOpen( const ::Ice::Current & c )
{
    bool res = m_motoCtrl->isOpen();
    //debug( "isOpen()->%s\n", res ? "true" : "false" );
    return res;
}

void CMotoIce::close( const ::Ice::Current & c )
{
    m_motoCtrl->close();
    //debug( "close()\n" );
}

void CMotoIce::setMotoEn( bool en, const ::Ice::Current & c )
{
    m_motoCtrl->setMotoEn( en );
    //debug( "setMotoEn( %s )\n", en ? "true" : "false" );
}

bool CMotoIce::motoEn( const ::Ice::Current & c )
{
    bool res = m_motoCtrl->motoEn();
    //debug( "motoEn()->%s\n", res ? "true" : "false" );
    return res;
}

void CMotoIce::setMoto( ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Int period, const ::Ice::Current & c )
{
    m_dir1 = dir1;
    m_dir2 = dir2;
    m_motoCtrl->setMoto( dir1, dir2 );
    //debug( "setMoto( %i, %i )\n", dir1, dir2 );
}

void CMotoIce::moto( ::Ice::Int & dir1, ::Ice::Int & dir2, const ::Ice::Current & c )
{
    dir1 = m_dir1;
    dir2 = m_dir2;
    //debug( "moto()->%i, %i\n", dir1, dir2 );
}

void CMotoIce::setServoEn( bool en, const ::Ice::Current & c )
{
    if ( !en )
        m_motoCtrl->setServo( 0, 0 );
    m_motoCtrl->setServoEn( en );
    if ( en )
    	m_motoCtrl->setServo( m_servo1, m_servo2 );
    //debug( "setServoEn( %s )\n", en ? "true" : "false" );
}

bool CMotoIce::servoEn(const ::Ice::Current & c )
{
    bool res = m_motoCtrl->servoEn();
    //debug( "servoEn()->%s\n", res ? "true" : "false" );
    return res;
}

void CMotoIce::setServo( ::Ice::Int servo1, ::Ice::Int servo2, const ::Ice::Current & c )
{
    m_servo1 = servo1;
    m_servo2 = servo2;
    m_motoCtrl->setServo( servo1, servo2 );
    //debug( "setServo( %i, %i )\n", servo1, servo2 );
}

void CMotoIce::servo( ::Ice::Int & servo1, ::Ice::Int & servo2, const ::Ice::Current & c )
{
    servo1 = m_servo1;
    servo2 = m_servo2;
    //debug( "servo()->%i, %i\n", servo1, servo2 );
}

void CMotoIce::setWatchdog( ::Ice::Int period, const ::Ice::Current & c )
{
    m_motoCtrl->setWatchdog( period );
    //debug( "setWatchdog( %i )\n", period );
}

void CMotoIce::resetWatchdog( const ::Ice::Current & c )
{
    m_motoCtrl->resetWatchdog();
    //debug( "resetWatchdog()\n" );
}









