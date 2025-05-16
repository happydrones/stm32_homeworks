#ifndef __key_H
#define __key_H	 


#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>

#define Key_GPIOPORT    	  GPIOC	       //定义IO接口
#define Key_Ground	        GPIO_Pin_7	 //定义IO接口 矩阵键盘做独立键盘 公共地 IO

#define K4_Pin	            GPIO_Pin_0	 //定义IO接口
#define K8_Pin	            GPIO_Pin_1	 //定义IO接口
#define K12_Pin	            GPIO_Pin_2	 //定义IO接口
#define K16_Pin	            GPIO_Pin_3	 //定义IO接口

#define Key_GPIO_RCC     RCC_APB2Periph_GPIOC   //定义IO 时钟


void Key_Init(void);//初始化
u8 Key_Independent_Value(void);//初始化
#endif
