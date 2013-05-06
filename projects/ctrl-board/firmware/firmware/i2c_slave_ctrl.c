
#include "i2c_slave_ctrl.h"
#include "hal.h"
#include "i2c_slave_conf.h"

static uint8_t outBuffer[ I2C_OUT_BUFFER_SZ ];
static uint8_t inBuffer[ I2C_IN_BUFFER_SZ ];
//static Mutex   mutex;

static InputQueue inputQueue;
#define QUEUE_SZ (I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE)
static uint8_t queue[ I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE ];

static const I2CConfig i2cfg1 =
{
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

static void i2cRxCb( I2CDriver * i2cp );
static void i2cTxCb( I2CDriver * i2cp );

static WORKING_AREA( waExec, 1024 );
static msg_t execThread( void *arg );



void initI2cSlave( void )
{
    palSetPadMode( GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
    palSetPadMode( GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );

    // Initialize mailbox.
    chIQInit( &inputQueue, queue, I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE, NULL );
    // Creating thread.
    chThdCreateStatic( waExec, sizeof(waExec), NORMALPRIO, execThread, NULL );
}

void startI2cSlave( void )
{
    static msg_t status;
    static systime_t tmo;
    tmo = MS2ST( I2C_TIMEOUT );

    i2cStart( &I2CD1, &i2cfg1 );
    status = i2cSlaveIoTimeout( &I2CD1, I2C_ADDRESS,
                                inBuffer,  I2C_IN_BUFFER_SZ,
                                outBuffer, I2C_OUT_BUFFER_SZ,
                                i2cRxCb,
                                i2cTxCb,
                                tmo );
}

void stopI2cSlave( void )
{
    i2cStop( &I2CD1 );
}

static void i2cRxCb( I2CDriver * i2cp )
{
    (void)i2cp;
    // Command processing.
    chSysLockFromIsr();
    static uint32_t i;
    static msg_t res;
    for ( i=0; i<I2C_IN_BUFFER_SZ; i++ )
    {
        res = chIQPutI( &inputQueue, inBuffer[i] );
        if ( res != Q_OK )
            return;
    }
    chSysUnlockFromIsr();
}

static void i2cTxCb( I2CDriver * i2cp )
{
    (void)i2cp;
    // Refresh buffer if necessary.
    //palTogglePad( GPIOB, 11 );
}

static msg_t execThread( void *arg )
{
    (void)arg;
    chRegSetThreadName( "e" );
    while ( 1 )
    {
        static size_t sz;
        static uint8_t buffer[ I2C_IN_BUFFER_SZ ];
        sz = chIQReadTimeout( &inputQueue, buffer, I2C_IN_BUFFER_SZ, TIME_INFINITE );

        //static int32_t value32;
        // Parse inBuffer
        switch ( buffer[0] )
        {
        /*case I2C_CMD_DAC1:
            dacSet( 0, buffer[1] );
            break;
        case I2C_CMD_DAC2:
            dacSet( 1, buffer[1] );
            break;
        case I2C_CMD_ENC1:
            value32 = *(int32_t *)(&(buffer[1]));
            encrelSet( 0, value32 );
            break;
        case I2C_CMD_ENC2:
            value32 = *(int32_t *)(&(buffer[1]));
            encrelSet( 1, value32 );
            break;
        case I2C_CMD_BMSD:
            bmsdRawCmd( &buffer[1] );
            break;
        case I2C_CMD_LEDS:
            setLeds( (uint32_t)buffer[1] );
            break;*/
        }
    }
    return 0;
}



