
#ifndef __OSC_CTRL_H_
#define __OSC_CTRL_H_

#include "ch.h"

void initOsc( void );
void oscSetup( uint16_t period, uint8_t sigs );
uint16_t oscMeasuresCnt( uint8_t * sigs );
uint16_t oscValue( uint16_t index );


#endif


