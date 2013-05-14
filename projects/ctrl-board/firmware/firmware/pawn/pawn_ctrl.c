
#include "pawn_ctrl.h"
#include "amx.h"
#include "pawn_config.h"

#include "led_ctrl.h"

//#include "i2c_ctrl.h"

typedef struct
{
    AMX amx;
    char isRunning;
    int result, error;
    unsigned char memblock[ PAWN_MEM_SIZE ];
    uint32_t      ioblock[ PAWN_IO_SIZE ];
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

void pawnStop( Pawn * pawn )
{
    chSysLock();
        amx_SetDebugHook( &pawn->amx, aux_Monitor );
    chSysUnlock();
}

char pawnIsRunning( Pawn * pawn )
{
    chSysLock();
        char res = pawn->isRunning;
    chSysUnlock();
    return res;
}

static void pawnRun( Pawn * pawn )
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
    index = (uint32_t)params[1];
    g_pawn.ioblock[ index ] = params[2];
    return 0;
}

static cell n_setLeds( AMX * amx, const cell * params )
{
    (void)amx;
    uint32_t value;
    value = (uint32_t)params[1];
    setLed( value );
    return 0;
}



























void pawnInit( void )
{

}



