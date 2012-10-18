
#ifndef __MCU_CTRL_H_
#define __MCU_CTRL_H_

#include "usb_io.h"

class McuCtrl: public UsbIo
{
public:
	McuCtrl();
	~McuCtrl();

	bool powerOffReset();
	bool powerConfig( int onFirst, int onRegular, int off );
    bool powerEn( bool en );

    bool motoConfig( bool en, int val );
    bool moto( bool moto1, bool moto2, bool moto3, bool moto4 );
    bool motoReset();

    bool led( bool en );

    bool adcConfig( bool en );
    bool adc( int & solar, int & battery );

};


#endif





