#ifndef __I2C_H
#define __I2C_H
#include "delay.h"
#include "stm32f10x.h"
#include "includes.h"

#define scl_pin   GPIO_Pin_4  
#define sda_pin   GPIO_Pin_5 
#define scl_gpio  GPIOA
#define sda_gpio  GPIOA

#define scl_1()   GPIO_SetBits(scl_gpio,scl_pin)
#define sda_1()   GPIO_SetBits(sda_gpio,sda_pin)
#define scl_0()   GPIO_ResetBits(scl_gpio,scl_pin)
#define sda_0()   GPIO_ResetBits(sda_gpio,sda_pin)

#define sda_state GPIO_ReadInputDataBit(sda_gpio,sda_pin)


void i2c_delay(void);
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_writebyte(unsigned char writebyte);
unsigned char i2c_readbyte(void);
void i2c_wait_ack(void);
void sendack(void);
void sendnack(void);

#endif


