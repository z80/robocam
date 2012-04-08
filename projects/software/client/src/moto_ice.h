
#ifndef __MOTO_ICE_H_
#define __MOTO_ICE_H_

#include "client.h"
class CClientIceThread;

class CMotoIce: public ::Client::CMoto
{
public:
    CMotoIce( CClientIceThread * owner );
    ~CMotoIce();

    void acceptMotoEn( bool en, const ::Ice::Current& c );
    void acceptMoto( ::Ice::Int, ::Ice::Int, const ::Ice::Current& c );
    void acceptServoEn( bool, const ::Ice::Current& c );
    void acceptServo( ::Ice::Double, ::Ice::Double, const ::Ice::Current& c );

private:
    CClientIceThread * m_owner;
};

#endif


