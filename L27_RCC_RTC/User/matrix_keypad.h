/**
  ******************************************************************************
  * @file    matrix_keypad.h
  * @author  oscar
  * @version v0.0.1
  * @date    2025-05-1
  * @brief   该文件是针对STM32F10x的矩阵键盘驱动代码，主要用于初始化键盘GPIO端口
  *          以及扫描键盘按键，判断按键是短按还是长按。
  * 
  ******************************************************************************
  * @details 主要功能包括矩阵键盘的GPIO初始化和按键扫描。
  *          键盘的行配置为推挽输出模式，列配置为上拉输入模式。
  *          通过读取列的状态来判断按键是否被按下，并根据按键按下的持续时间来区分短按和长按。
  * 
  * @changelog
  * ------------v0.0.1   初始化键盘GPIO端口，实现按键扫描功能   2025-05-02
  * 
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
  */
#ifndef __matrix_keypad_H
#define __matrix_keypad_H	 


#include "stm32f10x.h"
#include "delay.h"   
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
