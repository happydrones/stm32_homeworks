#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h" 

#define   LED_PORT       GPIOA
#define   LED_PORT_RCC   RCC_APB2Periph_GPIOC

#define   down_LED       GPIO_Pin_0
#define   right_LED      GPIO_Pin_1
#define   left_LED       GPIO_Pin_2
#define    up_LED        GPIO_Pin_3

void LED_Init(GPIO_TypeDef* GPIOx);
void Single_Led_Init(GPIO_TypeDef* GPIOx,  uint16_t GPIO_Pin_x);
void LED_On(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x);
void LED_Off(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x);
void LED_Toggle(GPIO_TypeDef* GPIOx,  uint16_t GPIO_Pin_x);

// 声明全局变量
extern int8_t ledStatus; // 使用 extern 声明全局变量

#endif

