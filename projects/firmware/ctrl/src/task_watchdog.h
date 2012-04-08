
#ifndef __TASK_WATCHDOG_H_
#define __TASK_WATCHDOG_H_

#include "FreeRTOS.h"
#include "croutine.h"

void setWatchdog( portTickType timeout );
void resetWatchdog();
void taskWatchdog( xCoRoutineHandle xHandle, unsigned portBASE_TYPE uxIndex );

#endif


