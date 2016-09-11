#include "encoder.h"

static void Encoder_PortConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=ENCODER_PIN1|ENCODER_PIN2;
	GPIO_Init(ENCODER_PORT,&GPIO_InitStruct);
}

static void Encoder_RccConfig(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

static void Encoder_ExtiConfig(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line=EXTI_Line8|EXTI_Line9;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8|GPIO_PinSource9);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
}


void Encoder_Init(void)
{
	Encoder_RccConfig();
	Encoder_PortConfig();
	Encoder_ExtiConfig();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	delay_init();
}




void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8)==SET)
	{
		delay_ms(1);
		if(GPIO_ReadInputDataBit(ENCODER_PORT,ENCODER_PIN1)==RESET)//下降沿中断，所以判断是否为低电平
		{
			encoder_value1++;
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(EXTI_GetITStatus(EXTI_Line9)==SET)
	{
		delay_ms(1);
		if(GPIO_ReadInputDataBit(ENCODER_PORT,ENCODER_PIN2)==RESET)//下降沿中断，所以判断是否为低电平
		{
			encoder_value2++;

		}
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

