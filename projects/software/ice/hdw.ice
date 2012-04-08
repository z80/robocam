
#ifndef __HDW_ICE_
#define __HDW_ICE_

#include "types.ice"

module Hdw
{
    class CMoto
    {
        bool open();
        bool isOpen();
        void close();
        
        void setMotoEn( bool en );
        bool motoEn();
        void setMoto( int dir1, int dir2, int period );
        void moto( out int dir1, out int dir2 );

        void setServoEn( bool en );
        bool servoEn();
        void setServo( int servo1, int servo2 );
        void servo( out int servo1, out int servo2 );
        
        void setWatchdog( int period );
        void resetWatchdog();
    };

    class CCam
    {
        void setDeviceName( string devName );
        bool open();
        bool isOpen();
        void close();
        bool capabilities( out Types::TStringArray cap, out Types::TBoolArray en, out Types::TStringArray info );
        bool formats( out Types::TStringArray fmt, out Types::TLongArray fourcc );
        Types::TIntArray resolutions();
        bool initDevice( bool streaming, long fourcc, int width, int height, int fps );
        void imageSize( out int width, out int height, out int bufferSize );
        bool startCapture();
        void stopCapture();
        bool started();
        bool acquire();
        bool release();
        void data( int from, int sz, out Types::TByteArray res );
        string lastError();
        // Тут скорее всего сжатие будет во временный файл.
    };

    class CLua
    {
        bool exec( string stri );
    };

    class CHdw
    {
        CMoto * moto();
        CCam  * cam();
        //CLua  * lua();
    };
};

#endif

