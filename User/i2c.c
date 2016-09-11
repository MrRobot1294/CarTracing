#include "i2c.h"


//i2c������
//SCL  PA2
//SDA  PA3
//INT  PA4

#include "i2c.h"
//����i2cЭ�飬��scl=0��ʱ�����ݲŻ���д��䣬��sda=0��ʱ��ץס���ߣ���Ϊ���ʱ����һ����ʹΪ1ѽ�޷��ı�
//sda��״̬���������Ķ�ддע���������͵�ack�ź�
void i2c_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=scl_pin|sda_pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	scl_1();
	sda_1();
}

void i2c_delay(void)
{
  delay_us(5);
}



//��ʼ�ź�
void i2c_start(void)//����:��scl��Ϊ�ߵ�ʱ��sda�иߵ���
{
  sda_1();
	i2c_delay();
	scl_1();
	i2c_delay();
	sda_0();
	i2c_delay();
	scl_1();
	i2c_delay();
}

//ֹͣ�ź�
void i2c_stop(void)//��������sclΪ�ߵ�ʱ��sda�ɵ͵���
{
	scl_0();
  sda_0();
	i2c_delay();
	scl_1();
	sda_1();
	i2c_delay();
}

//ack�ź�
void i2c_wait_ack(void) //˭Ӧ��˭�Ͱ�sda����
{
	u8 temp=0;
  scl_1();
	i2c_delay();
	sda_1();
	i2c_delay();
	while((sda_state==1)&&(temp<254)) temp++;
			scl_0();
}

void i2c_writebyte(unsigned char writebyte)
{
  unsigned char i;
	unsigned char temp=0;
	u8 temp2;
	temp=writebyte;
	
	for(i=0;i<8;i++)
	{
		temp2=temp>>7;
		scl_0();//scl���Ϳ�ʼ��������
		i2c_delay();
    if(temp2)
			sda_1();
		else
			sda_0();
		i2c_delay();
		scl_1();
		i2c_delay();	
		temp<<=1;
  }
	scl_0();
	i2c_delay();
	sda_1();
  i2c_delay();	
}

//��ȡһ���ֽڵ�����
unsigned char i2c_readbyte(void)
{
  unsigned char temp=0;
	unsigned char i;
  sda_1();
	i2c_delay();	
	for(i=0;i<8;i++)
	{
		scl_0();
	  i2c_delay();	
		temp=temp<<1;	  		
		scl_1();
		i2c_delay();
		if(sda_state==1)
			temp++;		
		i2c_delay();	    
  }
	return temp;	
}


void sendack(void){
	scl_0();
	i2c_delay();
	sda_0(); //���ͣ�����ACK�źţ�scl=0�ǲ��ܴ������ݣ�Ϊ���´��ܹ������������ݴ˴���scl=0Ӧ������
	i2c_delay();
	scl_1();
	i2c_delay();
	scl_0();
}
void sendnack(void){
	scl_0();
	i2c_delay();  
  sda_1();
	i2c_delay();
	scl_1();
	i2c_delay();
	scl_0();
	i2c_delay();  
}






