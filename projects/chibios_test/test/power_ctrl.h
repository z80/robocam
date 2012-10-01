
#ifndef __POWER_CTRL_H_
#define __POWER_CTRL_H_

#include "ch.h"
#include "shell.h"

void initPower( void );

void powerConfig( int offFirst, int offRegular, int on );
void powerOffReset( void );
void cmd_pwr_cfg( BaseChannel *chp, int argc, char * argv [] );
void cmd_pwr_rst( BaseChannel *chp, int argc, char * argv [] );

#endif





