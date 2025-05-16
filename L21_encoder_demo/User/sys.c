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

/*********************************************************************
*函数名称：PC_PA_13_14_15_Gpio
*函数功能：设置 PA 13 14 15   PC 13 14 15 为io功能
*函数调用：PC_PA_13_14_15_Gpio();
*参数列表：无
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/

void PC_PA_13_14_15_Gpio(void) //设置 PA 13 14 15   PC 13 14 15 io功能
{
	//rtc作为io，需要先取消rtc备用纽扣电池配置好后再装电池或不装
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE );
	//RCC_APB2Periph_AFIO IO功能复用AFIO 时钟 改变默认功能 恢复IO口功能
    PWR_BackupAccessCmd( ENABLE );/* 允许修改RTC和后备寄存器*/
    RCC_LSEConfig( RCC_LSE_OFF ); /* 关闭外部低速时钟,PC14+PC15可以用作普通IO*/
    BKP_TamperPinCmd(DISABLE);  /* 关闭入侵检测功能,PC13可以用作普通IO*/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //恢复PA13  PA14  PA15 IO功能，默认位jtag swd下载功能
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    PWR_BackupAccessCmd(DISABLE);/* 禁止修改RTC和后备寄存器*/
    //BKP_ITConfig(DISABLE);       /* 禁止TAMPER 中断*/
}
