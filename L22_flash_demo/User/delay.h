#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32f10x.h" 
#define RCC_SysTclk 72

void delay_us(u16 nCount);
void delay_ms(u16 nCount);
void delay_s(u16 nCount);
void delay_10us(u16 nCount);
void Systick_delay_us(uint32_t X_us);
void Systick_delay_ms(uint32_t X_ms);
void Systick_delay_10us(uint32_t X_us);

#endif

