
#include "power_ctrl.h"


Mutex g_mutex;
int g_firstOnDelay = (60 * 60 * 2);
int g_onDelay      = (60 * 60 * 2);
int g_offDelay     = ( 30 );
int g_timer        = 0;

void setPowerOnTimeout( int sec )
{
    chMtxLock( &g_mutex );
    g_onDelay = sec;
    chMtxUnlock( &g_mutex );
}

void setPowerOffTimeout( int sec )
{
    chMtxLock( &g_mutex );
    g_offDelay = sec;
    chMtxUnlock( &g_mutex );
}

void powerOffReset( void )
{
    chMtxLock( &g_mutex );
    g_timer = g_offDelay;
    chMtxUnlock( &g_mutex );
}

static void setPower( BOOL en )
{
   if ( en )
       palSetPad( POWER_PORT, POWER_PIN );
   else
       palClearPad( POWER_PORT, POWER_PIN );
   palSetPadMode( POWER_PORT, POWER_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}

void cmd_power( BaseChannel *chp, int argc, char * argv [] )
{
    if ( argc > 0 )
    {
        if ( argv[0][0] != '0' )
            setPower( 1 );
        else
            setPower( 0 );
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
        setPower( 1 );
        chMtxLock( &g_mutex );
        g_timer = g_offDelay;
        int t = g_timer;
        chMtxUnlock( &g_mutex );
        while ( t > 0 )
        {
            chThdSleepSeconds( 1 );
            chMtxLock( &g_mutex );
            g_timer--;
            t = g_timer;
            chMtxUnlock( &g_mutex );
        }
        setPower( 0 );
        // Wait for next power on.
        g_timer = g_onDelay;
        while ( g_timer-- > 0 )
            chThdSleepSeconds( 1 );
        goto POWER_LOOP;
    }
    return 0;
}

void initPower( void )
{
    setPower( 0 );
    chMtxInit( &g_mutex );

    chThdCreateStatic( waPower, sizeof(waPower), NORMALPRIO, Power, NULL );
}





