
#ifndef  __ENCODER_H
#define  __ENCODER_H

#include "includes.h"
/*
 * ʹ��˵��
 * ��ENCODER_PORT��ENCODER_PIN�������ñ�����������˿�
 * ��ֲ��ʱ�򣬻���Ҫ�޸��������ã�
 *   1.�޸�Encoder_RccConfig()�����ж�Ӧ��RCC��
 *   2.�޸�Encoder_ExtiConfig()�����е�EXTI_InitStruct.EXTI_Line=EXTI_Line8��
 *                                                              ^^^^^^^^^^
 *     GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8)��
 *                         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *     NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
 *                                     ^^^^^^^^^^^^
 *   3.�޸��жϷ�����EXTI9_5_IRQHandler()��
 *   4.ʹ��ʱҪ����NVIC�ķ��顣
 * Example:
 * 	Encoder_Init();
 *  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	
 */
#define ENCODER_PORT GPIOA
#define ENCODER_PIN1  GPIO_Pin_8
#define ENCODER_PIN2 GPIO_Pin_9

void Encoder_Init(void);

#endif





