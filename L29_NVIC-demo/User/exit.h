#ifndef __EXIT_H__
#define __EXIT_H__

#include "stm32f10x.h" 

#define KEY_UP_EXTI_GPIO_RCC  		RCC_APB2Periph_GPIOC //GPIOC
#define KEY_UP_EXTI_GPIO_PORT  	    GPIOC
#define KEY_UP_GPIO_PORTSOURCE      GPIO_PortSourceGPIOC
#define KEY_UP_EXTI_GPIO_PIN   		GPIO_Pin_0
#define KEY_UP_EXTI_LINE          	EXTI_Line0
#define KEY_UP_GPIO_PINSOURCE       GPIO_PinSource0
#define KEY_UP_EXTI_IRQN  			EXTI0_IRQn

#define KEY_DOWN_EXTI_GPIO_RCC  	RCC_APB2Periph_GPIOC //GPIOC
#define KEY_DOWN_EXTI_GPIO_PORT  	GPIOC
#define KEY_DOWN_GPIO_PORTSOURCE	GPIO_PortSourceGPIOC
#define KEY_DOWN_EXTI_GPIO_PIN   	GPIO_Pin_3
#define KEY_DOWN_EXTI_LINE          EXTI_Line3
#define KEY_DOWN_GPIO_PINSOURCE		GPIO_PinSource3
#define KEY_DOWN_EXTI_IRQN 			EXTI3_IRQn

#endif