
#include "mcu_ctrl.h"

#include <iostream>
#include <boost/regex.hpp>

int main( int argc, char * argv[] )
{
    std::string text(" bababa ba {123 567 } { 12 45} ");
    std::string pattern = "\\{\\b{0,}\\d{0,}\\b{0,}";
    boost::regex patt( pattern );

    boost::sregex_iterator it( text.begin(), text.end(), patt );
    boost::sregex_iterator end;
    for ( ; it!=end; ++it )
    {
        std::cout << it->str() << "\n";
        // v.push_back(it->str()); or something similar
    }

    //McuCtrl c;
    //bool res = c.open();
    //if ( !res )
    //    return 1;

    //std::string stri;
    //stri.resize( 128 );
    //int cnt = c.read( stri );
    //cnt = c.write( "mem\r\n" );
    //cnt = c.read( stri );
    //cnt = c.read( stri );

    //bool r = c.led( true );
    //r = c.motoConfig( false, 3 );
    //r = c.motoReset();
    //r = c.adcConfig( true );
    //int val1, val2;
    //r = c.adc( val1, val2 );

    return 0;
}

