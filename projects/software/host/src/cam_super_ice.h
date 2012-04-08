
#ifndef __CAM_SUPER_ICE_H_
#define __CAM_SUPER_ICE_H_

#include "cam_ctrl_ice.h"

class CCamSuperIce: public CCamCtrlIce
{
public:
    CCamSuperIce( CHostIceThread * owner );
    ~CCamSuperIce();

    void setResolution( ::Ice::Int width, ::Ice::Int height, const ::Ice::Current & c );
    void setDeviceName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());
    bool open(const ::Ice::Current& = ::Ice::Current());
    void close(const ::Ice::Current& = ::Ice::Current());
};


#endif

