
#ifndef __MOTO_ICE_H_
#define __MOTO_ICE_H_

#include "hdw.h"
class CMotoCtrl;

class CMotoIce: public Hdw::CMoto
{
public:
    CMotoIce( CMotoCtrl * moto );
    ~CMotoIce();

    bool open(const ::Ice::Current& = ::Ice::Current());
    bool isOpen(const ::Ice::Current& = ::Ice::Current());
    void close(const ::Ice::Current& = ::Ice::Current());
    void setMotoEn(bool, const ::Ice::Current& = ::Ice::Current());
    bool motoEn(const ::Ice::Current& = ::Ice::Current());
    void setMoto(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current());
    void moto(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current());
    void setServoEn(bool, const ::Ice::Current& = ::Ice::Current());
    bool servoEn(const ::Ice::Current& = ::Ice::Current());
    void setServo(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current());
    void servo(::Ice::Int&, ::Ice::Int&, const ::Ice::Current& = ::Ice::Current());

    void setWatchdog( ::Ice::Int period, const ::Ice::Current& = ::Ice::Current() );
    void resetWatchdog( const ::Ice::Current& = ::Ice::Current() );
private:
    CMotoCtrl * m_motoCtrl;
    int m_dir1, 
        m_dir2, 
        m_servo1, 
        m_servo2;
};


#endif


