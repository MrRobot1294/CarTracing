
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              SCL   ��PB9��SCL��
//              SDA   ��PB8��SDA��
//              RES  ��PB7
//              DC   ��PB6
//              CS   ��PB5               
//              ----------------------------------------------------------------
#ifndef __OLED_H
#define __OLED_H		
#include "includes.h"
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------����LED�˿ڶ���---------------- 
#define LED_ON GPIO_ResetBits(GPIOD,GPIO_Pin_2)
#define LED_OFF GPIO_SetBits(GPIOD,GPIO_Pin_2)

//-----------------OLED�˿ڶ���----------------  					   


#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)//SCK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_7)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_5)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



