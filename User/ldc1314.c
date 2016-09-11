#include "ldc1314.h"
#include "i2c.h"

//#define  slaver_addr    必须声明
void writebyte(u8 reg_addr,u8 info)
{
  i2c_start();
	i2c_writebyte(slaver_addr);
	i2c_wait_ack();
	i2c_writebyte(reg_addr);
	i2c_wait_ack();
	i2c_writebyte(info);
	i2c_wait_ack();
	i2c_stop();
	delay_ms(5);
}



void readbytes(u8 reg_addr,u8 length,u8* buffer){
	int i;
	i2c_start();
	i2c_writebyte(slaver_addr);
	i2c_wait_ack();
	i2c_writebyte(reg_addr);
	i2c_wait_ack();
	i2c_start();
	i2c_writebyte(slaver_addr+1);
	i2c_wait_ack();
	for(i=0;i<length;i++){
		buffer[i]=i2c_readbyte();
	  if(i!=(length-1)){
			sendack();
		}else{
			sendnack();
		}		
	}
	i2c_stop();
}


unsigned char read_onebyte(u8 reg_addr)
{
  u8 i;
	i2c_start();
	i2c_writebyte(slaver_addr);//先写入，后写出  0xa0
	i2c_wait_ack();
	i2c_writebyte(reg_addr);
	i2c_wait_ack();
	i2c_start();
	i2c_writebyte(slaver_addr+1);//发送读信号
	i2c_wait_ack();
	i=i2c_readbyte();
	i2c_stop();
	delay_ms(5);
	return i;
}


void ldc1314_write(u8 addr,u8 regist,u16 data){	
	u8 data_lsb=(u8)(data&0x00ff);//低位
	u8 data_msb=(u8)(data>>8);//高位
	i2c_start();
	i2c_writebyte(slaver_addr<<1);
	i2c_wait_ack();
	i2c_writebyte(regist);
	i2c_wait_ack();
	i2c_writebyte(data_msb);
	i2c_wait_ack();
	i2c_writebyte(data_lsb);
}	




u16 read_ldc1314(u8 addr,u8 regist){
	u8 data_msb=0;
	u8 data_lsb=0;
	u16 data=0;
  i2c_start();
	i2c_writebyte((slaver_addr<<1));
	i2c_wait_ack();
	i2c_writebyte(regist);
	i2c_wait_ack();
	i2c_start();
	i2c_writebyte((slaver_addr<<1)+1);
	i2c_wait_ack();
	data_msb=i2c_readbyte();
	sendack();
	data_lsb=i2c_readbyte();
	sendnack();
	i2c_stop();
	data|=data_msb;
	data=data<<8;
	data|=data_lsb;
	return data;
}


//寄存器的配置
void ldc1314_init(void){
  ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH0,0x04d6);//配置的是传感器的转化时间
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH1,0x04d6);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH2,0x04d6);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_REF_COUNT_CH3,0x04d6);
	
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH0,0x29ff);//转化的偏移量
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH1,0x29ff);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH2,0x29ff);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_OFFSET_CH3,0x29ff);

	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH0,0x000A);//利用这个时间让lc稳定在通道数据稳定之前
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH1,0x000A);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH2,0x000A);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH3,0x000A);
	
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH0,0x1005);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH1,0x1005);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH2,0x1005);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH3,0x1005);
	
	
	
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_MUX_CONFIG,0xC20C);


	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH0,0x6000);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH1,0x7000);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH2,0x7000);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH3,0x6000);
	
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_RESET_DEVICE,0x0600);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_SYSTEM_CLOCK_CONFIG,0x0200);
	ldc1314_write(slaver_addr,LDC13xx16xx_CMD_CONFIG,0x1601);
}

void ldc_read_data(u16* data_sum){
	
  data_sum[0]=read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH0);

	data_sum[1]=read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH1);

	data_sum[2]=read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH2);

	data_sum[3]=read_ldc1314(slaver_addr,LDC13xx16xx_CMD_DATA_MSB_CH3);	
}





