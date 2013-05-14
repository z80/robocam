
#include "led_ctrl.h"
#include "hal.h"

void initLed( void )
{
    // Configure LED outputs.
    palSetPadMode( GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL );

    palClearPad( GPIOB, 13 );
    palClearPad( GPIOB, 14 );
}

void setLed( uint32_t arg )
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



