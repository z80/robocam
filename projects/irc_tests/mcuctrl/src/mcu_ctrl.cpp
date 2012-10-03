
#include "mcu_ctrl.h"
#include <sstream>

McuCtrl::McuCtrl()
: UsbIo()
{

}

McuCtrl::~McuCtrl()
{

}

bool McuCtrl::powerOffReset()
{
	std::string stri = "pwrrst\r\n";
	int cntWr = write( stri );
	int cntRd = read( stri );
	return ( cntRd >= cntWr );
}

bool McuCtrl::powerConfig( int onFirst, int onRegular, int off )
{
    std::ostringstream out;
    out << "powercfg " << onFirst << " " << onRegular << " " << off << "\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}







