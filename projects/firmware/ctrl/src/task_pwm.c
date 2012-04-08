
#include "task_pwm.h"
#include "io_struct.h"
#include <avr/io.h>

extern struct TIOStr * pst;

void taskPwm( xCoRoutineHandle xHandle, unsigned portBASE_TYPE uxIndex )
{
    static uint8_t low;
    static uint8_t high;
    static uint8_t i;
    crSTART( xHandle );
    for ( ;; )
    {
        // Первый PWM.
        low = (uint8_t)(pst->pwm1 & 0xff);
        high = (uint8_t)(pst->pwm1 >> 8);

        if ( low || high )
        {
            taskDISABLE_INTERRUPTS();
            TCCR0 = 0;
            TCNT0 = 0;
            MOTORS_PORT |= SERVO1;
            TCCR0 = ( 1 << CS01) | ( 1 << CS00 ); // Tclk / 64  (1=4us);
            for ( i=0; i<high; i++ )
            {
                while ( TCNT0 < 0xff )
                    asm volatile ( "nop;" );
                while ( TCNT0 == 0xff )
                    asm volatile ( "nop;" );
            }
            while ( TCNT0 < low )
                asm volatile ( "nop;" );
            MOTORS_PORT &= (~SERVO1);
            TCCR0 = 0;
            taskENABLE_INTERRUPTS();
        }
        // С делением на 64 получается по 4 микросекунды на единицу таймера.
        crDELAY( xHandle, pst->pwmDelay );

        // Второй PWM.
        // Первый PWM.
        low = (uint8_t)(pst->pwm2 & 0xff);
        high = (uint8_t)(pst->pwm2 >> 8);
        if ( low || high )
        {
            taskDISABLE_INTERRUPTS();
            TCCR0 = 0;
            TCNT0 = 0;
            MOTORS_PORT |= SERVO2;
            TCCR0 = ( 1 << CS01) | ( 1 << CS00 ); // Tclk / 64  (1=4us);
            for ( i=0; i<high; i++ )
            {
                while ( TCNT0 < 0xff )
                    asm volatile ( "nop;" );
                while ( TCNT0 == 0xff )
                    asm volatile ( "nop;" );
            }
            while ( TCNT0 < low )
                asm volatile ( "nop;" );
            MOTORS_PORT &= (~SERVO2);
            TCCR0 = 0;
            taskENABLE_INTERRUPTS();
        }
        crDELAY( xHandle, pst->pwmDelay );
    }
    crEND();
}

