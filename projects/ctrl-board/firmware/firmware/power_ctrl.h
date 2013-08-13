
#ifndef __POWER_CTRL_H_
#define __POWER_CTRL_H_

#include "ch.h"
#include "shell.h"

void initPower( void );
// To be called in main loop.
void powerHandler( void );

void setPowerTimeout( int activeTime );
void powerOffReset( void );

// Time management functions.
// Seconds per one day.
void setSecondsPerDay( uint32_t cnt );
// Set current time to adjust time counting imperfectness.
void setCurrentTime( int32_t t );
// Obtain current time
uint32_t currentTime( void );
// Wakeups number per day.
void setWakeupsCnt( uint16_t cnt );
// Configure particular wakeup.
void setWakeup( uint8_t index, int32_t t );

#endif





