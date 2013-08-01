
#include "osc_ctrl.h"
#include "hal.h"
#include "i2c_slave_conf.h"
#include "conv_ctrl.h"

static WORKING_AREA( waExec, 128 );
static msg_t execThread( void *arg );


#define SIG_CURR   1 // Current through battery.
#define SIG_BATT   2 // Battery voltage.
#define SIG_TEMP   4 // Temperature.
static uint8_t  signals = (SIG_CURR | SIG_TEMP);
static uint16_t index       = 0;
static uint16_t measuresCnt = 0;
static uint16_t measurePeriod = 60;

uint16_t measures[ OSC_SIZE ];

static Mutex    mutex;

void initOsc( void )
{
    chMtxInit( &mutex );
    chThdCreateStatic( waExec, sizeof(waExec), NORMALPRIO, execThread, NULL );
}

void oscSetup( uint16_t period, uint8_t sigs )
{
    chMtxLock( &mutex );
        measurePeriod = period;
        signals       = sigs;
        index         = 0;
        measuresCnt   = 0;
    chMtxUnlock();
}

uint16_t oscMeasuresCnt( uint8_t * sigs )
{
    chMtxLock( &mutex );
        uint16_t res = measuresCnt;
        if ( sigs )
            *sigs = signals;
    chMtxUnlock();
    return res;
}

uint16_t oscValue( uint16_t ind )
{
    static uint16_t i;
    chMtxLock( &mutex );
        i = index + OSC_SIZE - ind - 1;
    chMtxUnlock();
    i = i % OSC_SIZE;
    i = measures[ i ];
    return i;
}

static msg_t execThread( void *arg )
{
    (void)arg;
    while ( 1 )
    {
        // Measure
        static uint8_t sigs;
        static uint16_t ind;
        static uint16_t cnt;

        static uint16_t val;
        if ( sigs & SIG_CURR )
        {
            val = adcCurrent();
            measures[ ind ] = val;
            ind = ( ind + 1 ) % OSC_SIZE;
            cnt++;
        }
        if ( sigs & SIG_BATT )
        {
            val = adcBoostFb();
            measures[ ind ] = val;
            ind = ( ind + 1 ) % OSC_SIZE;
            cnt++;
        }
        if ( sigs & SIG_TEMP )
        {
            val = adcTemperature();
            measures[ ind ] = val;
            ind = ( ind + 1 ) % OSC_SIZE;
            cnt++;
        }
        cnt = ( cnt < OSC_SIZE ) ? cnt : OSC_SIZE;

        static int period;
        chMtxLock( &mutex );
            index       = ind;
            measuresCnt = cnt;
            period      = measurePeriod;
        chMtxUnlock();

        // Delay
        chThdSleepSeconds( period );
    }
    return 0;
}






