
#ifndef __CLIENT_ICE_
#define __CLIENT_ICE_

#include "types.ice"

module Client
{
    class CChat
    {
        void acceptMessage( string stri );
        void acceptClientList( Types::TStringArray list, string driverNickname );
    };
    
    class CMoto
    {
        void acceptMotoEn( bool en );
        void acceptMoto( int dir1, int dir2 );
        void acceptServoEn( bool en );
        void acceptServo( double servo1, double servo2 );
    };
    
    class CCam
    {
        void acceptImage( Types::TByteArray image );
        void acceptResolution( int width, int height );
        void acceptPeriod( double value );
    };
    
    class CClient
    {
        CChat * chat();
        CMoto * moto();
        CCam  * cam();
    };
};

#endif


