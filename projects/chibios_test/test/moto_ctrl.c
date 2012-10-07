
#include "moto_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "hdw_cfg.h"

#include <string.h>
#include <stdlib.h>

static Mutex g_mutex;
int g_offTimeout   = ( 3 );
int g_timeout      = 0;


void motoConfig( bool_t en, int timeout )
{
	chMtxLock( &g_mutex );
	g_offTimeout = timeout;
	chMtxUnlock();
	if ( en )
	    palSetPad( MOTO_EN_PORT, MOTO_EN_PIN );
	else
	    palClearPad( MOTO_EN_PORT, MOTO_EN_PIN );
    motoSet( 0 );
    palSetPadMode( MOTO_EN_PORT, MOTO_EN_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}

void motoReset(void)
{
	chMtxLock( &g_mutex );
	g_timeout = g_offTimeout;
	chMtxUnlock();
}

void motoSet( uint8_t en )
{
	if ( en & 1 )
	    palSetPad( MOTO_1_PORT, MOTO_1_PIN );
	else
	    palClearPad( MOTO_1_PORT, MOTO_1_PIN );
    palSetPadMode( MOTO_1_PORT, MOTO_1_PIN, PAL_MODE_OUTPUT_PUSHPULL );

	if ( en & 2 )
	    palSetPad( MOTO_2_PORT, MOTO_2_PIN );
	else
	    palClearPad( MOTO_2_PORT, MOTO_2_PIN );
    palSetPadMode( MOTO_2_PORT, MOTO_2_PIN, PAL_MODE_OUTPUT_PUSHPULL );

	if ( en & 4 )
	    palSetPad( MOTO_3_PORT, MOTO_3_PIN );
	else
	    palClearPad( MOTO_3_PORT, MOTO_3_PIN );
    palSetPadMode( MOTO_3_PORT, MOTO_3_PIN, PAL_MODE_OUTPUT_PUSHPULL );

	if ( en & 8 )
	    palSetPad( MOTO_4_PORT, MOTO_4_PIN );
	else
	    palClearPad( MOTO_4_PORT, MOTO_4_PIN );
    palSetPadMode( MOTO_4_PORT, MOTO_4_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}

void cmd_moto_cfg( BaseChannel *chp, int argc, char * argv [] )
{
	(void)chp;
	if ( argc > 0 )
	{
		bool_t en = ( argv[0][0] != '0' ) ? 1 : 0;
		int timeout;
		if ( argc > 1 )
			timeout = atoi( argv[1] );
		else
		{
			chMtxLock( &g_mutex );
			timeout = g_offTimeout;
			chMtxUnlock();
		}
		motoConfig( en, timeout );
	}
}

void cmd_moto_rst( BaseChannel *chp, int argc, char * argv [] )
{
	(void)chp;
	(void)argc;
	(void)argv;
	motoReset();
}

void cmd_moto_set( BaseChannel *chp, int argc, char * argv [] )
{
	(void)chp;
	if ( argc > 0 )
	{
		if ( strlen(argv[0]) > 3 )
		{
			static uint8_t v;
			v = ( ( argv[0][0] != '0' ) ? 1 : 0 ) +
			    ( ( argv[0][1] != '0' ) ? 2 : 0 ) +
			    ( ( argv[0][2] != '0' ) ? 4 : 0 ) +
			    ( ( argv[0][3] != '0' ) ? 8 : 0 );
			motoSet( v );
		}
	}
}

static WORKING_AREA( waMoto, 256 );
static msg_t Moto( void *arg )
{
    (void)arg;
    motoConfig( 0, 3 );
    chRegSetThreadName( "moto" );
    while (TRUE)
    {
        chMtxLock( &g_mutex );
        g_timeout = g_offTimeout;
        static int t;
        t = g_timeout;
        chMtxUnlock();
        while ( t > 0 )
        {
            chThdSleepSeconds( 1 );
            chMtxLock( &g_mutex );
            g_timeout--;
            t = g_timeout;
            chMtxUnlock();
        }
        chMtxLock( &g_mutex );
        t = g_offTimeout;
        chMtxUnlock();
        motoConfig( 0, t );
    }
    return 0;
}

void initMoto( void )
{
    chMtxInit( &g_mutex );
    motoConfig( 0, 3 );

    chThdCreateStatic( waMoto, sizeof(waMoto), NORMALPRIO, Moto, NULL );
}







