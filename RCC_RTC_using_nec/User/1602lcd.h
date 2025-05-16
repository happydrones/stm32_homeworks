/**
  ******************************************************************************
  * @file    main.c
  * @author  oscar
  * @version v0.0.1
  * @date    2025-05-1
  * @brief  此文件包含1602 LCD显示屏的硬件配置和驱动函数声明
  *          
  *
  
  *******************************************************************************
 * @details 此驱动程序用于STM32系列微控制器，通过位带操作和GPIO输出驱动1602 LCD显示屏。
  * @changelog
  * ------------v0.0.1   定义了1602LCD显示屏的GPIO配置及相关操作函数。   2025-05-02
  *
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
  */
#ifndef __1602LCD_H__
#define __1602LCD_H__

#include "sys_config.h" 

#define Lcd_1602_GPIO_RCC     RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG   //定义IO 时钟
////位带方式驱动
#define RS_Lcd_1602  PFout(9)
#define RW_Lcd_1602  PFout(10)
#define E_Lcd_1602   PBout(1)
//GPIO输出驱动方式 
//#define RS_Lcd_1602(n)     GPIO_WriteBit(RS_Lcd_1602_GPIOPORT,RS_Lcd_1602_Pin,(BitAction)(n));  //n  0 或 1  
//#define RW_Lcd_1602(n)        GPIO_WriteBit(RW_Lcd_1602_GPIOPORT,RW_Lcd_1602_Pin ,(BitAction)(n));  //n  0 或 1  
//#define E_Lcd_1602(n)        GPIO_WriteBit(E_Lcd_1602_GPIOPORT,E_Lcd_1602_Pin,(BitAction)(n));  //n  0 或 1  

#define RS_Lcd_1602_GPIOPORT  GPIOF
#define RS_Lcd_1602_Pin       GPIO_Pin_9

#define RW_Lcd_1602_GPIOPORT  GPIOF
#define RW_Lcd_1602_Pin       GPIO_Pin_10

#define E_Lcd_1602_GPIOPORT   GPIOB
#define E_Lcd_1602_Pin        GPIO_Pin_1

#define LCD_1602_Data_Bus_GPIOPORT  GPIOG   
#define LCD_1602_Data_Bus_Pin       GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7

void Lcd_1602_GPIO_Config(void);
void LCD1602_IsBusy(void);  //1602液晶屏判忙函数
void Write_Data_Lcd_1602(u8 Data_Dat);//1602液晶屏写数据函数
void Write_Order_Lcd_1602(u8 Order_Dat);//1602液晶屏写指令函数
void Lcd_1602_Init(void);  //1602液晶屏初始化函数
void Display_Lcd_1602(u8 X_1602,u8 Y_1602,u8 *P_1602,u8 Count_1602);//1602任意位置写字符串
void Display_Lcd_1602_Number(u8 X_1602,u8 Y_1602,u32 Number,u8 Count_1602);//1602任意位置写字十进制数
void Display_Time_LCD1602(u8 X_1602, u8 Y_1602, u8 Hours, u8 Minutes, u8 Seconds);
/***********************************************************************/

#endif
