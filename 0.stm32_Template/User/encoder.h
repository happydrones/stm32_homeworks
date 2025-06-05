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

#include "stm32f10x.h"
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

/** @defgroup Encoder_EXTI_Definitions 
 * @{
 */
//Encoder button EXTI line and interrupt
#define ENCODER_BUTTON_EXTI_GPIO_PORT  	      GPIOE
#define ENCODER_BUTTON_EXTI_GPIO_RCC  		  RCC_APB2Periph_GPIOE 
#define ENCODER_BUTTON_GPIO_PORTSOURCE        GPIO_PortSourceGPIOE
#define ENCODER_BUTTON_EXTI_GPIO_PIN   		  GPIO_Pin_4
#define ENCODER_BUTTON_EXTI_LINE          	  EXTI_Line4
#define ENCODER_BUTTON_GPIO_PINSOURCE         GPIO_PinSource4
#define ENCODER_BUTTON_EXTI_IRQN  			  EXTI4_IRQn
//Encoder A  EXTI line and interrupt
#define ENCODER_A_EXTI_GPIO_PORT  	          GPIOE
#define ENCODER_A_EXTI_GPIO_RCC  		      RCC_APB2Periph_GPIOE 
#define ENCODER_A_GPIO_PORTSOURCE             GPIO_PortSourceGPIOE
#define ENCODER_A_EXTI_GPIO_PIN   		      GPIO_Pin_5
#define ENCODER_A_EXTI_LINE          	      EXTI_Line5
#define ENCODER_A_GPIO_PINSOURCE              GPIO_PinSource5
#define ENCODER_A_EXTI_IRQN  			      EXTI9_5_IRQn
//Encoder B  EXTI line and interrupt
#define ENCODER_B_EXTI_GPIO_RCC  	          RCC_APB2Periph_GPIOE
#define ENCODER_B_EXTI_GPIO_PORT  	          GPIOE
#define ENCODER_B_GPIO_PORTSOURCE	          GPIO_PortSourceGPIOE
#define ENCODER_B_EXTI_GPIO_PIN   	          GPIO_Pin_6
#define ENCODER_B_EXTI_LINE                   EXTI_Line6
#define ENCODER_B_GPIO_PINSOURCE		      GPIO_PinSource6
#define ENCODER_B_EXTI_IRQN 			      EXTI9_5_IRQn
/** 
 * @} 
*/



/** @brief Global variable to store the encoder count. */
extern volatile uint8_t encoder_count;  //fast rotation count detection
extern volatile uint8_t long_press_flag;

/** @defgroup Encoder_Function_Prototypes Function Prototypes
 * @{
 */
void Encoder_GPIO_Init(void);
//todo: add encoder button interrupt function
void Encoder_EXIT_Init(void); 
uint8_t ENCODER_READ(void);
/** @} */
#endif
