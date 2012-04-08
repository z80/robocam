
#include "moto_ice.h"
#include "client_ice_thread.h"

CMotoIce::CMotoIce( CClientIceThread * owner )
: ::Client::CMoto(), 
  m_owner( owner )
{
}

CMotoIce::~CMotoIce()
{
}

void CMotoIce::acceptMotoEn( bool en, const ::Ice::Current& c )
{
}

void CMotoIce::acceptMoto( ::Ice::Int dir1, ::Ice::Int dir2, const ::Ice::Current& c )
{
}

void CMotoIce::acceptServoEn( bool en, const ::Ice::Current& c )
{
}

void CMotoIce::acceptServo( ::Ice::Double servo1, ::Ice::Double servo2, const ::Ice::Current& c )
{
}


