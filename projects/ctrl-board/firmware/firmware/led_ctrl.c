
#include "led_ctrl.h"
#include "hal.h"

uint8_t leds = 0;
static void applyLed( uint16_t arg );

static WORKING_AREA( waLeds, 256 );
static msg_t Leds( void *arg )
{
    (void)arg;

    chRegSetThreadName( "pwr" );

    // Configure LED outputs.
    palSetPadMode( GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL );

    while ( 1 )
    {
        applyLed( 0 );
        chThdSleepMilliseconds( 100 );

        applyLed( 3 );
        chThdSleepMilliseconds( 100 );

        applyLed( leds );
        chThdSleepMilliseconds( 800 );

    }
    return 0;
}


void initLed( void )
{
    // Configure LED outputs.
    palSetPadMode( GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL );

    palClearPad( GPIOB, 13 );
    palClearPad( GPIOB, 14 );

    chThdCreateStatic( waLeds, sizeof(waLeds), NORMALPRIO, Leds, NULL );
}

void setLed( uint32_t arg )
{
    leds = arg;
    applyLed( arg );
}

static void applyLed( uint16_t arg )
{
    if ( arg & 1 )
        palSetPad( GPIOB, 13 );
    else
        palClearPad( GPIOB, 13 );

    if ( arg & 2 )
        palSetPad( GPIOB, 14 );
    else
        palClearPad( GPIOB, 14 );
}



