
#include "io_ctrl.h"
#include "uart.h"
#include <avr/io.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define QUEUE_SZ    64

struct TQueue
{
    uint8_t wrInd;
    uint8_t rdInd;
    unsigned char data[ QUEUE_SZ ];
};

struct TQueue inQueue;
struct TQueue outQueue;

char queuePush( struct TQueue * q, unsigned char val )
{
    q->data[ q->wrInd++ ] = val;
    q->wrInd %= QUEUE_SZ;
    return 0;
}

char queuePop( struct TQueue * q, unsigned char * val )
{
    // If pointers match there is no new data.
    // Return error result.
    if ( q->rdInd == q->wrInd )
        return 1;
    *val = q->data[ q->rdInd++ ];
    q->rdInd %= QUEUE_SZ;
    return 0;
}

void queueInit()
{
    inQueue.rdInd = 0;
    inQueue.wrInd = 0;
    outQueue.rdInd = 0;
    outQueue.wrInd = 0;

    uartInit( MYUBRR );
}

char          sendStarted = 0;
unsigned char sendVal = 0;
void queueProcess()
{
    if ( sendStarted == 0 )
    {
        if ( inQueuePop( &sendVal ) == 0 )
            sendStarted = 1;
    }
    else
    {
        if ( uartWrite( sendVal ) == 0 )
            sendStarted = 0;
    }
    // UART reading.
    unsigned char val;
    if ( uartRead( &val ) == 0 )
        outQueuePush( val );
}

char inQueuePush( unsigned char val )
{
    return queuePush( &inQueue, val );
}

char inQueuePop( unsigned char * val )
{
    return queuePop( &inQueue, val );
    //*val = 0xAF;
    //return 0;
}

char outQueuePush( unsigned char val )
{
    return queuePush( &outQueue, val );
}

char outQueuePop( unsigned char * val )
{
    return queuePop( &outQueue, val );
}



