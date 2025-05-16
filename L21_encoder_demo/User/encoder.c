/**
  ******************************************************************************
  * @file    encoder.c
  * @author  Wang Shenghui
  * @version  --0.1   ：create file
  * 		  --0.2   ：add checklock function and long press function
  * 		  --0.3   ：add fast rotation detection （2024-12-29）
  * @date    2024-12-26
  * @brief   Implementation of rotary encoder functionality including 
  *          initialization, read functions, and debounce handling for 
  *          STM32 microcontrollers.
  ******************************************************************************
  * @attention
  * This module provides functions to initialize the GPIO pins connected to a 
  * rotary encoder, read the encoder state (left, right, or button press), and 
  * handle debounce logic and fast rotation detection.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/** 
 * @brief Global variable to track encoder rotation count. 
 */
volatile uint8_t encoder_count = 0;
volatile uint8_t long_press_flag  = 0;

/** 
 * @brief Flag to indicate if the encoder is locked (1 = locked). 
 */
u8 KUP =1;

/** 
 * @brief Counter for encoder lock wait time. 
 */
u16 cou;

/**
 * @brief Initializes the GPIO pins used for the rotary encoder and its button.
 *
 * Configures the GPIO pins connected to the rotary encoder channels (A and B) 
 * and the button as input with pull-up resistors.
 */
void ENCODER_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable the clock for the GPIO port used by the encoder
    RCC_APB2PeriphClockCmd(ENCODER_RCC, ENABLE);

    // Configure GPIO pins for encoder channels A and B as input pull-up
    GPIO_InitStructure.GPIO_Pin = ENCODER_L | ENCODER_R;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ENCODER_PORT_A, &GPIO_InitStructure);

    // Configure GPIO pin for encoder button as input pull-up
    GPIO_InitStructure.GPIO_Pin = ENCODER_button;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ENCODER_PORT_B, &GPIO_InitStructure);
}

/**
 * @brief Reads the state of the rotary encoder and button.
 *
 * This function detects left or right rotation and button press events. It handles debounce logic
 * and fast rotation detection using internal counters.
 *
 * @return A value indicating the encoder state:
 *         - 0: No action
 *         - 1: Left rotation
 *         - 2: Right rotation
 *         - 3: Button press
 *         - long_press_flag = 1: Long press
 */
u8 ENCODER_READ(void) {
    encoder_count = 0;  //fast rotation detection counter
    u8 key_value;   // Variable to store the detected key value
    u8 direction_flag;   // Variable to store the detected direction
    u16 fast_rotate_flag = 0; // Fast rotation detection flag
	uint16_t long_press_value =0;
    // Check if the encoder is not locked
    if (GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L) && GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_R)) {
        KUP = 0;
    }
	
    // Detect rotation
    if ((GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L) == 0) && KUP == 0)
	{
        direction_flag = GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_R);

		if (direction_flag == 0) {
			key_value = 1; // Left rotation
			encoder_count += 1;
			fast_rotate_flag = 15000;
		} else {
			key_value = 2; // Right rotation
			encoder_count += 1;
			fast_rotate_flag = 15000;
		}

		// Wait for the encoder to be released
		cou = 0;
		while (!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L) && cou < 600) {
			cou++;
			KUP = 1;
			delay_us(10);
		}
	}

	// Fast left rotation detection
	while ((key_value == 1) && (fast_rotate_flag > 1)) {
		if (GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)==1) {
			while (GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)!=0);

			if (!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)) {
				encoder_count += 1;
				fast_rotate_flag = 15000;
			}
		}
		fast_rotate_flag--;
		
	}

	// Fast right rotation detection
	while ((key_value == 2) && (fast_rotate_flag > 1)) {
		if (GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L) == 1) {
			while (GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L) != 1);

			if (!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_L)) {
				encoder_count += 1;
				fast_rotate_flag = 15000;
			}
		}
		fast_rotate_flag--;
	}
    // Detect button press
    if (!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_button) && KUP == 0) {
        delay_ms(15); // Debounce delay
        if (!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_button)) {
            key_value = 3; // Button press
			while ((!GPIO_ReadInputDataBit(ENCODER_PORT_A, ENCODER_button)) && (long_press_value < long_press_threshold))
			{
				long_press_value++;
				delay_ms(10);
			}
			
        }
    }
	// Long press detection and flag setting
	if(long_press_value>=long_press_threshold)
	{
		long_press_flag = 1;
		long_press_value =0;
	}
    return key_value;
}

/**
 * @brief GPIO mode configurations available for STM32.
 *
 * - GPIO_Mode_AIN: Analog input
 * - GPIO_Mode_IN_FLOATING: Floating input
 * - GPIO_Mode_IPD: Input with pull-down resistor
 * - GPIO_Mode_IPU: Input with pull-up resistor
 * - GPIO_Mode_Out_PP: Push-pull output
 * - GPIO_Mode_Out_OD: Open-drain output
 * - GPIO_Mode_AF_PP: Alternate function push-pull output
 * - GPIO_Mode_AF_OD: Alternate function open-drain output
 */
