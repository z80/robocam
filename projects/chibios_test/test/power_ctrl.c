
#include "power_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "light_ctrl.h"
#include "moto_ctrl.h"
#include "hdw_cfg.h"

#include <stdlib.h>

static Mutex g_mutex;
int g_firstOnDelay = (60 * 60 * 2);
int g_onDelay      = (60 * 60 * 2);
int g_offDelay     = ( 30 );
int g_nextOnDelay;
int g_timer        = 0;

void powerConfig( int onFirst, int on, int off )
{
    chMtxLock( &g_mutex );
    g_firstOnDelay = onFirst;
    g_onDelay      = on;
    g_offDelay     = off;
    chMtxUnlock();
}

void powerOffReset( void )
{
    chMtxLock( &g_mutex );
    g_timer = g_offDelay;
    // Of it was reset at least once, means computer performed something.
    // And it most probably means we need more recharge time.
    g_nextOnDelay = g_firstOnDelay;
    chMtxUnlock();
}

static void setPower( bool_t en )
{
   if ( en )
       palSetPad( PWR_PORT, PWR_PIN );
       // initUsb();
   else
   {
       palClearPad( PWR_PORT, PWR_PIN );
       setLight( 0 );
       motoConfig( 0, 3 );
       // finitUsb();
   }
   palSetPadMode( PWR_PORT, PWR_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}

void cmd_pwr_rst( BaseChannel *chp, int argc, char * argv [] )
{
	(void)chp;
	(void)argc;
	(void)argv;
	powerOffReset();
}

void cmd_pwr_cfg( BaseChannel *chp, int argc, char * argv [] )
{
	(void)chp;
	if ( argc > 0 )
	{
		chMtxLock( &g_mutex );
		int res = atoi( argv[0] );
		g_firstOnDelay = res;
		if ( argc > 1 )
		{
			res = atoi( argv[1] );
			g_onDelay = res;
			if ( argc > 2 )
			{
				res = atoi( argv[2] );
				g_offDelay = res;
			}
		}
		chMtxUnlock();
	}
}


static WORKING_AREA( waPower, 256 );
static msg_t Power( void *arg )
{
    (void)arg;
    setPower( 0 );
    chRegSetThreadName( "power" );
    while (TRUE)
    {
        // First wait for power on.
        g_timer = g_firstOnDelay;
        while ( g_timer-- > 0 )
            chThdSleepSeconds( 1 );
        // Power on.
POWER_LOOP:
        g_nextOnDelay = g_offDelay;
        setPower( 1 );
        chMtxLock( &g_mutex );
        g_timer = g_offDelay;
        int t = g_timer;
        chMtxUnlock();
        while ( t > 0 )
        {
            chThdSleepSeconds( 1 );
            chMtxLock( &g_mutex );
            g_timer--;
            t = g_timer;
            chMtxUnlock();
        }
        setPower( 0 );
        // Wait for next power on.
        g_timer = g_nextOnDelay;
        while ( g_timer-- > 0 )
            chThdSleepSeconds( 1 );
        goto POWER_LOOP;
    }
    return 0;
}

void initPower( void )
{
    chMtxInit( &g_mutex );
    setPower( 0 );

    chThdCreateStatic( waPower, sizeof(waPower), NORMALPRIO, Power, NULL );
}





