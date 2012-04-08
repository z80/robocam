
#ifndef __MOTO_CTRL_ICE_H_
#define __MOTO_CTRL_ICE_H_

#include "host.h"
#include "moto_view_ice.h"

class CMotoCtrlIce: public CMotoViewIce
{
public:
    CMotoCtrlIce( CHostIceThread * owner );
    ~CMotoCtrlIce();

    virtual void setMoto(::Ice::Int, ::Ice::Int, ::Ice::Double, const ::Ice::Current& = ::Ice::Current() );
    virtual void setServo(::Ice::Double, ::Ice::Double, const ::Ice::Current& = ::Ice::Current() );

protected:
    friend class CMotoSuperIce;
};

#endif

