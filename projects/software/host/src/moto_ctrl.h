
#ifndef __MOTO_CTRL_H_
#define __MOTO_CTRL_H_

#include "host.h"
class CHostIceThread;

class CMotoCtrl
{
public:
    CMotoCtrl( CHostIceThread * owner );
	virtual ~CMotoCtrl();

    virtual bool isOpen() = 0;
    virtual bool motoEn() = 0;
    virtual void moto( ::Ice::Int & dir1, ::Ice::Int & dir2 ) = 0;
    virtual bool servoEn() = 0;
    virtual void servo( ::Ice::Double & servo1, ::Ice::Double & servo2 ) = 0;
    virtual void setMoto( ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period ) = 0;
    virtual void setServo( ::Ice::Double servo1, ::Ice::Double servo2 ) = 0;
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual void setMotoEn( bool en ) = 0;
    virtual void setServoEn( bool en ) = 0;
protected:
    CHostIceThread * m_owner;
    friend class CMotoCtrlHdw;
    friend class CMotoCtrlEml;
};


#endif



