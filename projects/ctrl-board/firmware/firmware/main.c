
#include "ch.h"
#include "hal.h"
#include "led_ctrl.h"
#include "light_ctrl.h"
#include "power_ctrl.h"
#include "moto_ctrl.h"
#include "adc_ctrl.h"
#include "conv_ctrl.h"
#include "serial_ctrl.h"
#include "i2c_slave_ctrl.h"


//*
//* Application entry point.
//*
int main(void)
{
  halInit();
  chSysInit();

  initLed();
  initLight();
  initMoto();
  initI2cSlave();
  initPower();

  powerHandler();
  return 0;
}






