#include "includes.h"


void get_sensor_init_value(void){
	u32 ch0_sensor=0;
	u32 ch1_sensor=0;
	u32 ch2_sensor=0;
	u32 ch3_sensor=0;
	
  for(int i=0;i<100;i++){
	  ldc_read_data(LDC_DATA);
		ch0_sensor+=LDC_DATA[0];
		ch1_sensor+=LDC_DATA[1];
		ch2_sensor+=LDC_DATA[2];
		ch3_sensor+=LDC_DATA[3];
		delay_ms(10);
	}
	
	CH0_INITVALUE=(u16)(ch0_sensor/100);
	CH1_INITVALUE=(u16)(ch1_sensor/100);
	CH2_INITVALUE=(u16)(ch2_sensor/100);
	CH3_INITVALUE=(u16)(ch3_sensor/100);
	
}

u8 sensor_data_get(void){
  u8 value=0x00;
	ldc_read_data(LDC_DATA);//读取传感器的数据
	if(LDC_DATA[0]<CH0_CIRLCE){
	   value|=0x01;
		led0_on();
	}else
	{
	  led0_off();
	}
	
	if(LDC_DATA[1]<CH1_CIRLCE){
	   value|=0x02;
		led1_on();
	}else{
	  led1_off();
	}
	
	if(LDC_DATA[2]<CH2_CIRLCE){
	   value|=0x04;
		led2_on();
	}else{
	  led2_off();
	}
	
	if(LDC_DATA[3]<CH3_CIRLCE){
	   value|=0x08;
		led3_on();
	}else{
	  led3_off();
	}
	
	if((LDC_DATA[0]>=CH0_COIN_VALUE)||(LDC_DATA[1]>=CH1_COIN_VALUE)||(LDC_DATA[2]>=CH2_COIN_VALUE)||(LDC_DATA[3]>=CH3_COIN_VALUE)||(LDC_DATA[0]-CH0_INITVALUE<-60)||(LDC_DATA[1]-CH1_INITVALUE)<-60||(LDC_DATA[2]-CH2_INITVALUE)<-60||(LDC_DATA[3]-CH3_INITVALUE)<-60){
		//蜂鸣器响
		beep_on();
	}else{
		//蜂鸣器不想
		beep_off();
	}
	
//	if((LDC_DATA[0]-CH0_INITVALUE<-60)||(LDC_DATA[1]-CH1_INITVALUE)<-60||(LDC_DATA[2]-CH2_INITVALUE)<-60||(LDC_DATA[3]-CH3_INITVALUE)<-60){
//	  beep_on();
//	}else{
//	  beep_off();
//	}
	return value;
}

//PWM1   左电机正传
//PWM2   右电机正传
//PWM3   左电机反转
//PWM4   右电机反转

//带入函数
void MOTOR_DRIVER(u8 temp_data,
	                u16 thrust1_base,u16 thrust2_base,
                  int thrust1_increase,int thrust2_increase,
                  u16 *pwm1,u16 *pwm2,u16 *pwm3,u16 *pwm4){
	//左大偏
  switch(temp_data){
		//lefe max  leftmotor+++
	  case 0x01:
//			thrust1_increase=150;
//		  thrust2_increase=0;
			*pwm1=1000;  //left+   ++
		  *pwm2=0;                              //left-   0 
		  *pwm3=340;															//right+  
		  *pwm4=0;   												  //right-  +
		break;
		
		//left min left +
		case 0x02:
			thrust1_increase=30;
		  thrust2_increase=-30;
			*pwm1=thrust1_base+thrust1_increase;
		  *pwm2=0;
		  *pwm3=thrust2_base+thrust2_increase;
		  *pwm4=0;
		break;
		
		//right min
		case 0x04:
			thrust1_increase=-30;
			thrust2_increase=30;	  
			*pwm1=thrust1_base+thrust1_increase;
		  *pwm2=0;
		  *pwm3=thrust2_base+thrust2_increase;
		  *pwm4=0;
		break;
		
		
		//(right MAX)
		case 0x08:
//			thrust1_increase=0;
//			thrust2_increase=150;	
			*pwm1=340;
		  *pwm2=0;
		  *pwm3=1000;
		  *pwm4=0;
		break;
		
		default: 
      *pwm1=LAST_PWM1;
		  *pwm2=LAST_PWM2;
		  *pwm3=LAST_PWM3;
		  *pwm4=LAST_PWM4;
		break;
	}
	
}


void thrust_aollcate(u16* motor1,u16* motor2,u16* motor3,u16* motor4){
	remember_value();
  set_compare(*motor1,*motor2,*motor3,*motor4);
}

void remember_value(void){
  LAST_PWM1=PWMLEFT1;
	LAST_PWM2=PWMLEFT2;
	LAST_PWM3=PWMRIGHT1;
	LAST_PWM4=PWMRIGHT2;
}









