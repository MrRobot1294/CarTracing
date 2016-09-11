#include "flysystemtime.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"

int FLYTIME_5MS;//200hz 
int FLYTIME_10MS;
int FLYTIME_1s;
//定时器4的初始化程序
void systemtime_config(uint16_t period){
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Down;
	TIM_TimeBaseInitStructure.TIM_Period=period;//72000000/psc/72 us
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
  //TIM_Cmd(TIM4,ENABLE);//使能定时器
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
}

void open_systemtime(void){
  TIM_Cmd(TIM4,ENABLE);//使能定时器
}


void TIM4_IRQHandler()
{
	 
  if(TIM_GetITStatus(TIM4,TIM_IT_Update)==1)
	{
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    FLYTIME_5MS++;
		FLYTIME_10MS++;
		if(FLYTIME_10MS>200){
			FLYTIME_10MS=0;
		  FLYTIME_1s++;
		}
  }
}


