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
#include "stdlib.h"

#define length 3
uint16_t cnt;
uint8_t  pwm=30;
uint8_t  get_keypad_value;
uint16_t current_speed;
uint8_t  list[length];
uint8_t  e =0;
uint16_t p = 2;



int main(void)
{
	RCC_Configuration();
    Oled0561_Init();
	W25Q_Init();
	Keypad_Init();
    uint32_t jedec_id = W25Q_Read_JEDEC_ID();
    Oled_Display_String_6X8(0,0,(u8 *)"JEDEC ID: ");
	Oled_Display_String_6X8(1,5,(u8 *)"JEDEC ID: ");
    Oled_display_number(2,0,jedec_id,FONT_SIZE_6x8);
    srand(1234);

    for (uint16_t i = 0; i < length; i++)
    {
        list[i] = rand()%256;
    }
    for (uint16_t i = 0; i < length; i++)
    {
        Oled_display_number(4,4*i,list[i],FONT_SIZE_6x8);
        Delay_ms(1000);
    }
    
//    e =list[p];
//    for (uint16_t i =p; i < length; i++)
//    {
//        if (i ==length-1)
//        {
//            list[i] =0;
//        }
//        else
//        {
//            list[i] = list[i+1];
//        }
//        
//    }
//    for (uint16_t i = 0; i < length; i++)
//    {
//        
//        Oled_display_integer(4,i,list[i]);
//        Delay_ms(1000);
//    }
    


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


