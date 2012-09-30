
#include "light_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

void cmd_light( BaseChannel *chp, int argc, char * argv [] )
{
    if ( argc > 0 )
    {
        if ( argv[0][0] != '0' )
        {
            palSetPad( LED_PORT, LED_PIN );
        }
        else
        {
            palClearPad( LED_PORT, LED_PIN );
        }
    }
}



