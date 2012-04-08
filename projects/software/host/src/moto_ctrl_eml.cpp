
#include "moto_ctrl_eml.h"

CMotoCtrlEml::CMotoCtrlEml( CHostIceThread * owner )
: CMotoCtrl( owner )
{
}

CMotoCtrlEml::~CMotoCtrlEml()
{
}

bool CMotoCtrlEml::isOpen()
{
    return false;
}

bool CMotoCtrlEml::motoEn()
{
    return false;
}

void CMotoCtrlEml::moto( ::Ice::Int & dir1, ::Ice::Int & dir2 )
{
}

bool CMotoCtrlEml::servoEn()
{
    return false;
}

void CMotoCtrlEml::servo( ::Ice::Double & servo1, ::Ice::Double & servo2 )
{
}

void CMotoCtrlEml::setMoto( ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period )
{
}

void CMotoCtrlEml::setServo( ::Ice::Double servo1, ::Ice::Double servo2 )
{
}

bool CMotoCtrlEml::open()
{
    return false;
}

void CMotoCtrlEml::close()
{
}

void CMotoCtrlEml::setMotoEn( bool en )
{
}

void CMotoCtrlEml::setServoEn( bool en )
{
}





