
#ifndef __MOTO_VIEW_ICE_H_
#define __MOTO_VIEW_ICE_H_

#include "host.h"
class CHostIceThread;

class CMotoViewIce: public ::Host::CMoto
{
public:
    CMotoViewIce( CHostIceThread * owner );
    ~CMotoViewIce();

    virtual bool isOpen(const ::Ice::Current& = ::Ice::Current());
    virtual bool motoEn(const ::Ice::Current& = ::Ice::Current());
    virtual void moto(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current());
    virtual bool servoEn(const ::Ice::Current& = ::Ice::Current());
    virtual void servo(::Ice::Double&, ::Ice::Double&, const ::Ice::Current& = ::Ice::Current());

    virtual void setMoto(::Ice::Int, ::Ice::Int, ::Ice::Double, const ::Ice::Current& = ::Ice::Current());
    virtual void setServo(::Ice::Double, ::Ice::Double, const ::Ice::Current& = ::Ice::Current());

    virtual bool open(const ::Ice::Current& = ::Ice::Current());
    virtual void close(const ::Ice::Current& = ::Ice::Current());
    virtual void setMotoEn(bool, const ::Ice::Current& = ::Ice::Current());
    virtual void setServoEn(bool, const ::Ice::Current& = ::Ice::Current());

protected:
    CHostIceThread * m_owner;
    friend class CMotoCtrlIce;
    friend class CMotoSuperIce;

    //bool m_opened;
    //bool m_motoEn;
    //bool m_servoEn;
    //int  m_dir1;
    //int  m_dir2;
    //double m_servo1;
    //double m_servo2;
};

#endif

