

#include "conv_ctrl.h"
#include "hal.h"

#define PWM_CLOCK_FREQ     8000000  // 8MHz clock
#define PWM_PERIOD         60       // 150kHz
#define BOOST_MAX_FILL     9000

#define CONV_PORT          GPIOA
#define CONV_BOOST_PIN     1
#define CONV_BUCK_PIN      2

#define CONV_PWM           PWMD2
#define PWM_BOOST_CHAN     1
#define PWM_BUCK_CHAN      2

#define CONV_ADC_PORT      GPIOA
#define CONV_SOLAR_FB_PIN  	3
#define CONV_BOOST_FB_PIN  	4
#define CONV_BUCK_FB_PIN   	5
#define CONV_CURRENT_FB_PIN 6
#define CONV_TEMP_FB_PIN 	7

#define ADC_NUM_CHANNELS   3
#define ADC_BUF_DEPTH      2
#define SOLAR_IND          0
#define BOOST_IND          1
#define BUCK_IND           2

static uint16_t buckPwm   = 0;
static uint16_t boostPwm  = 0;
static uint16_t buckGain  = 1000; // Gain is 10%
static uint16_t boostGain = 1000; // Gain is 10%
static uint16_t buckSp    = ( ( 4095 * 5000 ) / ( 3 * 3300 ) );
static uint16_t boostSp   = ( ( 4095 * 7000 ) / ( 3 * 3300 ) );
// Was 4.9V but with diode decreased on voltage drop on diode which is 0.65V.
// So now solar setpoint is 4.2V.
static uint16_t solarSp   = ( ( 4095 * 4200 ) / ( 3 * 3300 ) );
static uint16_t buckSpSave = 0;

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
        pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
    }
    else if ( buffer[ BUCK_IND ] > buckSp )
    {
    	buckPwm = ( buckPwm >= buckGain ) ? buckPwm : buckGain;
    	buckPwm -= buckGain;
    	pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
    }
    // Boost
    if ( buffer[ SOLAR_IND ] >= solarSp )
    {
        if ( buffer[ BOOST_IND ] < boostSp )
        {
        	boostPwm += boostGain;
        	boostPwm = ( boostPwm <= BOOST_MAX_FILL ) ? boostPwm : BOOST_MAX_FILL;
        	pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
        }
        else if ( buffer[ BOOST_IND ] > boostSp )
        {
        	boostPwm = ( boostPwm >= boostGain ) ? boostPwm : boostGain;
        	boostPwm -= boostGain;
        	pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
        }
    }
    else
    	pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0 ) );
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
#define ADC_SAMPLING  ADC_SAMPLE_13P5

static const ADCConversionGroup adcGroup =
{
    TRUE,
    ADC_NUM_CHANNELS,
    contAdcReadyCb,
    NULL,
    0, 0,           /* CR1, CR2 */
    0,
    ADC_SMPR2_SMP_AN3( ADC_SAMPLING ) |
    ADC_SMPR2_SMP_AN4( ADC_SAMPLING ) |
    ADC_SMPR2_SMP_AN5( ADC_SAMPLING ),
    ADC_SQR1_NUM_CH( ADC_NUM_CHANNELS ),
    0,
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN3) |
    ADC_SQR3_SQ2_N(ADC_CHANNEL_IN4) |
    ADC_SQR3_SQ3_N(ADC_CHANNEL_IN5)
};

static PWMConfig pwmCfg =
{
    PWM_CLOCK_FREQ, // 1000kHz PWM clock frequency.
    PWM_PERIOD,     // Initial PWM period 10us.
    NULL,
    {
        { PWM_OUTPUT_DISABLED, NULL },
        //{ PWM_OUTPUT_DISABLED, NULL },      // Disable boost part of PWM.
        { PWM_OUTPUT_ACTIVE_HIGH, NULL },
        { PWM_OUTPUT_ACTIVE_HIGH, NULL },
        { PWM_OUTPUT_DISABLED, NULL }
    },
    0,
#if STM32_PWM_USE_ADVANCED
    0
#endif
};




void convStart( void )
{
    // Start PWM peripherial.
    pwmStart( &CONV_PWM, &pwmCfg );
    // Init PWM pins.
    palSetPadMode( CONV_PORT, CONV_BUCK_PIN,  PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    palSetPadMode( CONV_PORT, CONV_BOOST_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    // Set zero active period.
    pwmEnableChannel( &CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0000 ) );
    pwmEnableChannel( &CONV_PWM, PWM_BUCK_CHAN,  PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0000 ) );

    // Init ADC.
    palSetGroupMode( CONV_ADC_PORT, PAL_PORT_BIT( CONV_BUCK_FB_PIN ) |
    	                            PAL_PORT_BIT( CONV_BOOST_FB_PIN ) |
    	                            PAL_PORT_BIT( CONV_SOLAR_FB_PIN ) |
    	                            PAL_PORT_BIT( CONV_CURRENT_FB_PIN ) |
    	                            PAL_PORT_BIT( CONV_TEMP_FB_PIN ),
                                    0, PAL_MODE_INPUT_ANALOG );
    adcStart( &ADCD1, NULL );

    adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
}

void convStop( void )
{
    pwmStop( &CONV_PWM );
    adcStopConversion( &ADCD1 );
    adcStop( &ADCD1 );
}

void convSetBuckEn( uint16_t en )
{
    chSysLock();
        if ( en )
        {
            buckSp = buckSpSave;
        }
        else
        {
            // It is significant that only meaningful setpoint should be saved.
            // Otherwise turning off power twice would cause 0 setpoint
            // in active state.
            if ( buckSp > 0 )
                buckSpSave = buckSp;
            buckSp = 0;
        }
    chSysUnlock();
}

void convSetBuck( uint16_t sp )
{
    chSysLock();
        buckSp = sp;
    chSysUnlock();
}

void convSetBoost( uint16_t sp )
{
    chSysLock();
        boostSp = sp;
    chSysUnlock();
}

void convSetSolar( uint16_t minValue )
{
    chSysLock();
        solarSp = minValue;
    chSysUnlock();
}

void convSetBuckGain( uint16_t val )
{
    chSysLock();
        buckGain = val;
    chSysUnlock();
}

void convSetBoostGain( uint16_t val )
{
    chSysLock();
        boostGain = val;
    chSysUnlock();
}





















static const ADCConversionGroup grpCurrent =
    {
        FALSE,
        1,
        NULL,
        NULL,
        0, 0,
        0,
        ADC_SMPR2_SMP_AN6( ADC_SAMPLING ),
        ADC_SQR1_NUM_CH( 1 ),
        0,
        ADC_SQR3_SQ1_N( ADC_CHANNEL_IN6 )
    };

static const ADCConversionGroup grpTemperature =
    {
        FALSE,
        1,
        NULL,
        NULL,
        0, 0,
        0,
        ADC_SMPR2_SMP_AN7( ADC_SAMPLING ),
        ADC_SQR1_NUM_CH( 1 ),
        0,
        ADC_SQR3_SQ1_N( ADC_CHANNEL_IN7 )
    };

static adcsample_t valCurrect,
                   valTemperature;


uint16_t adcCurrent( void )
{
    uint8_t en =  ( ADCD1.state != ADC_STOP ) ? 1 : 0;
    if ( !en )
        adcStart( &ADCD1, NULL );
    else
        adcStopConversion( &ADCD1 );
    adcConvert( &ADCD1, &grpCurrent, &valCurrect, 1 );
    if ( en )
        adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
    else
        adcStop( &ADCD1 );
    return (uint16_t)valCurrect;
}

uint16_t adcTemperature( void )
{
    uint8_t en =  ( ADCD1.state != ADC_STOP ) ? 1 : 0;
    if ( !en )
        adcStart( &ADCD1, NULL );
    else
        adcStopConversion( &ADCD1 );
    adcConvert( &ADCD1, &grpTemperature, &valTemperature, 1 );
    if ( en )
        adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
    else
        adcStop( &ADCD1 );
    return (uint16_t)valTemperature;
}

uint16_t adcBoostFb( void )
{
    chSysLock();
        uint16_t res = adcSamples[BOOST_IND];
    chSysUnlock();
    return res;
}

uint16_t adcBuckFb( void )
{
    chSysLock();
        uint16_t res = adcSamples[BUCK_IND];
    chSysUnlock();
    return res;
}

uint16_t adcSolarFb( void )
{
    chSysLock();
        uint16_t res = adcSamples[SOLAR_IND];
    chSysUnlock();
    return res;
}








