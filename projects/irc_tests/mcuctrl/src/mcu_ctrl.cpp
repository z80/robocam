
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

bool McuCtrl::motoConfig( bool en, int val )
{
    std::ostringstream out;
    out << "motocfg ";
    out << (en) ? 1 : 0;
    out << val;
    out << "\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::moto( bool moto1, bool moto2, bool moto3, bool moto4 )
{
    std::ostringstream out;
    out << "moto ";
    out << ( moto1 ? 1 : 0 );
    out << ( moto2 ? 1 : 0 );
    out << ( moto3 ? 1 : 0 );
    out << ( moto4 ? 1 : 0 );
    out << "\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    return ( ( cntWr >= 0 ) && ( cntRd >= cntWr ) );
}

bool McuCtrl::motoReset()
{
    std::ostringstream out;
    out << "motorst\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::led( bool en )
{
    std::ostringstream out;
    out << "led ";
    out << (en) ? 1 : 0;
    out << "\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::adcConfig( bool en )
{
    std::ostringstream out;
    out << "adccfg ";
    out << (en) ? 1 : 0;
    out << "\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::adc( int & solar, int & battery )
{
    std::ostringstream out;
    out << "adc\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    // Get values from result string. Values are between "{" and "}".

    return ( cntRd >= cntWr );
}







