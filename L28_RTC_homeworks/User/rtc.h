/**
  **********************************************************************
  * @file    rtc.h
  * @author  oscar
  * @version v0.2.0
  * @date    2025-05-15
  * @brief   This file contains all the functions prototypes for the 
  * 		 RTC driver and Time setting.
  *          
  *
  * @note    Implemented a digital clock system based on STM32.
  * @function   --show current time on 1602 LCD.
  *             --set time by keypad & UART host interface.
  *       
  **********************************************************************
  * @version
  * 2025-05-01: Initial version by oscar.           	     	  v0.0.1          
  * 
  * 
  *
  * Copyright (c) 2025-2025 oscar All rights reserved.
  **********************************************************************
***/
#ifndef __RTC_H
#define __RTC_H	 


#include "stm32f10x.h"

//模块化编程，
//注意在.h文件内通过在定义变量之前添加extern关键字，然后在.c文件中进行赋值，
//而不是在.h文件内初始化赋值
//注意：这里不能给变量赋值
extern uint16_t ryear;
extern uint8_t rmon,rday,rhour,rmin,rsec,rweek;



u8 RTC_Get(void);									//读出当前时间值	
static void RTC_First_Config(void);					//首次启用RTC的设置
void RTC_Config(void);								//实时时钟初始化
u8 Is_Leap_Year(u16 year);							//判断是否是闰年函数                    
u8 RTC_Set(u16 syear,u8 smon,u8 sday,
			u8 hour,u8 min,u8 sec      );	        //写入当前时间
u8 RTC_Get_Week(u16 year,u8 month,u8 day);			//按年月日计算星期




#endif


