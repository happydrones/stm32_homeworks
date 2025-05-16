/**
 * @file encoder.h
 * @author wangshenghui
 * @brief Header file for rotary encoder driver.
 * @version  --0.1   ：create file
 * 		     --0.2   ：add checklock function and long press function
 * 		     --0.3   ：add fast rotation detection （2024-12-29）
 * @date    2024-12-26
 * @brief   Implementation of rotary encoder functionality including 
 *          initialization, read functions, and debounce handling for 
 *          STM32 microcontrollers.
  ******************************************************************************
  * @attention
  * This module provides functions to initialize the GPIO pins connected to a S
  * rotary encoder, read the encoder state (left, right, or button press), and 
  * handle debounce logic and fast rotation detection.
  ******************************************************************************
  */

#ifndef __ENCODER_H
#define __ENCODER_H

#include "sys_config.h"
#include "delay.h"

/** @defgroup Encoder_GPIO_Definitions GPIO Definitions
 * @{
 */
#define ENCODER_RCC     	RCC_APB2Periph_GPIOE /**< RCC clock for encoder GPIO ports */
#define ENCODER_PORT_A		GPIOE	              /**< GPIO port for rotary encoder pins */
#define ENCODER_L	   		GPIO_Pin_6	          /**< GPIO pin for rotary encoder L (Left) */
#define ENCODER_R	     	GPIO_Pin_5	          /**< GPIO pin for rotary encoder R (Right) */
#define ENCODER_PORT_B		GPIOE	              /**< GPIO port for encoder button */
#define ENCODER_button		GPIO_Pin_4	          /**< GPIO pin for encoder button */
#define long_press_threshold	100	              /**< Long press threshold in milliseconds */ 

/** @} */

/** @brief Global variable to store the encoder count. */
extern volatile uint8_t encoder_count;  //fast rotation count detection
extern volatile uint8_t long_press_flag;


void ENCODER_Init(void);

uint8_t ENCODER_READ(void);

#endif
