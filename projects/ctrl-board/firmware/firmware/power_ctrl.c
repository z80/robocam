
#include "power_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "led_ctrl.h"
#include "light_ctrl.h"
#include "moto_ctrl.h"
#include "i2c_slave_ctrl.h"
#include "conv_ctrl.h"

// #include <stdlib.h>

#define JUST_PS_PORT       GPIOB
#define JUST_PS_PIN        15
#define SECONDS_PER_DAY   86400
#define MAX_WAKEUPS_CNT   20

static Mutex mutex;
static int activeTime    = ( 3 * 60 );
static int timeout       = ( 3 * 60 );

static RTCTime  rtcTime;
static uint32_t secondsPerDay = SECONDS_PER_DAY;
static int32_t wakeups[ MAX_WAKEUPS_CNT ];
static uint8_t wakeupsCnt = 3;
static BinarySemaphore rtcSem;

static void rtcCb( RTCDriver * rtcp, rtcevent_t event );
inline uint8_t justPs( void );

void setPowerTimeout( int newActiveTime )
{
    chMtxLock( &mutex );
        activeTime = newActiveTime;
    chMtxUnlock();
}

void powerOffReset( void )
{
    chMtxLock( &mutex );
        timeout = activeTime;
    chMtxUnlock();
}

static void setPower( bool_t en )
{
   if ( !en )
   {
       setLight( 0 );
       motoSet( 0 );
       motoSetEn( 0 );
       setLed( 0 );
   }
   if ( !en )
       stopI2cSlave();
   convSetBuckEn( en ? 1 : 0 );
   if ( en )
   {
       // Wait for some time and turn I2C on after that.
       chThdSleepMilliseconds( 15000 );
       startI2cSlave();
   }
}

void powerHandler( void )
{
    chRegSetThreadName( "p" );

    // Just after enabling don't power on immediately.
    // Give some time to attach all wires.
    chThdSleepMilliseconds( 5000 );

    while ( 1 )
    {
        // If not pure source wait for appropriate time to
        // turn power on.
        if ( !justPs() )
            chBSemWait( &rtcSem );

        // Power on.
        setPower( 1 );
        // Wait for next power off.
        chMtxLock( &mutex );
            timeout = activeTime;
        chMtxUnlock();
        while ( 1 )
        {
            chThdSleepSeconds( 1 );
            if ( !justPs() )
            {
                chMtxLock( &mutex );
                    int t = timeout;
                chMtxUnlock();
                t--;
                chMtxLock( &mutex );
                    timeout = t;
                chMtxUnlock();
                if ( t<=0 )
                    break;
            }
        }
        // Power off.
        setPower( 0 );
    }
}

void initPower( void )
{
    // Initializing real time clock.
    chBSemInit( &rtcSem, TRUE );

    // Some initial setup for wakeups.
    wakeups[0] = 10 * 60 * 60;
    wakeups[1] = 14 * 60 * 60;
    wakeups[2] = 21 * 60 * 60;
    wakeupsCnt = 3;

    // Set RTC callback.
    rtcSetCallback( &RTCD1, rtcCb );

    // Reset RTC time.
    RTCTime t;
    t.tv_sec  = 0;
    t.tv_msec = 0;
    rtcSetTime( &RTCD1, &t );

    // Starting power converters.
    convStart();

    // Just power source mode check pin.
    palSetPadMode( JUST_PS_PORT, JUST_PS_PIN,  PAL_MODE_INPUT );

    chMtxInit( &mutex );
    setPower( 0 );
}

void setSecondsPerDay( uint32_t cnt )
{
    chSysLock();
        secondsPerDay = cnt;
    chSysUnlock();
}

void setCurrentTime( int32_t t )
{
    rtcGetTime( &RTCD1, &rtcTime );
    rtcTime.tv_sec = t;
    rtcSetTime( &RTCD1, &rtcTime );
}

uint32_t currentTime( void )
{
    rtcGetTime( &RTCD1, &rtcTime );
    return rtcTime.tv_sec;
}

void setWakeupsCnt( uint16_t cnt )
{
    chSysLock();
        wakeupsCnt = cnt;
    chSysUnlock();
}

void setWakeup( uint8_t index, int32_t t )
{
    chSysLock();
        wakeups[index] = t;
    chSysUnlock();
}


inline uint8_t justPs( void )
{
    if ( palReadPad( JUST_PS_PORT, JUST_PS_PIN ) )
        return 0;
    return 1;
}

static void rtcCb( RTCDriver * rtcp, rtcevent_t event )
{
    (void)rtcp;
    static RTCTime t;
    int i;

    switch (event)
    {
    case RTC_EVENT_OVERFLOW:
        break;
    case RTC_EVENT_SECOND:
        chSysLockFromIsr();
            rtcGetTimeI( &RTCD1, &t );
        chSysUnlockFromIsr();
        if ( t.tv_sec < secondsPerDay )
        {
            chSysLockFromIsr();
                for ( i=wakeupsCnt-1; i>=0; i-- )
                {
                    static int32_t dt;
                    dt = t.tv_sec - wakeups[i];
                    // If wakeuptime is passed but not quite much.
                    if ( ( dt >= 0 ) && ( dt < 5 ) )
                    {
                        // Command to turn power on.
                        chBSemSignalI( &rtcSem );
                        break;
                    }
                }
            chSysUnlockFromIsr();
        }
        else
        {
            t.tv_sec -= secondsPerDay;
            chSysLockFromIsr();
                rtcSetTimeI( &RTCD1, &t );
            chSysUnlockFromIsr();
        }
        break;
    case RTC_EVENT_ALARM:
        break;
    }
}






