
#ifndef __LIGHT_CTRL_H_
#define __LIGHT_CTRL_H_

#include "ch.h"
#include "shell.h"

void setLight( bool_t en );
void cmd_light( BaseChannel *chp, int argc, char * argv [] );

#endif




