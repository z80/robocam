
#include "ch.h"
#include "hal.h"
#include "light_ctrl.h"
#include "power_ctrl.h"
#include "moto_ctrl.h"
#include "adc_ctrl.h"
#include "conv_ctrl.h"
#include "serial_ctrl.h"

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
        chThdSleepMilliseconds( 300 );
        palSetPad( GPIOB, 13 );
	palClearPad( GPIOB, 14 );

        chThdSleepMilliseconds( 300 );
        palClearPad( GPIOB, 13 );
	palSetPad( GPIOB, 14 );
 
    }
    return 0;
}

void initLeds( void )
{
    //chMtxInit( &g_mutex );
    //setPower( 0 );

    chThdCreateStatic( waLeds, sizeof(waLeds), NORMALPRIO, Leds, NULL );
}


//*
//* Application entry point.
//*
int main(void)
{
  halInit();
  chSysInit();

  initLeds();
  convStart();
  initSerial();

  while ( TRUE )
  {
      processSerial();
      chThdSleepSeconds( 1 );
  }
  return 0;
}






