
#ifndef __MOTO_SUPER_ICE_H_
#define __MOTO_SUPER_ICE_H_

#include "host.h"
#include "moto_ctrl_ice.h"
class CHostIceThread;

class CMotoSuperIce: public CMotoCtrlIce
{
public:
    CMotoSuperIce( CHostIceThread * owner );
    ~CMotoSuperIce();

    bool open(const ::Ice::Current& = ::Ice::Current());
    void close(const ::Ice::Current& = ::Ice::Current());
    void setMotoEn(bool, const ::Ice::Current& = ::Ice::Current());
    void setServoEn(bool, const ::Ice::Current& = ::Ice::Current());
};

#endif

