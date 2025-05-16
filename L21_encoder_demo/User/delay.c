/**
 * @file delay.c
 * @brief This file implements various delay functions for precise time control, supporting microseconds, milliseconds, and seconds.
 * 
 * This file provides four delay functions: delay_us for microseconds, delay_10us for 10-microsecond delays, delay_ms for milliseconds, 
 * and delay_s for seconds. These functions use loops to generate delay, which can be used in embedded systems like STM32.
 */
#include "delay.h"


/**
 * @brief Delay function in microseconds
 * @param  nCount  The number of loop iterations to control the delay time
 * @retval None
 * 
 * This function generates a delay by looping. nCount represents the number of loops, and each loop consumes a specific amount of time.
 */
void delay_us(u16 nCount)
{
	uint16_t loop;  ///< Variable to control the number of loops
    for(loop =0;loop<nCount; loop++)
	{
        for (uint8_t i = 0; i < 5; i++)  ///< Inner empty loop to control the delay time
        {
        }
        loop++;  ///< Increment the loop counter
    };  ///< Loop until the specified delay time is reached
}

/**
 * @brief Delay function for 10 microseconds
 * @param  nCount  The number of loop iterations to control the delay time
 * @retval None
 * 
 * This function generates a 10-microsecond delay by looping. nCount represents the number of loops for the delay.
 */
void delay_10us(u16 nCount)
{
    uint16_t loop;  ///< Variable to control the number of loops
    for(loop =0;loop<nCount;loop++)
	{
        for (uint8_t i = 0; i < 95; i++)  ///< Inner empty loop to control the 10-microsecond delay
        loop++;  ///< Increment the loop counter
    }  ///< Loop until the specified delay time is reached
}

/**
 * @brief Delay function in milliseconds
 * @param  nCount  The number of loops to control the delay time in milliseconds
 * @retval None
 * 
 * This function generates a millisecond delay by looping. nCount represents the number of milliseconds for the delay.
 */
void delay_ms(u16 nCount)
{
    for (u16 j = 0; j < nCount; j++)  ///< Outer loop controls the number of milliseconds
    {    
        for (u16 i = 0; i < 7995; i++);  ///< Inner loop controls the delay for each millisecond
    } 
}

/**
 * @brief Delay function in seconds
 * @param  nCount  The number of loops to control the delay time in seconds
 * @retval None
 * 
 * This function generates a second-level delay by looping. nCount represents the number of seconds for the delay.
 */
void delay_s(u16 nCount)
{
    for (u32 j = 0; j < nCount; j++)  ///< Outer loop controls the number of seconds
    {    
        for (u32 i = 0; i < 6605000; i++);  ///< Inner loop controls the delay for each second
    } 
}


void Systick_delay_us(uint32_t X_us)
{
	SysTick->CTRL = 0x05; //时钟源选择AHB，siable中断，打开定时器
	SysTick->LOAD =RCC_SysTclk*X_us;
	SysTick->VAL =0x00;
	while(!(SysTick->CTRL&0x00010000));
	SysTick->CTRL = 0x000000004;     //关闭计时器
	
	
}
