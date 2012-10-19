
#include "mcu_ctrl.h"

#include <iostream>
#include <sstream>
#include <boost/regex.hpp>

int main( int argc, char * argv[] )
{
    /*std::string text(" bababa ba {123 567 } { 12 45} ");

    int adc1 = -1, adc2 = -1;
    {
        boost::regex patt( "\\{ {0,}\\d+" );
        boost::sregex_iterator it( text.begin(), text.end(), patt );
        boost::sregex_iterator end;
        for ( ; it!=end; ++it )
        {
            std::cout << it->str() << "\n";
            std::string stri = it->str().substr( 1 );
            std::istringstream in( stri );
            in >> adc1;
            // v.push_back(it->str()); or something similar
        }
    }
    {
        boost::regex patt( "\\d+ {0,}\\}" );
        boost::sregex_iterator it( text.begin(), text.end(), patt );
        boost::sregex_iterator end;
        for ( ; it!=end; ++it )
        {
            std::cout << it->str() << "\n";
            std::string stri = it->str();
            std::istringstream in( stri );
            in >> adc2;
            // v.push_back(it->str()); or something similar
        }
    }
    std::cout << "adc1: " << adc1 << "\n";
    std::cout << "adc2: " << adc2 << "\n";*/

    McuCtrl c;
    bool res = c.open();
    if ( !res )
        return 1;

    //std::string stri;
    //stri.resize( 128 );
    //int cnt = c.read( stri );
    //cnt = c.write( "mem\r\n" );
    //cnt = c.read( stri );
    //cnt = c.read( stri );

    bool r;
    r = c.powerEn( true );
    r = c.led( true );
    r = c.led( false );
    r = c.motoConfig( true, 30 );
    int val;
    r = c.motoSet( true, true, true, true );
    r = c.moto( val );
    r = c.motoSet( true, false, true, false );
    r = c.moto( val );
    r = c.motoSet( true, false, false, false );
    r = c.moto( val );
    r = c.motoSet( true, true, true, true );
    r = c.moto( val );
    //r = c.motoReset();
    r = c.motoConfig( false, 3 );
    r = c.adcConfig( true );
    int val1, val2;
    r = c.adc( val1, val2 );
    r = c.powerEn( false );

    return 0;
}

