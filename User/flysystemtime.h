#ifndef __FLYSYSTEMTIME_H
#define __FLTSYSTEMTIME_H
#include "stm32f10x.h"
extern int FLYTIME_5MS;;//定义一个5ms的时间，作为系统执行的周期
extern int FLYTIME_10MS;
extern int FLYTIME_1s;
void systemtime_config(uint16_t period);//设置定时器的频率，当值500的时候，定时时间5ms
void open_systemtime(void);
#endif

