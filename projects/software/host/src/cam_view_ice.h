
#ifndef __CAM_VIEW_ICE_H_
#define __CAM_VIEW_ICE_H_

#include "host.h"
#include "cam_ctrl.h"
class CHostIceThread;

class CCamViewIce: public ::Host::CCam
{
public:
    CCamViewIce( CHostIceThread * owner );
    ~CCamViewIce();

    virtual bool isOpen(const ::Ice::Current& = ::Ice::Current());
    virtual void setResolution( ::Ice::Int with, ::Ice::Int height, const ::Ice::Current& = ::Ice::Current());
    virtual void resolution(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current());
    virtual ::Ice::Double period(const ::Ice::Current& = ::Ice::Current());
    virtual bool image( ::Types::TByteArray & data, const ::Ice::Current& = ::Ice::Current());
    virtual void setReceiveImages(bool, const ::Ice::Current& = ::Ice::Current());
    virtual bool receiveImages(const ::Ice::Current& = ::Ice::Current());
    virtual ::std::string deviceName(const ::Ice::Current& = ::Ice::Current());
    virtual void setPeriod(::Ice::Double, const ::Ice::Current& = ::Ice::Current());
    virtual void setDeviceName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());
    virtual bool open(const ::Ice::Current& = ::Ice::Current());
    virtual void close(const ::Ice::Current& = ::Ice::Current());

protected:
    CHostIceThread * m_owner;
    friend class CCamCtrlIce;
    friend class CCamSuperIce;
};

#endif
