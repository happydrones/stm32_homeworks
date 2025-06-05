/**
 *******************************************************************************
 * @file    delay.h
 * @author  Oscar
 * @version V1.0.0  \
 * EOL: 2025-06-10
 * @date    2025-05-1
 * @brief   This file provides blocking delay functions for stm32f10x devices
 *          supporting microseconds(us),10 microseconds(10us), milliseconds(ms),
 *          and seconds(s).
 ******************************************************************************
 * @note    The file contains two kinds of blocking delay implementations:
 *          1. Loop-based delay functions
 *          2. SysTick-based delay functions
 * @attention 
 *         1. The loop-based delay functions are suitable for small delays, 
 *         2. in order to achieve high precision and accuracy,
 *            make sure the system clock is setted at 72MHz.
 *<h2><center>&copy; COPYRIGHT 2025 Oscar happydrones123@gmail.com </center></h2>
 *******************************************************************************
 */

#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32f10x.h" 
#define RCC_SysTclk 72

void Delay_us(u16 nCount);
void Delay_ms(u16 nCount);
void Delay_s(u16 nCount);
void Delay_10us(u16 nCount);
void Systick_delay_us(uint32_t X_us);
void Systick_delay_ms(uint32_t X_ms);
void Systick_delay_10us(uint32_t X_us);

#endif

