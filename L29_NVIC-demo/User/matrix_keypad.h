/**************************************************************************//**
 * @file     key.h
 * @brief    
 * @version  V1.0.0
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
 *
 * @par
 * 
 *
 ******************************************************************************/
#ifndef __matrix_keypad_H
#define __matrix_keypad_H	 


#include "stm32f10x.h"   
//keypad pins
#define LONG_PRESS_THRESHOLD    (uint8_t)(50)  //大于次值定义为长按
#define RCC_Keypad  RCC_APB2Periph_GPIOC 
#define GPIO_Keypad GPIOC
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

void Keypad_Init(void);  //矩阵键盘初始化函数);//矩阵键盘扫描 行给 0 初始化
uint8_t Keypad_Scan(void);  //矩阵键盘键值函数
#endif
