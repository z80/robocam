
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

static adcsample_t g_src[ 2 ] = { 32767, 32767 };
static adcsample_t g_res[ 2 ] = { 32767, 32767 };


#define ADC_CONT_PORT GPIOA
#define ADC_CONT_PIN  4

static void contAdcReadyCb( ADCDriver * adcp, adcsample_t * buffer, size_t n )
{
    (void)adcp;
    (void)buffer;
    (void)n;
    //chMtxLock( &g_mutex );
    //g_res[0] = g_src[0];
    //g_res[1] = g_src[1];
    //g_status &= (~ADC_RUNNING);
    //chMtxUnlock();
    static uint8_t b = 0;
    palSetPadMode( ADC_CONT_PORT, ADC_CONT_PIN, PAL_MODE_OUTPUT_PUSHPULL );
    if ( b )
    {
    	palSetPad( ADC_CONT_PORT, ADC_CONT_PIN );
    	b = 0;
    }
    else
    {
    	palClearPad( ADC_CONT_PORT, ADC_CONT_PIN );
    	b = 1;
    }
};

static adcsample_t g_contRes[ 2 ] = { 32767, 32767 };

// ADC_SAMPLE_1P5
// ADC_SAMPLE_7P5
// ADC_SAMPLE_13P5
// ADC_SAMPLE_28P5
// ADC_SAMPLE_41P5
// ADC_SAMPLE_55P5
// ADC_SAMPLE_71P5
// ADC_SAMPLE_239P5

static const ADCConversionGroup g_contGrp =
{
    TRUE,
    1,
    contAdcReadyCb,
    NULL,
    0, 0,
    0,
    ADC_SMPR2_SMP_AN2(ADC_SAMPLE_1P5) | ADC_SMPR2_SMP_AN3( ADC_SAMPLE_1P5 ),
    ADC_SQR1_NUM_CH( 2 ),
    0,
    ADC_SQR3_SQ1_N( ADC_CHANNEL_IN2 ) | ADC_SQR3_SQ2_N( ADC_CHANNEL_IN3 )
};






static const ADCConversionGroup g_grp[] =
{
    {
        FALSE,
        1,
        NULL,
        NULL,
        0, 0,
        0,
        ADC_SMPR2_SMP_AN2(ADC_SAMPLE_239P5),
        ADC_SQR1_NUM_CH( 1 ),
        0,
        ADC_SQR3_SQ1_N( ADC_CHANNEL_IN2 )
    },
    {
        FALSE,
        1,
        NULL,
        NULL,
        0, 0,
        0,
        ADC_SMPR2_SMP_AN3( ADC_SAMPLE_239P5 ),
        ADC_SQR1_NUM_CH( 1 ),
        0,
        ADC_SQR3_SQ1_N( ADC_CHANNEL_IN3 )
    }
};

/*static WORKING_AREA( waAdc, (1024) );
static msg_t Adc( void *arg )
{
    (void)arg;
    chRegSetThreadName( "adc" );

    while ( 1 )
    {
         processAdc();
         chThdSleepSeconds( 1 );
    }
    return 0;
}*/

void initAdc( void )
{
	chMtxInit( &g_mutex );
    g_status = 0;
    adcStart( &ADCD1, NULL );

    //chThdCreateStatic( waAdc, sizeof(waAdc), NORMALPRIO, Adc, NULL );
    adcStartConversion( &ADCD1, &g_contGrp, g_contRes, 1 );
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
    {
    	palSetGroupMode( ADC_SOL_PORT, PAL_PORT_BIT(ADC_SOL_PIN), 0, PAL_MODE_INPUT_ANALOG );
    	palSetGroupMode( ADC_BAT_PORT, PAL_PORT_BIT(ADC_BAT_PIN), 0, PAL_MODE_INPUT_ANALOG );
        g_status |= ADC_ENABLED;
    }
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
        chprintf( chp, "ok:adccfg" );
    }
}

void cmd_adc( BaseChannel *chp, int argc, char * argv [] )
{
	(void)argc;
	(void)(argv);
    static uint16_t v1, v2;
    adc( &v1, &v2 );
    chprintf( chp, "{%u %u}", v1, v2 );
}

void processAdc( void )
{
	static uint8_t en;
	chMtxLock( &g_mutex );
	en = ( g_status & ADC_ENABLED ) ? 1 : 0;
	chMtxUnlock();
	if ( en )
	{
		chMtxLock( &g_mutex );
		g_status |= ADC_RUNNING;
		chMtxUnlock();
        adcConvert( &ADCD1, &g_grp[0], &(g_src[0]), 1 );
        chThdSleepMilliseconds( 100 );
        adcConvert( &ADCD1, &g_grp[0], &(g_src[0]), 1 );
        chThdSleepMilliseconds( 100 );
        adcConvert( &ADCD1, &g_grp[1], &(g_src[1]), 1 );
        chThdSleepMilliseconds( 100 );
        adcConvert( &ADCD1, &g_grp[1], &(g_src[1]), 1 );
        chMtxLock( &g_mutex );
        g_res[0] = g_src[0];
        g_res[1] = g_src[1];
        g_status &= (~ADC_RUNNING);
        chMtxUnlock();
	}
}

