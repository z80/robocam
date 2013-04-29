
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
void motoSet( uint8_t en );
void motoApply( void );




#endif



