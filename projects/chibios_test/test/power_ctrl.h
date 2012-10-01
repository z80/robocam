
#ifndef __POWER_CTRL_H_
#define __POWER_CTRL_H_

#include "ch.h"
#include "shell.h"

void initPower( void );

void setPowerOnTimeout( int sec );
void setPowerOffTimeout( int sec );
void powerOffReset( void );
void cmd_power( BaseChannel *chp, int argc, char * argv [] );

#endif





