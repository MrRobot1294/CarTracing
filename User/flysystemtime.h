#ifndef __FLYSYSTEMTIME_H
#define __FLTSYSTEMTIME_H
#include "stm32f10x.h"
extern int FLYTIME_5MS;;//����һ��5ms��ʱ�䣬��Ϊϵͳִ�е�����
extern int FLYTIME_10MS;
extern int FLYTIME_1s;
void systemtime_config(uint16_t period);//���ö�ʱ����Ƶ�ʣ���ֵ500��ʱ�򣬶�ʱʱ��5ms
void open_systemtime(void);
#endif

