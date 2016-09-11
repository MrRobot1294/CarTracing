#include "pwm.h"

/*
PWM1=PA2
PWM2=PA3
PWM3=PB0
PWM4=PB1
*/
//PA2.....定时器二通道3
//PA3.....定时器er通道4

//PB0......定时器三通道3
//PB1......定时器三通道4


//定时器二：PA2...PA3
void timer2_gpio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void timer2_mode_config(u32 arr,u32 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// 
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx	
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH1预装载使能	
	TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIMx在ARR上的预装载寄存器	
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2  
}

void timer3_gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;	
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

void timer3_mode_config(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//???????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//????????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=arr;//????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low ;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
  TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);  
	TIM_Cmd(TIM3,ENABLE);
}





void set_compare(u16 crr1,u16 crr2,u16 crr3,u16 crr4)
{
		TIM_SetCompare3(TIM2,crr1); 
	  TIM_SetCompare4(TIM2,crr2); 
	  TIM_SetCompare3(TIM3,crr3); 
	  TIM_SetCompare4(TIM3,crr4); 
	
	
}

void pwm_init(void)//电机初始化函数
{
	/*初始化定时器*/
	 timer2_gpio();
	 timer2_mode_config(999,3);
	 timer3_gpio();
	 timer3_mode_config(999,3);
	
	 set_compare(0,0,0,0);
}




