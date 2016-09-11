#include "includes.h"
//
u32 distance=6600;
//油门的基础值
u16 THRUST1_BASE=999;
u16 THRUST2_BASE=999;
//油门基础值
u16 PWMLEFT1=0,PWMLEFT2=0;//正转电机左右的油门
u16 PWMRIGHT1=0,PWMRIGHT2=0;//反转电机的油门，正常的时候这个油门一定要为0

//油门增量
int PWM_INCREASE1=0;
int PWM_INCREASE2=0;
int PWM_INCREASE3=0;
int PWM_INCREASE4=0;

u16 LAST_PWM1=0;
u16 LAST_PWM2=0;
u16 LAST_PWM3=0;
u16 LAST_PWM4=0;



u16 LDC_DATA[4]={0};//ldc数据的定义区域

int CH0_INITVALUE;
int CH1_INITVALUE;
int CH2_INITVALUE;
int CH3_INITVALUE;

int CH0_CIRLCE;
int CH1_CIRLCE;
int CH2_CIRLCE;
int CH3_CIRLCE;

int CH0_COIN_VALUE;
int CH1_COIN_VALUE;
int CH2_COIN_VALUE;
int CH3_COIN_VALUE;

int CH12_MIDDLE;
int CH23_MIDDLE;
int CH34_MIDDLE;
//////////////////////////////////
////////////////////////////////////////////////////////////
u32 encoder_value1=0;
u32 encoder_value2=0;

//全局的按键标志











