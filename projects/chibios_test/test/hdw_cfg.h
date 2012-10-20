
#ifndef __HDW_CFG_H_
#define __HDW_CFG_H_

#define LED_CMD       "led"
#define LED_PIN       11
#define LED_PORT      GPIOB

#define PWR_RST_CMD   "pwrrst"
#define PWR_CFG_CMD   "pwrcfg"
#define PWR_PIN       10
#define PWR_PORT      GPIOB

#define MOTO_RST_CMD   "motorst"
#define MOTO_CFG_CMD   "motocfg"
#define MOTO_SET_CMD   "motoset"
#define MOTO_EN_PIN    2
#define MOTO_EN_PORT   GPIOB

#define MOTO_1_PIN   1
#define MOTO_1_PORT  GPIOB
#define MOTO_2_PIN   0
#define MOTO_2_PORT  GPIOB
#define MOTO_3_PIN   7
#define MOTO_3_PORT  GPIOA
#define MOTO_4_PIN   6
#define MOTO_4_PORT  GPIOA

#define ADC_CFG_CMD  "adccfg"
#define ADC_CMD      "adc"
#define ADC_SOL_PORT GPIOA
#define ADC_SOL_PIN  3
#define ADC_BAT_PORT GPIOA
#define ADC_BAT_PIN  2


#endif



