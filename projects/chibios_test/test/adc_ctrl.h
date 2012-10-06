
#ifndef __ADC_CTRL_H_
#define __ADC_CTRL_H_

void initAdc( void );
void finitAdc( void );
void adcCfg( uint8_t en );
void adc( uint16_t * v1, uint16_t * v2 );


#endif



