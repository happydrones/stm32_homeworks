 /**
  ******************************************************************************
  * @file    sys.c
  * @author  oscar
  * @version V0.1.1
  * @date    
  * @brief   
  * 
  * 1.增加RCC时钟配置函数
  * 2.增加了中断和NVIC设置函数 
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
#include "sys_config.h"


/**
 * @brief  Configures the system clock (RCC).
 * @param  None
 * @retval None
 * @note   This function initializes the system clock to use an external high-speed oscillator (HSE) 8MHZ. 
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
		/*主要是延时的部分，FLASH_ACR寄存器
		*/
        FLASH_SetLatency(FLASH_Latency_2);  
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  
        RCC_PLLCmd(ENABLE);  /* Enable PLL */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);  /* Wait for PLL to stabilize */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /* Switch system clock to PLL */
        while (RCC_GetSYSCLKSource() != 0x08);  /* Wait for PLL to be used as SYSCLK */
    }  

    /* Enable peripheral clocks for required devices */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
                           RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
}
  



/**
 * @brief  Configures the EXTI and NVIC for encoders and buttons.
 * @param  None
 * @retval None 
 * @note   This function configures the EXTI and NVIC for the two buttons and encoders. 
 *         It sets the interrupt priority and enables the corresponding interrupt.
 * @attention It also configures the GPIO ports for the buttons and encoders.
 */
void EXTI_Key_Config() /* 主要是连接EXTI与GPIO */
{
	//GPIO端口配置
    GPIO_InitTypeDef GPIO_InitStruct ;
    /* 初始化要与EXTI连接的GPIO */
    /* 开启GPIOA与GPIOC的时钟 */
    RCC_APB2PeriphClockCmd(KEY_UP_EXTI_GPIO_RCC | KEY_DOWN_EXTI_GPIO_RCC, ENABLE) ;
    
    GPIO_InitStruct.GPIO_Pin = KEY_UP_EXTI_GPIO_PIN ;
    //设置GPIO模式为上拉输入
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU ;                     // 1.首先需要配置GPIO的时钟还有模式
    //初始化旋转编码器的上旋转通道
    GPIO_Init( KEY_UP_EXTI_GPIO_PORT, &GPIO_InitStruct) ;
    
	
    GPIO_InitStruct.GPIO_Pin = KEY_DOWN_EXTI_GPIO_PIN ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU ;
    //初始化旋转编码器的下旋转通道
    GPIO_Init(KEY_DOWN_EXTI_GPIO_PORT , &GPIO_InitStruct) ;
	/****将GPIO配置为外部中断***/
    /* EXTI的时钟要设置AFIO寄存器 */                                   //2.配置EXTI外部中断控制器                                         
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE) ;            //2.1.开启AFIO时钟,必须启用AFIO复用重映射功能，
                                                                    
                            
                                                                    //2.2.配置EXTI线，使能中断，配置中断模式，边沿触发，使能中断
    /* 初始化EXTI外设 */                                            // 把对应作为中断输入的IO口，重映射到对应的EXTI外部中断中断/事件线。
    /* 选择作为EXTI线的GPIO引脚 */
    //函数解释 ：把某一组IO端口和外部中断EXTIx相连接，@param1是给出GPIO相应的IO端口组，
    //@@param2是给出的IO端口组连接到哪一个中断通道
    //相当于选定外部中断只能从EXTI4进入，然后再从连接EXTI4的物理端口中选中合适的即可
    GPIO_EXTILineConfig( KEY_UP_GPIO_PORTSOURCE , KEY_UP_GPIO_PINSOURCE) ;
    /* 配置中断or事件线 */
        
    //配置所需端口为外部中断。
	EXTI_InitTypeDef EXTI_InitStruct ;  
    EXTI_InitStruct.EXTI_Line = KEY_UP_EXTI_LINE ;
    /* 使能EXTI线 */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE ;
    /* 配置模式：中断or事件 */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt ;
    /* 配置边沿触发 上升or下降 */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling ;
    EXTI_Init(&EXTI_InitStruct) ;
    GPIO_EXTILineConfig( KEY_DOWN_GPIO_PORTSOURCE , KEY_DOWN_GPIO_PINSOURCE) ;
    EXTI_InitStruct.EXTI_Line = KEY_DOWN_EXTI_LINE ;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE ;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt ;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling ;
    EXTI_Init(&EXTI_InitStruct);
    //将中断向量控制器给打开
    NVIC_Config();
}

static void NVIC_Config(void) /* 主要是配置中断源的优先级与打开使能中断通道 */                        //3.配置NVIC(中断向量控制器)，也就是设置中断源的优先级和打开使能中断通道
{
	/* 配置中断优先级分组(设置抢占优先级和子优先级的分配)，在函数在misc.c */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2) ;
    //中断优先级分组为2 所以抢占优先级的范围为0~3 子优先级的范围为0~7
    //同时优先级的数字越小，优先级越高
    /* 配置初始化结构体 在misc.h中 */
    /* 配置中断源 在stm32f10x.h中 */
	//对KEY_UP的中断优先级和子优先级进行设置
	NVIC_InitTypeDef NVIC_InitStruct ;
    NVIC_InitStruct.NVIC_IRQChannel = KEY_UP_EXTI_IRQN ; //EXTI0_IRQn
    /* 配置抢占优先级 */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
    /* 配置子优先级 */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    /* 使能中断通道 */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
    /* 调用初始化函数 */
    NVIC_Init(&NVIC_InitStruct) ;
    
    /* 对KEY_DOWN执行相同操作 */
    NVIC_InitStruct.NVIC_IRQChannel = KEY_DOWN_EXTI_IRQN ;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
    NVIC_Init(&NVIC_InitStruct) ;
    
}

