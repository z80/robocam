
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

#include "io_struct.h"
#include "task_dbg.h"
#include "task_pwm.h"
#include "task_watchdog.h"

//portBASE_TYPE g_res;

struct TIOStr st;
struct TIOStr * pst = &st;

int __attribute__((noreturn)) main( void )
{
    ioStructInit( pst );
    // Create the tasks defined within this file.
    xCoRoutineCreate( taskDbg,      0, 0 );
    xCoRoutineCreate( taskPwm,      0, 0 );
    xCoRoutineCreate( taskWatchdog, 0, 0 );
    //g_res = ( g_res == pdPASS ) ? 0 : 1;

    vTaskStartScheduler();
}



void vApplicationIdleHook( void )
{
    for( ;; )
    {
        vCoRoutineSchedule();
    }
}




