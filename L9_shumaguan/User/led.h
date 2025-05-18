#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h" 


#define   LED0 GPIO_Pin_0
void LED_Init(GPIO_TypeDef* GPIOx);
void LED_On(GPIO_TypeDef* GPIOx, uint16_t LED_number);
void LED_Off(GPIO_TypeDef* GPIOx, uint16_t LED_number);

// 声明全局变量
extern int8_t ledStatus; // 使用 extern 声明全局变量

#endif

