
#ifndef __CAM_CTRL_ICE_H_
#define __CAM_CTRL_ICE_H_

#include "cam_view_ice.h"
class CHostIceThread;

class CCamCtrlIce: public CCamViewIce
{
public:
    CCamCtrlIce( CHostIceThread * owner );
    ~CCamCtrlIce();

    virtual void setPeriod(::Ice::Double, const ::Ice::Current& = ::Ice::Current());
    virtual void setReceiveImages(bool en, const ::Ice::Current& = ::Ice::Current() );
protected:
    friend class CCamSuperIce;
};


#endif
