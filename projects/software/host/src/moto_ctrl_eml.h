
#ifndef __MOTO_CTRL_EML_H_
#define __MOTO_CTRL_EML_H_

#include "moto_ctrl.h"
class CHostIceThread;

class CMotoCtrlEml: public CMotoCtrl
{
public:
    CMotoCtrlEml( CHostIceThread * owner );
	~CMotoCtrlEml();

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
};


#endif



