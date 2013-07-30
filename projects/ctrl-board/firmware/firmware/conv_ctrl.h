
#ifndef __CONV_CTRL_H_
#define __CONV_CTRL_H_

#include "ch.h"

void convStart( void );
void convStop( void );
void convSetBuckEn( uint16_t en );
void convSetBuck( uint16_t sp );
void convSetBoost( uint16_t sp );
void convSetSolar( uint16_t minValue );
void convSetBuckGain( uint16_t val );
void convSetBoostGain( uint16_t val );

uint16_t adcCurrent( void );
uint16_t adcTemperature( void );
uint16_t adcBoostFb( void );
uint16_t adcBuckFb( void );
uint16_t adcSolarFb( void );


#endif




