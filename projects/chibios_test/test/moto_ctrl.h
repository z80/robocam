
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
void motoSet( bool_t v1, bool_t v2, bool_t v3, bool_t v4 );
// USB shell access functions.
void cmd_moto_cfg( BaseChannel *chp, int argc, char * argv [] );
void cmd_moto_rst( BaseChannel *chp, int argc, char * argv [] );
void cmd_moto_set( BaseChannel *chp, int argc, char * argv [] );




#endif



