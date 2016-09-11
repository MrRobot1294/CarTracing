
#ifndef  __ENCODER_H
#define  __ENCODER_H

#include "includes.h"
/*
 * 使用说明
 * 宏ENCODER_PORT和ENCODER_PIN用于配置编码器的输入端口
 * 移植的时候，还需要修改以下配置：
 *   1.修改Encoder_RccConfig()函数中对应的RCC；
 *   2.修改Encoder_ExtiConfig()函数中的EXTI_InitStruct.EXTI_Line=EXTI_Line8，
 *                                                              ^^^^^^^^^^
 *     GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8)；
 *                         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *     NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
 *                                     ^^^^^^^^^^^^
 *   3.修改中断服务函数EXTI9_5_IRQHandler()；
 *   4.使用时要设置NVIC的分组。
 * Example:
 * 	Encoder_Init();
 *  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	
 */
#define ENCODER_PORT GPIOA
#define ENCODER_PIN1  GPIO_Pin_8
#define ENCODER_PIN2 GPIO_Pin_9

void Encoder_Init(void);

#endif





