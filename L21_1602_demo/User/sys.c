 /**
  ******************************************************************************
  * @file    sys.c
  * @author  oscar
  * @version V0.0.1
  * @date    
  * @brief   
  * 
  * 1.
  *
  *    
  *        
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#include "sys.h"
/**
 * @brief  Configures the Nested Vectored Interrupt Controller (NVIC).
 * @param  None
 * @retval None
 * @note   This function configures the NVIC interrupt priority grouping to group 2:
 *         2 bits for preemption priority and 2 bits for subpriority.
 */
void NVIC_Configuration(void) 
{  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // Set NVIC interrupt priority grouping to 2: 2 bits for preemption, 2 bits for subpriority
}

/**
 * @brief  Configures the system clock (RCC).
 * @param  None
 * @retval None
 * @note   This function initializes the system clock to use an external high-speed oscillator (HSE) 
 *         with PLL multiplier for a system clock of 72 MHz, configures AHB and APB clocks, and 
 *         enables prefetch buffer and flash latency based on the system frequency.
 * @attention It also enables the necessary peripheral clocks, such as USART and GPIO peripherals.
 */
void RCC_Configuration(void) 
{  
    ErrorStatus HSEStartUpStatus;   
    RCC_DeInit();  /* Reset RCC system registers for debugging purposes */
    RCC_HSEConfig(RCC_HSE_ON);  /* Enable HSE (High-Speed External oscillator) */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();  /* Wait for HSE to stabilize */
    
    if (HSEStartUpStatus == SUCCESS) 
	{   
        /* Configure PLL: use HSE as PLL source, multiply by 9 (72 MHz system clock) */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  
        RCC_HCLKConfig(RCC_SYSCLK_Div1);  /* Set AHB clock (HCLK) to SYSCLK */
        
        /* Set APB1 (PCLK1) and APB2 (PCLK2) clock dividers */
        RCC_PCLK1Config(RCC_HCLK_Div2);  /* APB1 clock = HCLK/2 = 36 MHz */
        RCC_PCLK2Config(RCC_HCLK_Div1);  /* APB2 clock = HCLK = 72 MHz */
        /* Set Flash latency for 72 MHz system clock and enable prefetch buffer */
        FLASH_SetLatency(FLASH_Latency_2);  
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  
        RCC_PLLCmd(ENABLE);  /* Enable PLL */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);  /* Wait for PLL to stabilize */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /* Switch system clock to PLL */
        while (RCC_GetSYSCLKSource() != 0x08);  /* Wait for PLL to be used as SYSCLK */
    }  

    /* Enable peripheral clocks for required devices */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
                           RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  // Enable APB1 peripherals
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);   
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   
}

