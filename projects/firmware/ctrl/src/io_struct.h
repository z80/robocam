
#ifndef __IO_STRUCT_H_
#define __IO_STRUCT_H_

#include <avr/io.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define CMD_LEN     64

#define MOTORS_PORT PORTA
#define MOTORS_DDR  DDRA

#define MOTORS_EN   (1<<0)
#define MOTOR1      (1<<1)
#define MOTOR2      (1<<2)
#define MOTOR3      (1<<3)
#define MOTOR4      (1<<4)
#define SERVO1      (1<<5)
#define SERVO2      (1<<6)
#define SERVO_EN    (1<<7)
#define MOTORS_MASK (MOTOR1 | MOTOR2 | MOTOR3 | MOTOR4)
#define SERVO_MASK  ( SERVO1 | SERVO2 )

struct TIOStr
{
    uint8_t crc;
    uint16_t pwm1,
             pwm2,
             pwmDelay;
};

void ioStructInit( struct TIOStr * st );
void parseCmd( const char * cmd );
uint8_t encodeWord( const char * stri, char * res );
uint8_t strLen( const char * stri );
uint8_t strCmp( const char * a, const char * b );
short str2int( const char * stri );

#endif
