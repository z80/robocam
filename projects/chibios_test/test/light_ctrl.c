
#include "light_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "hdw_cfg.h"


void setLight( bool_t en )
{
    if ( en )
        palSetPad( LED_PORT, LED_PIN );
    else
        palClearPad( LED_PORT, LED_PIN );
    // Configure pin to be output.
    palSetPadMode( LED_PORT, LED_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}

void cmd_light( BaseChannel *chp, int argc, char * argv [] )
{
	(void)chp;
    if ( argc > 0 )
    {
        if ( argv[0][0] != '0' )
            setLight( 1 );
        else
            setLight( 0 );
    }
}



