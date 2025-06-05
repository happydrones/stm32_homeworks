#ifndef    __TIMER_H
#define   __TIMER_H

#include "stm32f10x.h"  
extern volatile uint8_t timer_flag;
extern volatile uint32_t ic_rise;
extern volatile uint32_t ic_fall;
extern volatile uint32_t pulse_width;

void timer3_init(uint16_t Auto_reload_value,uint16_t Prescaler);//开启定时器3
void TIM4_InputCapture_Init(void);//开启定时器4输入捕获 
#endif
