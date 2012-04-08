
#ifndef __CAM_ICE_H_
#define __CAM_ICE_H_

#include "client.h"

class CClientIceThread;

class CCamIce: public ::Client::CCam
{
public:
    CCamIce( CClientIceThread * owner );
    ~CCamIce();

    void acceptImage( const ::Types::TByteArray & data, const ::Ice::Current& = ::Ice::Current() );
    void acceptResolution( ::Ice::Int width, ::Ice::Int height, const ::Ice::Current& = ::Ice::Current() );
    void acceptPeriod(::Ice::Double, const ::Ice::Current& = ::Ice::Current() );
private:
    CClientIceThread * m_owner;
};

#endif


