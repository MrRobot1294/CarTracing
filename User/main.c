#include "includes.h"

u8 data;//���������ݴ���Ķ�����ֵ

int main(void)

{
 	delay_init();//��ʱ�����ĳ�ʼ������
	JTAG_set();
	
	LED_init();//led�Ƶĳ�ʼ������
	beep_init();//��������ʼ������
	key_init();//������ʼ������
	pwm_init();//�����PWM��ʼ��
	
	DisplayInit();//oled��ʾ��ʼ���ĺ���
	systemtime_config(500);//��ʱ�������ú���
	i2c_init();
  ldc1314_init();//LDC1314��ʹ�ܺ���
	Encoder_Init();
	open_systemtime();//����ϵͳʱ��
	KEY_SET();
	//��ȡȫ�ֱ�������ʼ����ֵ
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
	
	
	FLYTIME_1s=0;//��ʼ��ʱ
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
     thrust_aollcate(&PWMLEFT1,&PWMLEFT2,&PWMRIGHT1,&PWMRIGHT2);//��ס����һ�ε�����ֵ��С
		}
		
		while(((encoder_value1+encoder_value1))>distance)
		{
		  set_compare(0,0,0,0);
		}
	}
}

