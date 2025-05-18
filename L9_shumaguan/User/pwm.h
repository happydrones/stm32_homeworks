#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f10x.h" 

void Pwm_Port_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Pwm_generate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,uint16_t PWM_Frequency, uint8_t PWM_Duty,uint16_t loop_times);


#endif

