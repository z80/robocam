
#include "moto_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "hdw_cfg.h"

#include <string.h>
#include <stdlib.h>

static Mutex g_mutex;
static int g_offTimeout = ( 3 );
static int g_timeout    = 0;
static uint8_t g_moto   = 0;


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
	motoReset();

    //static uint32_t arg;
    //arg = en;
    //en = 1+2+4+8;
    //arg |= 1;
	chMtxLock( &g_mutex );
    g_moto = en;
    chMtxUnlock();
    motoApply();
}

void motoApply( void )
{
	chMtxLock( &g_mutex );
    if (g_moto & 0x01 )
	    palSetPad( MOTO_1_PORT, MOTO_1_PIN );
	else
	    palClearPad( MOTO_1_PORT, MOTO_1_PIN );
    palSetPadMode( MOTO_1_PORT, MOTO_1_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( g_moto & 0x02 )
	    palSetPad( MOTO_2_PORT, MOTO_2_PIN );
	else
	    palClearPad( MOTO_2_PORT, MOTO_2_PIN );
    palSetPadMode( MOTO_2_PORT, MOTO_2_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( g_moto & 0x04 )
	    palSetPad( MOTO_3_PORT, MOTO_3_PIN );
	else
	    palClearPad( MOTO_3_PORT, MOTO_3_PIN );
    palSetPadMode( MOTO_3_PORT, MOTO_3_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( g_moto & 0x08 )
	    palSetPad( MOTO_4_PORT, MOTO_4_PIN );
	else
	    palClearPad( MOTO_4_PORT, MOTO_4_PIN );
    palSetPadMode( MOTO_4_PORT, MOTO_4_PIN, PAL_MODE_OUTPUT_PUSHPULL );
    chMtxUnlock();
}








