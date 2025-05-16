#ifndef __delay_H__
#define __delay_H__

#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>

void Delay_ms(u16 X_ms);  //延迟  X_ms*1  默认状态不配置rcc 默认时钟
void Delay_10us(u16 t);
void Delay_us(u16 X_us);  //延迟  X_us*1  默认状态不配置rcc 默认时钟
#endif
