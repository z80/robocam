
#ifndef __POWER_CTRL_H_
#define __POWER_CTRL_H_

#include "ch.h"
#include "shell.h"

void initPower( void );
// To be called in main loop.
void powerHandler( void );

void powerConfig( int aactiveTime, int aidleTime );
void powerOffReset( void );

#endif





