
#include "mcu_ctrl.h"
#include <sstream>
#include <boost/regex.hpp>

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

bool McuCtrl::powerEn( bool en )
{
    std::ostringstream out;
    out << "poweren ";
    out << ( en ) ? "1" : "0";
    out << "\r\n";
    std::string stri = out.str();
    int cntWr = write( stri );
    int cntRd = read( stri );
    return ( ( cntWr > 0) && ( cntRd >= cntWr ) );
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
    std::string text = out.str();
    int cntWr = write( text );
    int cntRd = read( text );
    bool res = ( ( cntWr > 0 ) && ( cntRd >= cntWr ) );
    solar = -1;
    battery = -1;
    if ( !res )
        return false;
    // Get values from result string. Values are between "{" and "}".
    {
        boost::regex patt( "\\{ {0,}\\d+" );
        boost::sregex_iterator it( text.begin(), text.end(), patt );
        boost::sregex_iterator end;
        for ( ; it!=end; ++it )
        {
            //std::cout << it->str() << "\n";
            std::string stri = it->str().substr( 1 );
            std::istringstream in( stri );
            in >> solar;
        }
    }
    {
        boost::regex patt( "\\d+ {0,}\\}" );
        boost::sregex_iterator it( text.begin(), text.end(), patt );
        boost::sregex_iterator end;
        for ( ; it!=end; ++it )
        {
            //std::cout << it->str() << "\n";
            std::string stri = it->str();
            std::istringstream in( stri );
            in >> battery;
        }
    }
    std::cout << "solar:   " << solar   << "\n";
    std::cout << "battery: " << battery << "\n";

    return res;
}







