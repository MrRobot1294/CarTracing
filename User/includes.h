#ifndef __INCLUDES_H
#define __INCLUDES_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"


#include "led.h"
#include "pwm.h"
#include "sensor.h"
#include "flysystemtime.h"
#include "delay.h"
#include "ldc1314.h"
#include "i2c.h"
#include "model.h"
#include "oled.h"
#include "encoder.h"

extern u32 distance;

extern u16 THRUST1_BASE;
extern u16 THRUST2_BASE;


extern u16 PWMLEFT1,PWMLEFT2;
extern u16 PWMRIGHT1,PWMRIGHT2;

extern int PWM_INCREASE1;
extern int PWM_INCREASE2;
extern int PWM_INCREASE3;
extern int PWM_INCREASE4;


extern u16 LAST_PWM1;
extern u16 LAST_PWM2;
extern u16 LAST_PWM3;
extern u16 LAST_PWM4;

extern u16 LDC_DATA[4];

extern int CH0_INITVALUE;
extern int CH1_INITVALUE;
extern int CH2_INITVALUE;
extern int CH3_INITVALUE;

extern int CH0_CIRLCE;
extern int CH1_CIRLCE;
extern int CH2_CIRLCE;
extern int CH3_CIRLCE;


extern int CH0_COIN_VALUE;
extern int CH1_COIN_VALUE;
extern int CH2_COIN_VALUE;
extern int CH3_COIN_VALUE;

extern int CH12_MIDDLE;
extern int CH23_MIDDLE;
extern int CH34_MIDDLE;

extern u8 coin;
///////////////////////////////////////////////////////////

extern u32 encoder_value1;
extern u32 encoder_value2;

extern u8 KEY_FLAG;

#define    MAX   60
#define    MID   30
#define    MIN   30

#endif




