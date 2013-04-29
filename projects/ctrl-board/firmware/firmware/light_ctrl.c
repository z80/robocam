
#include "light_ctrl.h"
#include "ch.h"
#include "hal.h"

#define LIGHT_PORT  GPIOB
#define LIGHT_PIN   12

void setLight( bool_t en )
{
    if ( en )
        palSetPad( LIGHT_PORT, LIGHT_PIN );
    else
        palClearPad( LIGHT_PORT, LIGHT_PIN );
    // Configure pin to be output.
    palSetPadMode( LIGHT_PORT, LIGHT_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}




