
#include "moto_ctrl.h"
#include "ch.h"
#include "hal.h"

#define MOTO_EN_PIN    8
#define MOTO_EN_PORT   GPIOA

#define MOTO_1_PIN   12
#define MOTO_1_PORT  GPIOA
#define MOTO_2_PIN   9
#define MOTO_2_PORT  GPIOA
#define MOTO_3_PIN   10
#define MOTO_3_PORT  GPIOA
#define MOTO_4_PIN   11
#define MOTO_4_PORT  GPIOA

void motoSetEn( uint16_t en )
{
	if ( en )
	    palSetPad( MOTO_EN_PORT, MOTO_EN_PIN );
	else
	    palClearPad( MOTO_EN_PORT, MOTO_EN_PIN );
    motoSet( 0 );
    palSetPadMode( MOTO_EN_PORT, MOTO_EN_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}

void motoSet( uint16_t en )
{
    if (en & 0x01 )
	    palSetPad( MOTO_1_PORT, MOTO_1_PIN );
	else
	    palClearPad( MOTO_1_PORT, MOTO_1_PIN );
    palSetPadMode( MOTO_1_PORT, MOTO_1_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( en & 0x02 )
	    palSetPad( MOTO_2_PORT, MOTO_2_PIN );
	else
	    palClearPad( MOTO_2_PORT, MOTO_2_PIN );
    palSetPadMode( MOTO_2_PORT, MOTO_2_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( en & 0x04 )
	    palSetPad( MOTO_3_PORT, MOTO_3_PIN );
	else
	    palClearPad( MOTO_3_PORT, MOTO_3_PIN );
    palSetPadMode( MOTO_3_PORT, MOTO_3_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( en & 0x08 )
	    palSetPad( MOTO_4_PORT, MOTO_4_PIN );
	else
	    palClearPad( MOTO_4_PORT, MOTO_4_PIN );
    palSetPadMode( MOTO_4_PORT, MOTO_4_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}








