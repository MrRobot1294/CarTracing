#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"

//定时器3的三四通道是pb0,pb1
//定时器1的三四通道是pa10..pa11
void pwm_init(void);//电机初始化函数
void timer1_gpio(void);
void timer1_mode_config(u32 arr,u32 psc);
void set_compare(u16 crr1,u16 crr2,u16 crr3,u16 crr4);
/*
void get_last_motor_data(u16 last_pwm1,u16 last_pwm2,u16 last_pwm3,u16 last_pwm4);
void motor_step(u16 motor1,u16 motor2,u16 motor3,u16 motor4);
*/
#endif

