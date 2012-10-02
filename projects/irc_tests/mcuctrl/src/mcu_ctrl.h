
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



};


#endif





