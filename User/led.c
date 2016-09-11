#include "led.h"


void JTAG_set(void){
  RCC->APB2ENR|=1<<0;
	AFIO->MAPR&=0XF8FFFFFF;
	AFIO->MAPR|=1<<25;
	
}

void LED_init(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	led0_off();
	led1_off();
	led2_off();
	led3_off();
}

void led_on(void){
  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}

void led_off(void){
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
}

///////////////////////////////////////////////////////////////////////////
void led0_on(void){
  GPIO_ResetBits(GPIOB,GPIO_Pin_2);
}
void led1_on(void){
  GPIO_ResetBits(GPIOB,GPIO_Pin_3);
}
void led2_on(void){
  GPIO_ResetBits(GPIOB,GPIO_Pin_4);
}
void led3_on(void){
  GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}

void led0_off(void){
  GPIO_SetBits(GPIOB,GPIO_Pin_2);
}
void led1_off(void){
  GPIO_SetBits(GPIOB,GPIO_Pin_3);
}
void led2_off(void){
  GPIO_SetBits(GPIOB,GPIO_Pin_4);
}
void led3_off(void){
  GPIO_SetBits(GPIOB,GPIO_Pin_10);
}

void all_off(void){
  led0_off();
	led1_off();
	led2_off();
	led3_off();
}
	
	


