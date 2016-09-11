#include "includes.h"

u8 data;//传感器数据处理的二进制值

int main(void)

{
 	delay_init();//延时函数的初始化函数
	JTAG_set();
	
	LED_init();//led灯的初始化函数
	beep_init();//蜂鸣器初始化函数
	key_init();//按键初始化函数
	pwm_init();//电机的PWM初始化
	
	DisplayInit();//oled显示初始化的函数
	systemtime_config(500);//定时器的配置函数
	i2c_init();
  ldc1314_init();//LDC1314的使能函数
	Encoder_Init();
	open_systemtime();//开启系统时钟
	KEY_SET();
	//读取全局变量，初始化的值
	delay_ms(100);
  get_sensor_init_value();
	
	CH0_CIRLCE=CH0_INITVALUE-4;
	CH1_CIRLCE=CH1_INITVALUE-4;
	CH2_CIRLCE=CH2_INITVALUE-4;
	CH3_CIRLCE=CH3_INITVALUE-4;
	
	CH0_COIN_VALUE=CH0_INITVALUE+60;
	CH1_COIN_VALUE=CH1_INITVALUE+60;
	CH2_COIN_VALUE=CH2_INITVALUE+60;
	CH3_COIN_VALUE=CH3_INITVALUE+60;
	

	
	
	LAST_PWM1=THRUST1_BASE;
	LAST_PWM3=THRUST2_BASE;
	
	OLED_ShowString(0,0,"really! go!");
	OLED_Clear();
  OLED_ShowString(0,0,"len:");
	OLED_ShowString(0,2,"timer:");
	for(int i=0;i<4;i++){
		delay_ms(1000);
	}
	
	
	FLYTIME_1s=0;//开始计时
	while(1)
	{
		ShowDistance();
		data=sensor_data_get();
		if(FLYTIME_5MS>5){
			FLYTIME_5MS=0;
//		  data=sensor_data_get();
			MOTOR_DRIVER(data,
			             THRUST1_BASE,THRUST2_BASE,
			             PWM_INCREASE1,PWM_INCREASE2,
			             &PWMLEFT1,&PWMLEFT2,&PWMRIGHT1,&PWMRIGHT2);
     thrust_aollcate(&PWMLEFT1,&PWMLEFT2,&PWMRIGHT1,&PWMRIGHT2);//记住了上一次的油门值大小
		}
		
		while(((encoder_value1+encoder_value1))>distance)
		{
		  set_compare(0,0,0,0);
		}
	}
}

