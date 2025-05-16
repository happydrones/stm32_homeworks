#ifndef __KeyScan_4x4_H
#define __KeyScan_4x4_H	 


#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>

#define Key_GPIOPORT    	  GPIOC	       //定义IO接口
 


#define Key_GPIO_RCC     RCC_APB2Periph_GPIOC   //定义IO 时钟
#define Key_Long_Time     200           //10ms *200  =2S  延迟函数

void Key_4x4_Scan_GPIO_Init(u16 Key_Ground_GPIO_Pin);//矩阵键盘扫描 行给 0 初始化
u8 KeyScan_4x4_Value(void);  //矩阵键盘键值函数
#endif
