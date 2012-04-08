
#ifndef __MOTO_CTRL_H_
#define __MOTO_CTRL_H_

#include "usb_io.h"

class CMotoCtrl: public CUsbIo
{
public:
    CMotoCtrl();
    ~CMotoCtrl();

    void setMotoEn( bool en );
    bool motoEn() const;
    void setMoto( int dir1, int dir2 );
    void setServoEn( bool en );
    bool servoEn() const;
    void setServo( int val1, int val2 );
    void setWatchdog( int period );
    void resetWatchdog();
private:
    bool m_motoEn,
         m_servoEn;
    std::string m_res;
};

#endif

