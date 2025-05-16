/**************************************************************************//**
 * @file     key.h
 * @brief    CMSIS Cortex-M3 Core Peripheral Access Layer Header File
 * @version  V1.30
 * @date     30. October 2009
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

#ifndef __KEY_H__
#define __KEY_H__


#include "stm32f10x.h"  
#define KEYPAD_GPIO_PORT         GPIOC
#define KEY_GPIO_RCC    RCC_APB2Periph_GPIOC 

struct key_struct
{
    GPIO_TypeDef* GPIO_Group;
    uint16_t GPIO_Pin;
    uint8_t key_flag;
};
extern struct key_struct up_key    ;
extern struct key_struct down_key  ;
extern struct key_struct left_key  ;
extern struct key_struct right_key ;
extern struct key_struct common_Pin;


void Common_Pin_Init(struct key_struct* Key);
void Key_Init(struct key_struct* Key);
void Key_Scan(struct key_struct* Key);



#endif 
