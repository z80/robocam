
#include "adc_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "hdw_cfg.h"

#include <string.h>
#include <stdlib.h>

static Mutex g_mutex;
static uint8_t g_status = 0;

#define ADC_ENABLED 1
#define ADC_RUNNING 2

static adcsample_t g_src[] = { 32767, 32767 };
static adcsample_t g_res[] = { 32767, 32767 };

static void adcReadyCb( ADCDriver * adcp, adcsample_t * buffer, size_t n )
{
    (void)adcp;
    (void)buffer;
    (void)n;
    chMtxLock( &g_mutex );
    g_res[0] = g_src[0];
    g_res[1] = g_src[1];
    g_status &= (~ADC_RUNNING);
    chMtxUnlock();
};

static const ADCConversionGroup g_grp =
{
    FALSE,
    2,
    adcReadyCb,
    NULL,
    0, 0,
    0,
    ADC_SMPR2_SMP_AN4(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN3( ADC_SAMPLE_239P5 ),
    ADC_SQR1_NUM_CH( 2 ),
    0,
    ADC_SQR3_SQ1_N( ADC_CHANNEL_IN4 ) | ADC_SQR3_SQ2_N( ADC_CHANNEL_IN3 )
};

void initAdc( void )
{
    //chMtxLock( &g_mutex );
    g_status = 0;
    //chMtxUnlock();
	palSetGroupMode( ADC_SOL_PORT, PAL_PORT_BIT(ADC_SOL_PIN), 0, PAL_MODE_INPUT_ANALOG );
	palSetGroupMode( ADC_BAT_PORT, PAL_PORT_BIT(ADC_BAT_PIN), 0, PAL_MODE_INPUT_ANALOG );
    adcStart( &ADCD1, NULL );
}

void finitAdc( void )
{
    chMtxLock( &g_mutex );
    g_status = 0;
    chMtxUnlock();
    adcStop( &ADCD1 );
}

void adcCfg( uint8_t en )
{
    chMtxLock( &g_mutex );
    if ( en )
        g_status |= ADC_ENABLED;
    else
    	g_status &= (~ADC_ENABLED);
    chMtxUnlock();
}

void adc( uint16_t * v1, uint16_t * v2 )
{
    chMtxLock( &g_mutex );
    if ( v1 )
    	*v1 = g_res[0];
    if ( v2 )
    	*v2 = g_res[1];
    chMtxUnlock();
}

void cmd_adc_cfg( BaseChannel *chp, int argc, char * argv [] )
{
	(void)chp;
    if ( argc > 0 )
    {
        static uint8_t en;
        en = ( argv[0][0] != '0' ) ? 1 : 0;
        adcCfg( en );
    }
}

void cmd_adc( BaseChannel *chp, int argc, char * argv [] )
{
	(void)argc;
	(void)(argv);
    static uint16_t v1, v2;
    adc( &v1, &v2 );
    chprintf( chp, "{%i %u}", v1, v2 );
}

void processAdc( void )
{
	static uint8_t en, running;
	//chMtxLock( &g_mutex );
	en = ( g_status & ADC_ENABLED ) ? 1 : 0;
	running = ( g_status & ADC_RUNNING ) ? 1 : 0;
	//chMtxUnlock();
	if ( en )
	{
		if ( !running )
		{
			//chMtxLock( &g_mutex );
			g_status |= ADC_RUNNING;
			//chMtxUnlock();
            adcConvert( &ADCD1, &g_grp, g_src, 1 );
		}
	}
}

