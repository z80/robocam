
#include "io_struct.h"
#include "uart.h"
#include "task_watchdog.h"

static void procDbg( const char * args );
static void procSetMoto( const char * args );
static void procSetMotoEn( const char * args );
static void procSetServo( const char * args );
static void procSetServoEn( const char * args );
static void procSetWatchdog( const char * args );
static void procResetWatchdog( const char * args );

extern struct TIOStr * pst;

void ioStructInit( struct TIOStr * st )
{
    st->crc = 0;
    st->pwm1 = 0;
    st->pwm2 = 0;
    st->pwmDelay = 20;
    // Инициализация портов.
    MOTORS_PORT &= ~(MOTORS_EN | MOTORS_MASK | SERVO_EN | SERVO_MASK);
    MOTORS_DDR |= MOTORS_EN | MOTORS_MASK | SERVO_EN | SERVO_MASK;

    //MOTORS_PORT |= MOTORS_EN | SERVO_EN;

    // Отключение прерываний таймера.
    TIMSK = TIMSK & ( ~((1 << OCIE0) | (1 << TOV0)) ); // disable interrupts.

    // Инициализация последовательного порта.
    uartInit( MYUBRR );
}

uint8_t encodeWord( const char * stri, char * res )
{
    uint8_t srcInd;
    uint8_t resInd;
    char ch;
    srcInd = resInd = 0;
    // Пропускаем все пробелы перед словом.
    while ( srcInd < CMD_LEN )
    {
        ch = stri[ srcInd ];
        if ( ch != ' ' )
            break;
        srcInd++;
    }
    // Если вдруг это уже конец, делаем на всякий случай результат пустой строкой.
    res[0] = '\0';
    // Добавляем символы до пробела или конца строки.
    while ( srcInd < CMD_LEN )
    {
        ch = stri[srcInd];
        if ( ( ch != ' ' ) && ( ch != '\0' ) )
            res[resInd] = ch;
        else
        {
            res[resInd] = '\0';
            return srcInd;
        }
        srcInd++;
        resInd++;
    }
    return srcInd;
}

void parseCmd( const char * cmd )
{
    static char word[ CMD_LEN ];
    static uint8_t ind = 0;
    ind = encodeWord( cmd, (char *)word );

    if ( strCmp( word, "dbg" ) == 0 )
    {
        procDbg( cmd );
    }
    else if ( strCmp( word, "setMoto" ) == 0 )
    {
        //procDbg( cmd+ind );
        procSetMoto( cmd+ind );
    }
    else if ( strCmp( word, "setMotoEn" ) == 0 )
    {
        //procDbg( cmd+ind );
        procSetMotoEn( cmd+ind );
    }
    else if ( strCmp( word, "setServoEn" ) == 0 )
    {
        //procDbg( cmd+ind );
        procSetServoEn( cmd+ind );
    }
    else if ( strCmp( word, "setServo" ) == 0 )
    {
        procSetServo( cmd+ind );
    }
    else if ( strCmp( word, "setWatchdog" ) == 0 )
    {
        procSetWatchdog( cmd+ind );
    }
    else if ( strCmp( word, "resetWatchdog" ) == 0 )
    {
        procResetWatchdog( cmd+ind );
    }
}

uint8_t strLen( const char * stri )
{
    uint8_t ind = 0;
    while ( stri[ ind ] != '\0' )
    {
        ind++;
        if ( ind == CMD_LEN )
        {
            ind--;
            break;
        }
    }
    return ind;
}

uint8_t strCmp( const char * a, const char * b )
{
    uint8_t ind = 0;
    while ( a[ind] == b[ind] )
    {
        if ( a[ind] == '\0' )
            return 0;
        ind++;
        if ( ind == CMD_LEN )
            return 0;
    }
    return 1;
}

short str2int( const char * stri )
{
    uint8_t ind = 0;
    uint8_t neg = ( stri[ind] == '-' ) ? 1 : 0;
    if ( neg )
        ind++;
    short res = 0;
    char val = stri[ ind ];
    while ( ( val >= '0' ) && ( val <= '9' ) && ( ind < CMD_LEN ) )
    {
        res *= 10;
        res += (short)( val-'0' );
        ind++;
        val = stri[ind];
    }
    if ( neg )
        res = -res;
    return res;
}

void procDbg( const char * args )
{
    char word[ CMD_LEN ];
    uint8_t ind = encodeWord( args, word );
    ind = str2int( word );
    while ( uartWrite( '0' + ind ) )
        asm( "nop;" );
    /*uint8_t i;
    for ( i=0; i<ind; i++ )
    {
        while( uartWrite( word[i] ) )
            asm( "nop;" );
    }
    while( uartWrite( ':' ) )
        asm( "nop;" );

    ind = encodeWord( args+ind, word );
    for ( i=0; i<ind; i++ )
    {
        while( uartWrite( word[i] ) )
            asm( "nop;" );
    }*/
}

void procSetMoto( const char * args )
{
    // Set flag for another coroutine handling motors.
    uint8_t ind;
    char word[ CMD_LEN ];
    ind = encodeWord( args, (char *)word );
    signed char res1 = (signed char)str2int( word );
    while ( uartWrite( '0' + res1 ) )
        asm( "nop;" );

    encodeWord( args+ind, (char *)word );
    signed char res2 = str2int( word );
    while ( uartWrite( '0' + res2 ) )
        asm( "nop;" );

    uint8_t res = 0;
    if ( res1 > 0 )
        res |= MOTOR1;
    else if ( res1 < 0 )
        res |= MOTOR2;
    if ( res2 > 0 )
        res |= MOTOR3;
    else if ( res2 < 0 )
        res |= MOTOR4;

    MOTORS_PORT = ( MOTORS_PORT & (~MOTORS_MASK) ) | res;
}

void procSetMotoEn( const char * args )
{
    // Set flag for another coroutine handling motors.
    uint8_t ind;
    char word[ CMD_LEN ];
    ind = encodeWord( args, (char *)word );
    short val = str2int( word );
    while ( uartWrite( '0' + val ) )
        asm( "nop;" );
    //PORTA = 0xff;
    //DDRA = 0xff;
    if ( val )
        MOTORS_PORT = MOTORS_PORT | MOTORS_EN;
    else
        MOTORS_PORT = MOTORS_PORT & (~MOTORS_EN);
}

void procSetServoEn( const char * args )
{
    uint8_t ind;
    char word[ CMD_LEN ];
    ind = encodeWord( args, (char *)word );
    uint8_t val = (uint8_t)str2int( word );
    while ( uartWrite( '0' + ((val & 0xf0) >> 4) ) )
        asm( "nop;" );
    val = ( val ) ? SERVO_EN : 0;
    MOTORS_PORT = ( MOTORS_PORT & (~SERVO_EN) ) | val;
}

void procSetServo( const char * args )
{
    // Set flag for another coroutine handling motors.
    uint8_t ind;
    char word[ CMD_LEN ];
    ind = encodeWord( args, (char *)word );
    pst->pwm1 = str2int( word );

    while ( uartWrite( '<' ) )
        asm( "nop;" );
    while ( uartWrite( '0' + ((pst->pwm1 & 0xf000) >> 12) ) )
        asm( "nop;" );
    while ( uartWrite( '0' + ((pst->pwm1 & 0xf00) >> 8) ) )
        asm( "nop;" );
    while ( uartWrite( '0' + ((pst->pwm1 & 0xf0) >> 4) ) )
        asm( "nop;" );
    while ( uartWrite( '0' + ((pst->pwm1 & 0x0f)) ) )
        asm( "nop;" );
    while ( uartWrite( '>' ) )
        asm( "nop;" );

    encodeWord( args+ind, (char *)word );
    pst->pwm2 = str2int( word );
}

void procSetWatchdog( const char * args )
{
    portTickType timeout;
    char word[ CMD_LEN ];
    encodeWord( args, (char *)word );
    timeout = str2int( word );
    setWatchdog( timeout );
}

void procResetWatchdog( const char * args )
{
    resetWatchdog();
}




