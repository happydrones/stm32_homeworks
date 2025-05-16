#ifndef __EXIT_NVIC_H__
#define __EXIT_NVIC_H__	 
#include "sys.h"


//extern u8 INT_MARK;//中断标志位


//void KEYPAD4x4_INT_INIT (void);
void NVIC_Configuration(void); //嵌套中断控制器的设置
void EXTI_Key_Config(void);
#endif
