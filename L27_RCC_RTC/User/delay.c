/**
 * @file delay.c
 * @brief This file implements various delay functions for precise time control, supporting microseconds, milliseconds, and seconds.
 * 
 * This file provides four delay functions: delay_us for microseconds, delay_10us for 10-microsecond delays, delay_ms for milliseconds, 
 * and delay_s for seconds. These functions use loops to generate delay, which can be used in embedded systems like STM32.
 * @note
 * us延时很不准确偏差很大
 */
#include "delay.h"


/**
 * @brief Delay function in microseconds
 * @param  nCount  The number of loop iterations to control the delay time
 * @retval None
 * 
 * This function generates a delay by looping. nCount represents the number of loops, and each loop consumes a specific amount of time.
 */
void Delay_us(u16 nCount)
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
void Delay_10us(u16 nCount)
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
void Delay_ms(u16 nCount)
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
void Delay_s(u16 nCount)
{
    for (u32 j = 0; j < nCount; j++)  ///< Outer loop controls the number of seconds
    {    
        for (u32 i = 0; i < 6605000; i++);  ///< Inner loop controls the delay for each second
    } 
}



/**
 * @brief  微秒级延时函数，基于SysTick定时器
 * 
 * 该函数使用SysTick定时器进行延时，延时的单位是微秒。它通过配置SysTick定时器的LOAD寄存器来实现延时。
 * 延时期间SysTick定时器在指定时间到达时会自动设置COUNTFLAG标志位，通过轮询该标志位来实现等待。
 * 
 * @param  X_us 延时的微秒数，范围为0到2^24-1（大约16.7秒）
 * @retval None
 */
void Systick_delay_us(uint32_t X_us)
{
	SysTick->LOAD = 72 * X_us - 1; /**< 设置加载值，定时器计数值为系统时钟频率 * 延时的微秒数 - 1 */
    SysTick->VAL = 0x00;     /**< 清除当前计数值 */
    SysTick->CTRL = 0x05;    /**< 使能SysTick定时器，选择AHB时钟源，禁用中断 */ 
    // 等待计时完成，当COUNTFLAG标志位为1时退出
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    
    SysTick->CTRL = 0x00000004; /**< 关闭定时器 */
}
void Systick_delay_10us(uint32_t X_us)
{
	SysTick->LOAD = 720 * X_us - 1; /**< 设置加载值，定时器计数值为系统时钟频率 * 延时的微秒数 - 1 */
    SysTick->VAL = 0x00;     /**< 清除当前计数值 */
    SysTick->CTRL = 0x05;    /**< 使能SysTick定时器，选择AHB时钟源，禁用中断 */ 
    // 等待计时完成，当COUNTFLAG标志位为1时退出
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    
    SysTick->CTRL = 0x00000004; /**< 关闭定时器 */
}

/**
 * @brief  毫秒级延时函数，基于SysTick定时器
 * 
 * 该函数使用SysTick定时器进行延时，延时的单位是毫秒。它通过配置SysTick定时器的LOAD寄存器来实现延时。
 * 延时期间SysTick定时器在指定时间到达时会自动设置COUNTFLAG标志位，通过轮询该标志位来实现等待。
 * 
 * @param  X_ms 延时的毫秒数，范围为0到2^24-1（大约16.7秒）
 * @retval None
 */
void Systick_delay_ms(uint32_t X_ms)
{
    SysTick->CTRL = 0x05;    /**< 使能SysTick定时器，选择AHB时钟源，禁用中断 */
    SysTick->LOAD = 72000 * X_ms - 1; /**< 设置加载值，定时器计数值为72,000 * 延时的毫秒数 - 1 (假设系统时钟频率为72MHz) */
    SysTick->VAL = 0x00;     /**< 清除当前计数值 */
    
    // 等待计时完成，当COUNTFLAG标志位为1时退出
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    
    SysTick->CTRL = 0x00000004; /**< 关闭定时器 */
}

