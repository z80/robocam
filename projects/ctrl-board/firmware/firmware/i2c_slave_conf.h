
#ifndef __I2C_SLAVE_CONF_H_
#define __I2C_SLAVE_CONF_H_

#define I2C_OUT_BUFFER_SZ       16
#define I2C_IN_BUFFER_SZ        4
#define EXEC_QUEUE_SIZE         3
#define I2C_ADDRESS             1
#define I2C_TIMEOUT             500

#define CMD_SET_POWER_TIMES     1
#define CMD_SHUTDOWN_RESET      2
#define CMD_TEMP                3
#define CMD_CURR                4
#define CMD_SET_SOLAR_VOLT      5
#define CMD_SET_CHARGE_VOLT     6
#define CMD_SET_MOTO_EN         7
#define CMD_SET_MOTO            8
#define CMD_SET_LIGHT           9
#define CMD_SET_LED             10
// To be continued.
// .....
#define CMD_PAWN_SET_IO         11
#define CMD_PAWN_IO             12
#define CMD_PAWN_SET_MEM        13
#define CMD_PAWN_WRITE_FLASH    14
#define CMD_PAWN_RUN            15
#define CMD_PAWN_IS_RUNNING     16
#define CMD_PAWN_STOP           17


#endif




