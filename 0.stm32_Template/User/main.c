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
#include "adc.h"
#include "encoder.h"
#include "w25q128.h"

uint16_t cnt;
uint8_t  pwm=30;
uint8_t  get_keypad_value;
uint16_t current_speed;

int main(void)
{
	RCC_Configuration();
    OLED0561_Init();
    USART1_Init(115200);
	W25Q_Init();
	Keypad_Init();
    uint32_t jedec_id = W25Q_Read_JEDEC_ID();
    OLED_DISPLAY_8x16(0,"JEDEC ID: ",8);
    OLED_DISPLAY_8x16(0,jedec_id,8);
	while(1)	
	{
		get_keypad_value = Key_Value;
		Key_Value = 0;

	}
}




float get_speed(uint16_t ic_rise, uint16_t ic_fall)
{
    float speed;
    //首先末次计数时间脉冲值-初始计数时间脉冲值，即可获得旋转n个脉冲所需的时间
    // 然后n个脉冲对应rad =n * 分度数 
    // 轮胎所走的距离是  rad * 2 * π * 轮胎半径
    // 速度v = 距离/时间 = 2 * π * 轮胎半径 * n * 分度数 / (ccR脉冲数*脉冲周期)
    // 单位：m/s
    speed = (ic_rise - ic_fall) * 1000.0 / 20.0;
	return speed;
}
