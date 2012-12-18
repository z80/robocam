

#include "conv_ctrl.h"
#include "hal.h"

#define CONV_PORT          GPIOA
#define CONV_BOOST_PIN     0
#define CONV_BUCK_PIN      1

#define CONV_PWM           PWMD2
#define PWM_BUCK_CHAN      1
#define PWM_BOOST_CHAN     0

#define CONV_ADC_PORT      GPIOA
#define CONV_INPUT_FB_PIN  2
#define CONV_BOOST_FB_PIN  3
#define CONV_BUCK_FB_PIN   4

#define ADC_NUM_CHANNELS   3
#define ADC_BUF_DEPTH      2
#define INPUT_IND          0
#define BOOST_IND          1
#define BUCK_IND           2

static uint16_t buckPwm   = 0;
static uint16_t boostPwm  = 0;
static uint16_t buckGain  = 128;
static uint16_t boostGain = 128;
static uint16_t buckSp    = 1024;
static uint16_t boostSp   = 1024;
static uint16_t inputSp   = 1024;

static void contAdcReadyCb( ADCDriver * adcp, adcsample_t * buffer, size_t n )
{
    (void)adcp;
    //(void)buffer;
    (void)n;
    // Buck
    if ( buffer[ BUCK_IND ] < buckSp )
    {
    	buckPwm += buckGain;
    	buckPwm = ( buckPwm <= 10000 ) ? buckPwm : 10000;
        pwmEnableChannel(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
    }
    else if ( buffer[ BUCK_IND ] > buckSp )
    {
    	buckPwm = ( buckPwm >= buckGain ) ? buckPwm : buckGain;
    	buckPwm -= buckGain;
    	pwmEnableChannel(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
    }
    // Boost
    if ( buffer[ INPUT_IND ] >= inputSp )
    {
        if ( buffer[ BOOST_IND ] < boostSp )
        {
        	boostPwm += boostGain;
        	boostPwm = ( boostPwm <= 10000 ) ? boostPwm : 10000;
        	pwmEnableChannel(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
        }
        else if ( buffer[ BOOST_IND ] > boostSp )
        {
        	boostPwm = ( boostPwm >= boostGain ) ? boostPwm : boostGain;
        	boostPwm -= boostGain;
        	pwmEnableChannel(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
        }
    }
    else
    	pwmEnableChannel(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0 ) );
};

static adcsample_t adcSamples[ ADC_NUM_CHANNELS * ADC_BUF_DEPTH ];

// ADC_SAMPLE_1P5
// ADC_SAMPLE_7P5
// ADC_SAMPLE_13P5
// ADC_SAMPLE_28P5
// ADC_SAMPLE_41P5
// ADC_SAMPLE_55P5
// ADC_SAMPLE_71P5
// ADC_SAMPLE_239P5

static const ADCConversionGroup adcGroup =
{
    TRUE,
    ADC_NUM_CHANNELS,
    contAdcReadyCb,
    NULL,
    0, 0,           /* CR1, CR2 */
    0,
    ADC_SMPR2_SMP_AN2(ADC_SAMPLE_1P5) | ADC_SMPR2_SMP_AN3( ADC_SAMPLE_1P5 ) |
    ADC_SMPR2_SMP_AN4( ADC_SAMPLE_1P5 ),
    ADC_SQR1_NUM_CH( ADC_NUM_CHANNELS ),
    0,
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN2) |
    ADC_SQR3_SQ2_N(ADC_CHANNEL_IN3) | 
    ADC_SQR3_SQ3_N(ADC_CHANNEL_IN4)
};

static PWMConfig pwmCfg =
{
    1000000, // 1000kHz PWM clock frequency.
    10,      // Initial PWM period 10us.
    NULL,
    {
        { PWM_OUTPUT_ACTIVE_HIGH, NULL },
        { PWM_OUTPUT_ACTIVE_HIGH, NULL },
        { PWM_OUTPUT_ACTIVE_HIGH, NULL },
        { PWM_OUTPUT_DISABLED, NULL }
    },
    0,
#if STM32_PWM_USE_ADVANCED
    0
#endif
};



void convInit( void )
{
	// Init PWM.
    palSetPadMode( CONV_PORT, CONV_BUCK_PIN,  PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    palSetPadMode( CONV_PORT, CONV_BOOST_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    // Init ADC.
    palSetGroupMode(CONV_ADC_PORT, PAL_PORT_BIT( CONV_BUCK_FB_PIN ) |
    	                           PAL_PORT_BIT( CONV_BOOST_FB_PIN ) |
    		                       PAL_PORT_BIT( CONV_INPUT_FB_PIN ),
                                   0, PAL_MODE_INPUT_ANALOG);
    adcStart(&ADCD1, NULL);
}

void convStart( void )
{
    pwmStart( &PWMD2, &pwmCfg );
    palSetPadMode( GPIOA, 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    palSetPadMode( GPIOA, 1, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    palSetPadMode( GPIOA, 2, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    pwmEnableChannel(&PWMD2, 0, PWM_PERCENTAGE_TO_WIDTH( &PWMD2, 5000 ) );
    pwmEnableChannel(&PWMD2, 1, PWM_PERCENTAGE_TO_WIDTH( &PWMD2, 3030 ) );
    pwmEnableChannel(&PWMD2, 2, PWM_PERCENTAGE_TO_WIDTH( &PWMD2, 3030 ) );

    //pwmStart( &CONV_PWM, &pwmCfg );
    //pwmEnableChannel(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 5000 ) );
    //pwmEnableChannel(&CONV_PWM, PWM_BUCK_CHAN,  PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 3030 ) );

    // To see that PWM really works.
    // ADC routine may change PWM period significantly. So I turn it of at
    // the moment for debug purpose.
    //adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
}

void convStop( void )
{
	adcStopConversion( &ADCD1 );
    pwmStop( &CONV_PWM );
}

void convSetBuck( uint16_t sp )
{
    buckSp = sp;
}

void convSetBoost( uint16_t sp )
{
    boostSp = sp;
}

void convSetInput( uint16_t minValue )
{
    inputSp = minValue;
}

void convSetBuckGain( uint16_t val )
{
    buckGain = val;
}

void convSetBoostGain( uint16_t val )
{
    boostGain = val;
}







