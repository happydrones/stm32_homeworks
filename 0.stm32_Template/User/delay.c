/**
 *******************************************************************************
 * @file    delay.c
 * @author  Oscar
 * @version V1.0.0  EOL: 2025-06-10
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

/* Includes ------------------------------------------------------------------*/
#include "delay.h"


/**
 * @brief  Delay function in microseconds
 * @param  nCount  The number of loop  delay time
 * @retval None
 */
void Delay_us(u16 nCount)
{
	uint16_t loop;  ///< Variable to control the number of loops
    for(loop =0;loop<nCount; loop++)
	{
        for (uint8_t i = 0; i < 5; i++)  ///< Inner empty loop to control the delay time
        loop++;  ///< Increment the loop counter
    };  ///< Loop until the specified delay time is reached
}

/**
 * @brief  Delay function for 10 microseconds
 * @param  nCount  The number of loop iterations to control the delay time
 * @retval None
 */
void Delay_10us(u16 nCount)
{
    uint16_t loop;  
    for(loop =0;loop<nCount;loop++)
	{
        for (uint8_t i = 0; i < 95; i++)  
        loop++;  
    }  
}

/**
 * @brief Delay function in milliseconds
 * @param  nCount  The number of loops to control the delay time in milliseconds
 * @retval None
 */
void Delay_ms(u16 nCount)
{
    for (u16 j = 0; j < nCount; j++)  
    {    
        for (u16 i = 0; i < 7995; i++);  
    } 
}

/**
 * @brief Delay function in seconds
 * @param  nCount  The number of loops to control the delay time in seconds
 * @retval None
 */
void Delay_s(u16 nCount)
{
    for (u32 j = 0; j < nCount; j++)
    {    
        for (u32 i = 0; i < 6605000; i++);  
    } 
}



/**
 * @brief  Delay function in microseconds, using SysTick timer
 * @param  X_us uint is the microseconds，from 0 to 2^24-1
 * @retval None
 */
void Systick_delay_us(uint32_t X_us)
{
	SysTick->LOAD = 72 * X_us - 1; 
    // 清除SysTick定时器的当前值寄存器
    SysTick->VAL = 0x00;    
    // 启动SysTick定时器，使用内部时钟，不中断
    SysTick->CTRL = 0x05;      
    // 等待定时器计数结束标志被置位
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL = 0x00000004; /**< 关闭定时器 */
}
/**
 * @brief  Delay function in 10 microseconds, using SysTick timer
 * @param  X_us uint is the microseconds，from 0 to 2^24-1
 * @retval None
 */
void Systick_delay_10us(uint32_t X_us)
{
	SysTick->LOAD = 720 * X_us - 1; 
    SysTick->VAL  = 0x00;     
    SysTick->CTRL = 0x05;    
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL = 0x00000004; 
}

/**
 * @brief  Delay function in milliseconds, using SysTick timer
 * @param  X_ms uint is the milliseconds，from 0 to 2^24-1
 * @retval None
 */
void Systick_delay_ms(uint32_t X_ms)
{
    SysTick->CTRL = 0x05;           
    SysTick->LOAD = 72000 * X_ms - 1; 
    SysTick->VAL = 0x00;   
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL = 0x00000004; 
}

