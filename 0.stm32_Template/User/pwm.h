#ifndef __GPIO_PWM_H__
#define __GPIO_PWM_H__

#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>

void GPIO_Out_PWM(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,u16 PWM_f,u16 PWM_Duty);
void GPIO_Out_Speet_Test(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin); //该函数临时测试stm32 gpio翻转极限速度用
void TIM2_PWM_Init(uint16_t Auto_reload_value, uint16_t Prescaler,uint8_t PWM);
void PWM_GPIO_Init(void);
#endif
