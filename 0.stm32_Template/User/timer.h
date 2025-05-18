#ifndef    __TIMER_H
#define   __TIMER_H

#include "stm32f10x.h"  
extern volatile uint8_t timer_flag;

void timer3_init(uint16_t Auto_reload_value,uint16_t Prescaler);//开启定时器3
#endif
