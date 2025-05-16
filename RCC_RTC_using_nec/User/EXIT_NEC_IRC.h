#ifndef __EXIT_NEC_IRC_H__
#define __EXIT_NEC_IRC_H__	 
#include "sys.h"


void NVIC_Configuration(void); //嵌套中断控制器的设置
void EXTI_NEC_IRC_Key_Config(void);//NEC中断红外解码初始化

 
u32 Get_NEC_RxLow_level(void); //NEC红外协议 获取低电平时间
u32 Get_NEC_RxHigh_level(void);//NEC红外协议 获取高电平时间
#endif
