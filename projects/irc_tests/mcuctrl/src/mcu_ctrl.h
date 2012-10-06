
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

    bool motoConfig( bool en, int val );
    bool motoReset();

    bool led( bool en );

    bool adcConfig( bool en );
    bool adc( int & solar, int & battery );

};


#endif





