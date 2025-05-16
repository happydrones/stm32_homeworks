/**************************************************************************//**
 * @file     keypad.h
 * @brief    
 * @version  V1.00
 * @date     30. October 2024
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

#ifndef __KEYPAD_H__
#define __KEYPAD_H__


#include "stm32f10x.h"  
#include "led.h"
//keypad pins
#define LONG_PRESS_THRESHOLD    (uint8_t)(50)
#define KEYPAD_GPIO_CLK    RCC_APB2Periph_GPIOC 
#define ROW_GPIO_PORT            GPIOC
#define COL_GPIO_PORT            GPIOC
//定义键盘行列引脚
#define ROW1_PIN        GPIO_Pin_0
#define ROW2_PIN        GPIO_Pin_1
#define ROW3_PIN        GPIO_Pin_2
#define ROW4_PIN        GPIO_Pin_3
//定义键盘列引脚
#define COL1_PIN        GPIO_Pin_4
#define COL2_PIN        GPIO_Pin_5
#define COL3_PIN        GPIO_Pin_6
#define COL4_PIN        GPIO_Pin_7

extern uint8_t Long_press_flag;
extern uint8_t Is_Pre_mode_long;

struct key_struct
{
    GPIO_TypeDef* GPIO_Group;
    uint16_t GPIO_Pin;
    uint8_t key_flag;
};

void Keypad_Init(void);
void Common_Pin_Init(struct key_struct* Key);
void Key_Init(struct key_struct* Key);
void Key_Scan(struct key_struct* Key);
uint8_t Keypad_Scan(void);
uint8_t test_static_key_word(uint8_t Flag);
#endif 
