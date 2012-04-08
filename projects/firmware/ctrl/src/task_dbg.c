
#include "task_dbg.h"
#include "io_struct.h"
#include "uart.h"

extern struct TIOStr * pst;

void taskDbg( xCoRoutineHandle xHandle, unsigned portBASE_TYPE uxIndex )
{
    static uint8_t ind = 0;
    static char    res = 'a';
    static char    cmd[ CMD_LEN ];

    crSTART( xHandle );
    // Task loop
    for ( ;; )
    {
        // Read command.
        while ( ( res != '\0' ) && ( res != 0x0d ) && ( ind < CMD_LEN ) )
        {
            if ( uartRead( (unsigned char *)(&res) ) == 0 )
            {
                res = ( res != 0x0d ) ? res : '\0';
                cmd[ ind++ ] = res;
                // Send result to sender to be sure it's been accepted.
                while ( uartWrite( *( (unsigned char *)(&res) ) ) )
                    crDELAY( xHandle, 1 );
            }
            else
                crDELAY( xHandle, 1 );
        }
        ind = 0;
        res = 'a';
        // Parse command
        parseCmd( cmd );
        crDELAY( xHandle, 1 );
    }

    crEND();
}




