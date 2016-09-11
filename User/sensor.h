#ifndef __SENSOR_H
#define __SENSOR_H
#include "includes.h"
void Sensor_gpio_init(void);
u8 Read_sensor1(void);
u8 Sensor_getdata(void);
void data_handler(u8 data);
void MOTOR_DRIVER(u8 temp_data,
	                u16 thrust1_base,u16 thrust2_base,
                  int thrust1_increase,int thrust2_increase,
                  u16 *pwm1,u16 *pwm2,u16 *pwm3,u16 *pwm4);
									
void thrust_aollcate(u16* motor1,u16* motor2,u16* motor3,u16* motor4);
u8 sensor_data_get(void);//获取传感器的传递的二进制值
void get_sensor_init_value(void);
void remember_value(void);

#endif 

