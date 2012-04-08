
#ifndef __UART_H_
#define __UART_H_

void uartInit( unsigned short ubrr );
unsigned char uartWrite( unsigned char val );
unsigned char uartRead( unsigned char * res );

#endif


