#ifndef __ESC_H__
#define __ESC_H__

#include "stm32f10x.h" 
#include "pwm.h"

void esc_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void esc_set_speed(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t speed);
#endif

