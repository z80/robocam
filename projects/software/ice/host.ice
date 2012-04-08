
#ifndef __HOST_ICE_
#define __HOST_ICE_

#include <IceE/Identity.ice>
#include "types.ice"
#include "client.ice"

module Host
{
    // Тут вызовы со стороны Hardware, если требуется.
    // И со стороны клиентов.
    
    class CMoto
    {
        idempotent bool isOpen();
        
        idempotent bool motoEn();
        idempotent void moto( out int dir1, out int dir2 );
        
        idempotent bool servoEn();
        idempotent void servo( out double servo1, out double servo2 );

        ["ami"] void setMoto( int dir1, int dir2, double period );
        ["ami"] void setServo( double servo1, double servo2 );

        bool open();
        void close();
        void setMotoEn( bool en );
        void setServoEn( bool en );
    };
    
    class CCam
    {
        idempotent bool isOpen();
        void setResolution( int width, int height );
        idempotent void resolution( out int width, out int height );
        idempotent double period();
        idempotent bool image( out ::Types::TByteArray data );
        void setReceiveImages( bool en );
        idempotent bool receiveImages();
        idempotent string deviceName();

        void setPeriod( double period );

        void setDeviceName( string devName );
        bool open();
        void close();
    };
    
    // Вызывается клиентами.
    class CHost
    {
        bool registerClient( ::Client::CClient * client, string nickname, out string idOrErrMsg );
        void removeClient( string id );
        ["ami", "amd"] void postMessage( string id, string stri );
        bool queryCtrl( string id );
        bool querySuper( string id, string password );
        void releaseCtrl( string id );
        
        CCam  * cam( string id );
        CMoto * moto( string id );
    };
};


#endif

