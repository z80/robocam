
#include "pawn_ctrl.h"
#include "amx.h"
#include "pawn_config.h"

#include "led_ctrl.h"
#include "stm32f10x_flash.h"

//#include "i2c_ctrl.h"

typedef struct
{
    AMX amx;
    char isRunning;
    int result, error;
    unsigned char memblock[ PAWN_MEM_SIZE ];
    uint8_t       ioblock[ PAWN_IO_SIZE ];
} Pawn;

Pawn g_pawn;

static cell n_io( AMX * amx, const cell * params );
static cell n_setIo( AMX * amx, const cell * params );
static cell n_setLeds( AMX * amx, const cell * params );

AMX_NATIVE const g_nativetable[] =
{
    n_io,
    n_setIo,
    n_setLeds
};


int AMXAPI aux_Monitor( AMX * amx )
{
    (void)amx;
    return AMX_ERR_EXIT;
}

static void pawnExec( Pawn * pawn )
{
    chSysLock();
        pawn->isRunning = 0;
    chSysUnlock();
    uint32_t i;
    unsigned char * tmp = (unsigned char *)&pawn->amx;
    for ( i=0; i<sizeof( pawn->amx ); i++ )
        tmp[i] = 0;
    pawn->result = amx_Init( &pawn->amx, pawn->memblock );
    if ( pawn->result != AMX_ERR_NONE )
        return;

    static cell ret = 0;
    chSysLock();
        pawn->isRunning = 1;
    chSysUnlock();
    pawn->error = amx_Exec( &pawn->amx, &ret, AMX_EXEC_MAIN );
    pawn->result = ret;
    amx_Cleanup( &pawn->amx );
    tmp = (unsigned char *)&pawn->amx;
    for ( i=0; i<sizeof( pawn->amx ); i++ )
        tmp[i] = 0;
    chSysLock();
        pawn->isRunning = 0;
    chSysUnlock();
}




static cell n_io( AMX * amx, const cell * params )
{
    (void)amx;
    uint32_t index;
    index = (uint32_t)params[1];
    return (cell)( g_pawn.ioblock[ index ] );
}

static cell n_setIo( AMX * amx, const cell * params )
{
    (void)amx;
    uint32_t index;
    index = (uint8_t)params[1];
    g_pawn.ioblock[ index ] = params[2];
    return 0;
}

static cell n_setLeds( AMX * amx, const cell * params )
{
    (void)amx;
    uint32_t value;
    value = (uint8_t)params[1];
    setLed( value );
    return 0;
}


























static WORKING_AREA( waExec, 1024 );
static msg_t execThread( void *arg );
static BinarySemaphore semaphore;

void pawnInit( void )
{
    // Initialize mailbox.
    chBSemInit( &semaphore, TRUE );
    // Creating thread.
    chThdCreateStatic( waExec, sizeof(waExec), NORMALPRIO, execThread, NULL );
}

void pawnSetIo( uint8_t cnt, uint8_t * vals )
{
    uint8_t i;
    for ( i=0; i<cnt; i++ )
        g_pawn.ioblock[i] = vals[i];
}

void pawnIo( uint8_t cnt, uint8_t * vals )
{
    uint8_t i;
    for ( i=0; i<cnt; i++ )
        vals[i] = g_pawn.ioblock[i];
}

void pawnSetMem( uint8_t cnt, uint16_t at, uint8_t * vals )
{
    uint16_t i;
    for ( i=0; i<cnt; i++ )
        g_pawn.memblock[at+i] = vals[i];
}

uint16_t pawnWriteFlash( uint8_t block )
{
    FLASH_Unlock();
    FLASH_Status st = FLASH_ErasePage( block + PAWN_FLASH_START );
    if ( st != FLASH_COMPLETE )
    {
        FLASH_Lock();
	return st;
    }
    uint32_t * memD   = (uint32_t *)( g_pawn.memblock );
    uint32_t   flashD = 0x800000 + PAWN_FLASH_BLOCK_SZ * ( block + PAWN_FLASH_START );
    uint32_t   i;
    for ( i=0; i<PAWN_MEM_SIZE; i+=4 )
    {
        st = FLASH_ProgramWord( flashD+i, memD[i] );
	if ( st != FLASH_COMPLETE )
	{
	    FLASH_Lock();
	    return 10+st;
	}
    }
    // to be done.
    (void)block;
    FLASH_Lock();
    return 0;
}

void pawnRun( void )
{
    chBSemSignal( &semaphore );
}

uint8_t pawnIsRunning( void )
{
    chSysLock();
        char res = g_pawn.isRunning;
    chSysUnlock();
    return res;
}

void pawnStop( void )
{
    chSysLock();
        amx_SetDebugHook( &(g_pawn.amx), aux_Monitor );
    chSysUnlock();
}

static msg_t execThread( void *arg )
{
    (void)arg;
    chRegSetThreadName( "e" );
    while ( 1 )
    {
        chBSemWait( &semaphore );

        // If's come here run Pawn machine.
        pawnExec( &g_pawn );
    }
    return 0;
}




