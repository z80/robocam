
#ifndef __ADC_CTRL_H_
#define __ADC_CTRL_H_

#include "ch.h"
#include "shell.h"

void initAdc( void );
void finitAdc( void );
void adcCfg( uint8_t en );
void adc( uint16_t * v1, uint16_t * v2 );
void cmd_adc_cfg( BaseChannel *chp, int argc, char * argv [] );
void cmd_adc( BaseChannel *chp, int argc, char * argv [] );

void processAdc( void );

#endif



