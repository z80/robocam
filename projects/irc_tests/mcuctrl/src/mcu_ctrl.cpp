
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
	const std::string stri = "pwrrst\n";
	int cnt = write( stri );
	return ( cnt == stri.size() );
}

bool McuCtrl::powerConfig( int onFirst, int onRegular, int off )
{
    std::ostringstream out;
    out << "powercfg " << onFirst << " " << onRegular << " " << off << "\n";
    int cnt = write( out.str() );
    return ( cnt == out.str().size() );
}







