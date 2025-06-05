/**
  ******************************************************************************
  * @file    	matrix_keypad.h
  * @author  	oscar
  * @version	v0.2.0   EOL: 2025-06-10
  * @date    	2025-05-30
  * @brief   	This file contains the driver  for a 4x4 matrix keypad 
  *******************************************************************************
  * @note    	This file contains  two different methods to scan the keypad:
  *          	1. Interrupt-based method
  *          	2. Polling-based method
  * @version
  * 			2025-05-01: Initial version by oscar.                v0.0.1          
  * 			2025-04-30: using intrrupt for matrix keypad.        v0.2.0
  * @attention
  * 			1.make sure to select only one method to scan the keypad.
  * 				by enable  macro INIT_KEYPAD_GPIO_PINS_WITH_INTRRUPT 
  * 				in matrix_keypad.h file.
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
  */
/*
    
                           COL1     COL2     COL3     COL4   
ROW1     PC0      <——      |⚪|    |⚪|    |⚪|    |⚪|    
        
ROW2     PC1      <——      |⚪|    |⚪|    |⚪|    |⚪|
        
ROW3     PC2      <——      |⚪|    |⚪|    |⚪|    |⚪|

ROW2     PC3      <——      |⚪|    |⚪|    |⚪|    |⚪|
                             |       |        |       |  
                            PC4      PC5     PC6     PC7

*/


#ifndef __matrix_keypad_H
#define __matrix_keypad_H	 

#include "stm32f10x.h"   
/*
 * @attention  :this macro is used to enable or disable the interrupt of the keypad pins.  
*/
#define INIT_KEYPAD_GPIO_PINS_WITH_INTRRUPT   1   

//keypad pins
//set the long press threshold
#define LONG_PRESS_THRESHOLD    (uint8_t)(50) 

#define RCC_Keypad  RCC_APB2Periph_GPIOC 
#define GPIO_Keypad GPIOC
#define ROW_GPIO_PORT            GPIOC 
#define COL_GPIO_PORT            GPIOC
//定义键盘行列引脚
#define ROW1_PIN        GPIO_Pin_0
#define ROW2_PIN        GPIO_Pin_1
#define ROW3_PIN        GPIO_Pin_2
#define ROW4_PIN        GPIO_Pin_3
//行中断扫描配置宏定义
#define ROW_GPIO_PORT_SOURCE   GPIO_PortSourceGPIOC
#define ROW1_PIN_SOURCE        GPIO_PinSource0
#define ROW2_PIN_SOURCE        GPIO_PinSource1
#define ROW3_PIN_SOURCE        GPIO_PinSource2
#define ROW4_PIN_SOURCE        GPIO_PinSource3
#define ROW1_PIN_EXTI_LINE    EXTI_Line0
#define ROW2_PIN_EXTI_LINE    EXTI_Line1
#define ROW3_PIN_EXTI_LINE    EXTI_Line2
#define ROW4_PIN_EXTI_LINE    EXTI_Line3
#define ROW1_PIN_EXTI_IRQN    EXTI0_IRQn
#define ROW2_PIN_EXTI_IRQN    EXTI1_IRQn
#define ROW3_PIN_EXTI_IRQN    EXTI2_IRQn
#define ROW4_PIN_EXTI_IRQN    EXTI3_IRQn


   
//定义键盘列引脚
#define COL1_PIN        GPIO_Pin_4
#define COL2_PIN        GPIO_Pin_5
#define COL3_PIN        GPIO_Pin_6
#define COL4_PIN        GPIO_Pin_7
//列中断扫描配置宏定义
#define COL_GPIO_PORT_SOURCE   GPIO_PortSourceGPIOC
#define COL1_PIN_SOURCE        GPIO_PinSource4
#define COL2_PIN_SOURCE        GPIO_PinSource5
#define COL3_PIN_SOURCE        GPIO_PinSource6
#define COL4_PIN_SOURCE        GPIO_PinSource7
#define COL1_PIN_EXTI_LINE    EXTI_Line4
#define COL2_PIN_EXTI_LINE    EXTI_Line5
#define COL3_PIN_EXTI_LINE    EXTI_Line6
#define COL4_PIN_EXTI_LINE    EXTI_Line7
#define COL1_PIN_EXTI_IRQN    EXTI4_IRQn
#define COL2_PIN_EXTI_IRQN    EXTI9_5_IRQn
#define COL3_PIN_EXTI_IRQN    EXTI9_5_IRQn
#define COL4_PIN_EXTI_IRQN    EXTI9_5_IRQn

extern uint8_t Key_Value;
extern uint8_t interrupt;  //按键值
void Keypad_Init(void);  //矩阵键盘初始化函数);//矩阵键盘扫描 行给 0 初始化
uint8_t Keypad_Scan(void);  //矩阵键盘键值函数
static void Key_NVIC_Config(void);
#endif
