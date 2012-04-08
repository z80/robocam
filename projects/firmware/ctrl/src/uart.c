
#include "uart.h"
#include <avr/io.h>

#define DDR_XCK 0

void uartInit( unsigned short ubrr )
{
    // Set baud rate
    UBRRH = (unsigned char)( ubrr >> 8 );
    UBRRL = (unsigned char)(ubrr & 0xFF );
    // Enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN);
    // Set frame format: 8data, 2stop bit
    UCSRC = (1<<URSEL)|
            (1<<USBS)|(3<<UCSZ0);
    // Set slave mode
    // DDRB &= ~(1<<DDR_XCK);
}

unsigned char uartWrite( unsigned char val )
{
    // Wait for empty transmit buffer
    if ( !( UCSRA & (1<<UDRE)) )
        return 1;
    // Put data into buffer, sends the data
    UDR = val;
    return 0;
}

unsigned char uartRead( unsigned char * res )
{
    // Wait for data to be received
    if ( !(UCSRA & (1<<RXC)) )
        return 1;
    // Get and return received data from buffer
    *res = UDR;
    return 0;
}



