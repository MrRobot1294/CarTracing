#include "model.h"
////////////////////////////OLED的现实函数/////////////////////////
#define CM_PER_CNT   1   //码盘动一次对用多少cm

void DisplayInit(void)
{
	OLED_Init();
	OLED_Clear();


}
void ShowDistance(void)
{
	u16 average_legth=0;
//	OLED_ShowString(0,0,"length:");
//	OLED_ShowString(0,2,"timer:");
	u32 trueDistance_cm_code1=0;
	u32 trueDistance_cm_code2=0;
	trueDistance_cm_code1=encoder_value1*CM_PER_CNT;
	trueDistance_cm_code2=encoder_value2*CM_PER_CNT;
	average_legth=(u16)((trueDistance_cm_code1+trueDistance_cm_code2));
//	OLED_Clear();
	OLED_ShowNum(40,0,average_legth,5,16);
//	OLED_ShowNum(50,2,FLYTIME_1s,6,16);
	if(FLYTIME_1s>500){
	  FLYTIME_1s-=50;
	}
	OLED_ShowNum(42,2,(FLYTIME_1s/10-1),2,16);
	OLED_ShowChar(60,2,'.');
	OLED_ShowNum(65,2,FLYTIME_1s%10,1,16);
	OLED_ShowChar(80,2,'S');
}




//按键程序的初始化函数  A0  A1  B12 
void key_init(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}
//凤鸣器的初始化函数  B13
void beep_init(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);//先关闭蜂鸣器
}

void beep_on(void){
  GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

void beep_off(void){
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}


u8 read_key1(void){
  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0){
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0){
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0);
			return 1;
		}
	}
	return 0;
}

u8 read_key2(void){
  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0){
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0){
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0);
			return 1;
		}
	}
	return 0;
}

u8 read_key3(void){
  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==0){
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==0){
		  while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==0);
			return 1;
		}
	}
	return 0;
}


void KEY_SET(void){
	static u8 speed_ok=0;
	static u8 distance_ok=0;
	while(!speed_ok){
		OLED_ShowString(0,0,"speed:  ");
		OLED_ShowNum(40,0,THRUST1_BASE,6,16);
		if(read_key1()==1){
		  THRUST1_BASE++;
			THRUST2_BASE++;
		}
		
		if(read_key2()==1){
		  THRUST1_BASE--;
			THRUST2_BASE--;
		}
		
		if(read_key3()==1){
		 speed_ok=1;
		}
	
	}
	OLED_Clear();
	while(!distance_ok){
	  OLED_ShowString(0,0,"dis:  ");
		OLED_ShowNum(40,0,distance,6,16);
		if(read_key1()==1){
		  distance++;
		}
		
		if(read_key2()==1){
		  distance--;
		}
		
		if(read_key3()==1){
		 distance_ok=1;
		}
	}
}








