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

uint8_t max_same_char(const volatile  char * s);
typedef struct student
{
	char name[128];
	const int *p;
	int ID;
	
}student_t;


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
	USART1_Init(9600);
	while(1)	
	{
		if(1 ==get_string_flag)
		{
			if(1 == rx_flag)
			{
				printf("first_time :%s\n",rx_buf);
				printf("the max_repeat_list:%d\n",max_same_char(rx_buf));
				get_string_flag =0;
				printf("second_time:%x\n",(rx_buf));
				printf("second_time:%x\n",(rx_buf+rx_index));
				rx_flag =0;
			}
		}

	}
}


uint8_t max_same_char( const volatile  char * s)
{
	uint8_t same_char_count = 0;
	uint8_t count = 0;
	char prev_char = *s;
	while('\0' !=*s )
	{
		if(prev_char ==*(s))
		{
			count++;
			if(count>same_char_count)
			{
				same_char_count = count;
			}
		}
		else
		{
			prev_char =*(s);
			count =1;
		}
		s++;
		
	}
	return same_char_count;
}

