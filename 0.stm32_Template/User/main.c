/**
  ******************************************************************************
  * @file    main.c
  * @author  oscar
  * @version v0.2.0
  * 
  * @date    2025-04-30
  * @brief  This file is a template for STM32F10x.
  *          
  *
  * @note    This file is a template for STM32F10x.
  *******************************************************************************
  * @version
  * 2025-05-01: Initial version by oscar.                v0.0.1          
  * 2025-04-28: add usart and i2c driver.                v0.1.0
  * 2025-04-30: add matrix keypad driver.                v0.2.0
  *
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
  */

#include "stm32f10x.h"   
#include "delay.h"
#include "pwm.h"
#include "matrix_keypad.h"
#include "led.h"
#include "sys_config.h"
#include "i2c.h"
#include "oled0561.h"
#include "usart.h"
#include "1602lcd.h"
#include "rtc.h"
#include "timer.h"

uint8_t max_same_char(const volatile  char * s);

//创建一个联合体union
union memmory
{
	uint32_t number;
	uint8_t  a;

};


uint8_t long_int8;
long     long_long;
char a[] = "hello";
uint32_t number =12345678;
uint32_t reverse=0;
char test_string[] = "abbcbbb";

int main(void)
{
	RCC_Configuration();
	Keypad_Init();
	USART1_Init(115200);
	timer3_init();

	while(1)	
	{
		if (1 == timer_flag)
		{
			printf("timer interrupt\n");
			timer_flag = 0;
		}	
	}
}



