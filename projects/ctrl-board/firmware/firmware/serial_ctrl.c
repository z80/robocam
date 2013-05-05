
#include "serial_ctrl.h"
#include "conv_ctrl.h"

#include "hal.h"
#include "shell.h"
#include "chprintf.h"

#define SERIAL_UART       SD3
#define SERIAL_BAUD       9600

static SerialConfig config =
{
    SERIAL_BAUD,
    0,
    0,
    0
};


static void cmd_mem( BaseChannel * chp, int argc, char * argv[] );
static void cmd_temperature( BaseChannel * chp, int argc, char * argv[] );
static void cmd_current( BaseChannel * chp, int argc, char * argv[] );

#define SHELL_WA_SIZE   THD_WA_SIZE( 2048 )
static const ShellCommand commands[] =
{
    { "mem", cmd_mem },
    { NULL,  NULL }
};

Thread * shelltp = NULL;

static const ShellConfig shell_cfg =
{
    (BaseChannel *)&SERIAL_UART,
    commands
};

void initSerial( void )
{
    sdStart( &SERIAL_UART, &config );
}

void processSerial( void )
{
    if ( !shelltp )
        shelltp = shellCreate( &shell_cfg, SHELL_WA_SIZE, NORMALPRIO );
    else if ( chThdTerminated( shelltp ) )
    {
        chThdRelease( shelltp );  // Recovers memory of the previous shell.
        shelltp = NULL;           // Triggers spawning of a new shell.
    }
}

static void cmd_mem( BaseChannel * chp, int argc, char * argv[] )
{
    size_t n, size;
    n = chHeapStatus( NULL, &size );
    chprintf( chp, "core free memory : %u bytes\r\n", chCoreStatus() );
    chprintf( chp, "heap fragments   : %u\r\n", n );
    chprintf( chp, "heap free total  : %u bytes\r\n", size );
}

static void cmd_temperature( BaseChannel * chp, int argc, char * argv[] )
{
    chprintf( chp, "temperature: %u\r\n", adcTemperature() );
}

static void cmd_current( BaseChannel * chp, int argc, char * argv[] )
{
    chprintf( chp, "temperature: %u\r\n", adcCurrent() );
}











