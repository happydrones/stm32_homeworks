/**
  ******************************************************************************
  * @file    usart.h
  * @author  oscar
  * @version v0.0.1
  * 
  * @date    2025-04-28
  * @brief   This file provides all the functions prototypes for usart driver.
  *          
  *
  * @note    this file is only used for stm32f10x.
  *******************************************************************************
  * @version
  * 2025-05-01: Initial version by oscar.                v0.0.1          
  * 
  * 
  *
  * Copyright (c) 2025-2025 oscar All rights reserved. happydrones@gmail.com
  ******************************************************************************
  */
#ifndef		__USART_H
#define		__USART_H


#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"	
#include "sys_config.h" 


#define USART_n		USART1  //定义使用printf函数的串口，其他串口要使用USART_printf专用函数发送

#define USART1_RX_BUF_LEN  	  200  	//Define the maximum number of bytes received by USART1
#define USART2_RX_BUF_LEN  	  200  	//Define the maximum number of bytes received by USART2
#define USART3_RX_BUF_LEN  	  200  	//Define the maximum number of bytes received by USART3
#define USART4_RX_BUF_LEN  		200  	//Define the maximum number of bytes received by USART4
#define USART5_RX_BUF_LEN  		200  	//Define the maximum number of bytes received by USART5

//不使用某个串口时要禁止此串口，以减少编译量
#define EN_USART1 			1		//Enable（1）/Disable（0）USART1
#define EN_USART2 			0		//Enable（1）/Disable（0）USART2
#define EN_USART3 			0		//Enable（1）/Disable（0）USART3

/******  STM32 specific UART **********************************/
#ifdef STM32F10X_HD
  #define EN_USART4 			1		//Enable（1）/Disable（0）USART4
  #define EN_USART5 			0		//Enable（1）/Disable（0）USART5

#endif /* STM32F10X_HD */

	  	
extern u8  USART1_RX_BUF[USART1_RX_BUF_LEN]; //接收缓冲,最大USART1_RX_BUF_LEN个字节.末字节为换行符 
extern u8  USART2_RX_BUF[USART2_RX_BUF_LEN]; //接收缓冲,最大USART2_RX_BUF_LEN个字节.末字节为换行符
extern u8  USART3_RX_BUF[USART3_RX_BUF_LEN]; //接收缓冲,最大USART3_RX_BUF_LEN个字节.末字节为换行符
 
extern u16 USART1_RX_STA;         		//接收状态标记	
extern u16 USART2_RX_STA;         		//接收状态标记	
extern u16 USART3_RX_STA;         		//接收状态标记
#define BUF_LEN 32
extern volatile char 	rx_buf[BUF_LEN];
extern volatile uint8_t rx_flag;
extern volatile uint8_t rx_index ;        // 当前索引
extern uint8_t  		get_string_flag ;        // 当前索引


void USART1_Init(u32 bound);//USART1 Initialization and startup
void USART2_Init(u32 bound);//USART2 Initialization and startup
void USART3_Init(u32 bound);//USART3 Initialization and startup

void USART1_printf(char* fmt,...); //USART1专用printf函数
void USART2_printf(char* fmt,...); //USART2专用printf函数
void USART3_printf(char* fmt,...); //USART3专用printf函数




#endif
