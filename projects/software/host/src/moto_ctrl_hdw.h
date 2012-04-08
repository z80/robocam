
#ifndef __MOTO_CTRL_HDW_H_
#define __MOTO_CTRL_HDW_H_

#include "moto_ctrl.h"
#include "hdw.h"
class CHostIceThread;
class CMotoThreadHdw;

class CMotoCtrlHdw: public CMotoCtrl
{
public:
    CMotoCtrlHdw( CHostIceThread * owner, Hdw::CHdwPrx hdwPrx );
    ~CMotoCtrlHdw();

    bool isOpen();
    bool motoEn();
    void moto( ::Ice::Int & dir1, ::Ice::Int & dir2 );
    bool servoEn();
    void servo( ::Ice::Double & servo1, ::Ice::Double & servo2 );
    void setMoto( ::Ice::Int dir1, ::Ice::Int dir2, ::Ice::Double period );
    void setServo( ::Ice::Double servo1, ::Ice::Double servo2 );
    bool open();
    void close();
    void setMotoEn( bool en );
    void setServoEn( bool en );

protected:
    void checkPowerState();
    Hdw::CMotoPrx m_motoPrx;
    std::string m_deviceName;
    bool m_powerState;

    ::IceUtil::Mutex m_mut;
    CMotoThreadHdw * m_motoThread;
    friend class CMotoThreadHdw;
};


#endif



