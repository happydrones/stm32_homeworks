#include "exit.h"


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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU ;
    //初始化旋转编码器的上旋转通道
    GPIO_Init( KEY_UP_EXTI_GPIO_PORT, &GPIO_InitStruct) ;
    
	
    GPIO_InitStruct.GPIO_Pin = KEY_DOWN_EXTI_GPIO_PIN ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU ;
    //初始化旋转编码器的下旋转通道
    GPIO_Init(KEY_DOWN_EXTI_GPIO_PORT , &GPIO_InitStruct) ;
	
	
	
	/****将GPIO配置为外部中断***/
    /* EXTI的时钟要设置AFIO寄存器 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE) ;
    //配置所需端口为外部中断。
	EXTI_InitTypeDef EXTI_InitStruct ;
    /* 初始化EXTI外设 */
    /* 选择作为EXTI线的GPIO引脚 */
    GPIO_EXTILineConfig( KEY_UP_GPIO_PORTSOURCE , KEY_UP_GPIO_PINSOURCE) ;
    /* 配置中断or事件线 */
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

static void NVIC_Config(void) /* 主要是配置中断源的优先级与打开使能中断通道 */
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