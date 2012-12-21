
#ifndef __CONV_CTRL_H_
#define __CONV_CTRL_H_

#include "ch.h"

void convStart( void );
void convStop( void );
void convSetBuck( uint16_t sp );
void convSetBoost( uint16_t sp );
void convSetInput( uint16_t minValue );
void convSetBuckGain( uint16_t val );
void convSetBoostGain( uint16_t val );

void cmd_conv( BaseChannel *chp, int argc, char * argv [] );


#endif




