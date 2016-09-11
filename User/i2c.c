#include "i2c.h"


//i2c的引脚
//SCL  PA2
//SDA  PA3
//INT  PA4

#include "i2c.h"
//关于i2c协议，当scl=0的时候数据才会进行传输，当sda=0的时候抓住总线，因为这个时候另一方即使为1呀无法改变
//sda的状态，当连续的读写写注意主机发送的ack信号
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



//开始信号
void i2c_start(void)//条件:当scl线为高的时候，sda有高到低
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

//停止信号
void i2c_stop(void)//条件：当scl为高的时候，sda由低到高
{
	scl_0();
  sda_0();
	i2c_delay();
	scl_1();
	sda_1();
	i2c_delay();
}

//ack信号
void i2c_wait_ack(void) //谁应答谁就吧sda拉低
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
		scl_0();//scl拉低开始传输数据
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

//读取一个字节的数据
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
	sda_0(); //拉低，产生ACK信号，scl=0是才能传递数据，为了下次能够继续床底数据此处的scl=0应该做好
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






