
#ifndef __MOTO_CTRL_H_
#define __MOTO_CTRL_H_

#include "ch.h"
#include "shell.h"

void initMoto( void );

// On or off and off timeout.
void motoConfig( bool_t en, int timeout );
// Resets auto off countdown.
void motoReset(void);
// Drives state.
void motoSet( BaseChannel *chp, uint8_t en );
void motoApply( void );
// USB shell access functions.
void cmd_moto_cfg( BaseChannel *chp, int argc, char * argv [] );
void cmd_moto_rst( BaseChannel *chp, int argc, char * argv [] );
void cmd_moto_set( BaseChannel *chp, int argc, char * argv [] );
void cmd_moto( BaseChannel *chp, int argc, char * argv [] );




#endif



