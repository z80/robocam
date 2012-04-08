
#ifndef __TASK_PWM_H_
#define __TASK_PWM_H_

#include "FreeRTOS.h"
#include "croutine.h"
#include "task.h"

void taskPwm( xCoRoutineHandle xHandle, unsigned portBASE_TYPE uxIndex );

#endif


