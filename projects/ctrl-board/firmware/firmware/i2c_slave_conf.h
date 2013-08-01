
#ifndef __I2C_SLAVE_CONF_H_
#define __I2C_SLAVE_CONF_H_

#define OSC_SIZE                1024

#define I2C_OUT_BUFFER_SZ       16
#define I2C_IN_BUFFER_SZ        8  // Command id as 1 byte and up to 2 two byte numbers = 5 bytes.
#define EXEC_QUEUE_SIZE         3
#define I2C_ADDRESS             1
#define I2C_TIMEOUT             500

#define CMD_SET_POWER_TIMES     1
#define CMD_POWER_RESET         2
#define CMD_SHUTDOWN_RESET      3
#define CMD_TEMP                4
#define CMD_CURR                5
#define CMD_SET_SOLAR_VOLT      6
#define CMD_SET_CHARGE_VOLT     7
#define CMD_SET_MOTO_EN         8
#define CMD_SET_MOTO            9
#define CMD_SET_LIGHT           10
#define CMD_SET_LED             11
#define CMD_BUCK_FB             12
#define CMD_BOOST_FB            13
#define CMD_SOLAR_FB            14
// Commands for power oscilloscope.
#define CMD_SETUP_OSC           15 // 2 bytes period in seconds, 1 byte what to measure: current, temperature.
#define CMD_OSC_STATUS          16 // 2 bytes number of measures in memory and 1 byte signals measured.
#define CMD_OSC                 17 // Get value/values by index. 0 - most recent, 1 - previous, 2 - prev-previous.
// To be continued.
// .....
#define CMD_PAWN_SET_IO         15
#define CMD_PAWN_IO             16
#define CMD_PAWN_SET_MEM        17
#define CMD_PAWN_WRITE_FLASH    18
#define CMD_PAWN_RUN            19
#define CMD_PAWN_IS_RUNNING     20
#define CMD_PAWN_STOP           21


#endif




