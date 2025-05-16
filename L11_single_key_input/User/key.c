/**************************************************************************//**
* @file     key.c
* @brief    4x4 Matrix Keypad Driver for STM32 Microcontrollers
* @version  V1.00
* @date     19. October 2024
*
* @note
* Copyright (C) 2009 ARM Limited. All rights reserved.
* @note
* This file contains functions for initializing and scanning a 4x4 matrix
* keypad connected to GPIO pins of an STM32 microcontroller. The keys can
* be scanned to detect key presses, and the corresponding GPIO configurations
* are set up for both input and output operations.
* @par
* This driver is designed to work with multiple GPIO ports (A, B, C, D, E, F, G)
* to support flexibility in wiring the keypad to different pins of the MCU.
* It also includes debounce logic with delays and can toggle an LED as feedback
* when a key is pressed.
* @par
* ARM Limited (ARM) is supplying this software for use with Cortex-M 
* processor based microcontrollers.  This file can be freely distributed 
* within development tools that are supporting such ARM based processors. 
*
* @par
* THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
* ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
******************************************************************************/



#include "key.h"
#include "delay.h"
#include "led.h"

struct key_struct up_key = {GPIOC, GPIO_Pin_0,0};
struct key_struct down_key = {GPIOC, GPIO_Pin_2,0};
struct key_struct left_key = {GPIOC, GPIO_Pin_1,0};
struct key_struct right_key = {GPIOC, GPIO_Pin_3,0};
struct key_struct common_Pin = {GPIOC, GPIO_Pin_7,0};

void Common_Pin_Init(struct key_struct* Key)
{
    GPIO_InitTypeDef GPIO_key_InitStructure;
    GPIO_key_InitStructure.GPIO_Pin = Key->GPIO_Pin;
    GPIO_key_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_Init(GPIOC, &GPIO_key_InitStructure);
    GPIO_ResetBits(Key->GPIO_Group, Key->GPIO_Pin);
}

void Key_Init(struct key_struct* Key)
{
    GPIO_InitTypeDef GPIO_key_InitStructure;
    GPIO_key_InitStructure.GPIO_Pin = Key->GPIO_Pin;
    GPIO_key_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(KEY_GPIO_RCC, ENABLE);
	GPIO_Init(GPIOC, &GPIO_key_InitStructure);
    
}


//void Key_Independent_Value(void)
//{
//	if()
//}




/*
 * @ brief 按键检测函数
 * @ param Key 按键结构体
 * @ return 按键状态，0：未按下，1：按下
 */
void Key_Scan(struct key_struct* Key)
{
	if((GPIO_ReadInputDataBit(Key->GPIO_Group, Key->GPIO_Pin))==0)
	{
        delay_ms(15);
        if((GPIO_ReadInputDataBit(Key->GPIO_Group, Key->GPIO_Pin))==0)
        {
            Key->key_flag =1;
//            LED_Toggle( GPIOA, GPIO_Pin_0);
        }
		else
		{
			Key->key_flag =0;
			
		}

	}

}
