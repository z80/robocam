/* Name: main.c
 * Project: PowerSwitch based on AVR USB driver
 * Author: Christian Starkjohann
 * Creation Date: 2005-01-16
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt) or proprietary (CommercialLicense.txt)
 * This Revision: $Id: main.c 523 2008-02-15 09:46:40Z cs $
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

#include "usbdrv.h"
#include <util/delay.h>

#include "io_ctrl.h"

#define OUT_BUFFER_SZ 8

USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
    usbRequest_t    * rq = (void *)data;
    static uchar    replyBuf[ OUT_BUFFER_SZ ];
    usbMsgPtr = replyBuf;

    inQueuePush( rq->bRequest );

    //replyBuf[0] = rq->bRequest;
    if ( outQueuePop( &(replyBuf[0]) ) == 0 )
        return 1;
    return 0;
}

int main(void)
{
    uchar   i;

    cli();
    queueInit();

    wdt_enable(WDTO_1S);
    //DDRD = ~(1 << 2);   // all outputs except PD2 = INT0
    DDRB  = 0x00;
    PORTB = 0xFF;
    DDRC  = 0x00 | (1<<1);
    PORTC = 0xFF;
    DDRD  = ~USBMASK;    // set all pins as outputs except USB
    //PORTD = 0xFF ^ ( (1<<2) | (1<<3) );

/* We fake an USB disconnect by pulling D+ and D- to 0 during reset. This is
 * necessary if we had a watchdog reset or brownout reset to notify the host
 * that it should re-enumerate the device. Otherwise the host's and device's
 * concept of the device-ID would be out of sync.
 */
    usbDeviceDisconnect();  // enforce re-enumeration, do this while interrupts are disabled!
    i = 0;
    while(--i){         // fake USB disconnect for > 500 ms
        wdt_reset();
        _delay_ms(2);
    }
    usbDeviceConnect();
    usbInit();
    sei();
    for(;;)
    {
        // main event loop
        wdt_reset();
        usbPoll();
        // Send data if any.
        queueProcess();
        _delay_ms( 1 );

        //uint8_t val = PORTC;
        //PORTC = val ^ (1<<1);
    }
    return 0;
}

