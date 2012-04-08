
#include "task_watchdog.h"
#include "io_struct.h"

portTickType g_wdTimeout = 60;
portTickType g_wdLeft    = 60;

extern struct TIOStr * pst;

void setWatchdog( portTickType timeout )
{
    g_wdTimeout = timeout;
}

void resetWatchdog()
{
    g_wdLeft = g_wdTimeout;
}

void taskWatchdog( xCoRoutineHandle xHandle, unsigned portBASE_TYPE uxIndex )
{
    crSTART( xHandle );
    // Task loop
    for ( ;; )
    {
        if ( g_wdLeft > 0 )
            // Count down
            g_wdLeft--;
        else
        {
            // Turn all motors off
            pst->pwm1 = 0;
            pst->pwm2 = 0;
            MOTORS_PORT &= ~( MOTORS_EN | SERVO_EN | MOTORS_MASK | SERVO_MASK );
            // To begin new count down.
            resetWatchdog();
        }
        crDELAY( xHandle, 100 );
    }

    crEND();
}




