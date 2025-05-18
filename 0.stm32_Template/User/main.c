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
#include  "software_spi_oled.h"

uint16_t cnt;


int main(void)
{
	RCC_Configuration();
	/*
	//初始化一定要等RCC配置完成之后才会生效，
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // 关闭 JTAG，仅保留 SWD（调试仍可用）
	PWM_GPIO_Init();
	//生成50hz的占空比为50hz的方波
	TIM2_PWM_Init(200, 7200);
	*/
	Lcd_1602_Init();
	OLED_Init();
	OLED_ColorTurn(0);
	OLED_DisplayTurn(0);

	while(1)	
	{
		OLED_ShowChinese(8,16,"dfdfffdsf",16);
		

		

	}
}



