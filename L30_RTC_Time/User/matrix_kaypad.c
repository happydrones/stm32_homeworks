/**
  ******************************************************************************
  * @file    matrix_keypad.c
  * @author  oscar
  * @version v0.2.0
  * 
  * @date    2025-04-30
  * @brief  This file is a driver for matrix keypad using intrrupt.
  *          
  *
  * @note    This file is a driver for matrix keypad using intrrupt.
  *          
  *
  *******************************************************************************
  * @version
  * 2025-05-01: Initial version by oscar.                v0.0.1          
  * 2025-04-30: Obtain key value through row scanning.   v0.1.0
  * 2025-05-15：Added column-scan interrupt mode for key value retrieval v0.2.0
  *
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
  */

#include "matrix_keypad.h"
#include "delay.h"

uint8_t Key_Value = 0;  //按键值
uint8_t interrupt = 0;  //按键值

#if  (!(INIT_KEYPAD_GPIO_PINS_WITH_INTRRUPT))
/**
  * @brief  Initializes the GPIO ports for the keypad rows and columns.
  *         Rows are configured as push-pull outputs, and columns are configured
  *         as pull-up inputs.
  * @param  None
  * @retval None
  */
void Keypad_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_Keypad, ENABLE); // Enable clock for GPIO ports used by the keypad

    GPIO_InitTypeDef GPIO_InitStruct;

    // Initialize rows (ROW) as push-pull outputs
    GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);

    // Initialize columns (COL) as pull-up inputs
    GPIO_InitStruct.GPIO_Pin = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
}


/**
  * @brief  Scans the keypad to detect key presses and determines whether the press
  *         is a short press or a long press based on the duration.
  * @param  None
  * @retval Key_Value: The value of the pressed key (1-16), with the MSB set (0x80) 
  *         if it is a long press. Returns 0 if no key is pressed.
  */
uint8_t Keypad_Scan(void)
{
	uint8_t key_contining_time =0 ;
	uint8_t Key_Value =0;
    uint8_t Temp;
	// 设置当前行为低电平，其他行为高电平
	GPIO_SetBits(ROW_GPIO_PORT, ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN); // 所有行设为高电平
	GPIO_ResetBits(ROW_GPIO_PORT, ROW1_PIN );  // 选择当前行为低电平
	//按照行扫描  
	// 第一行键盘扫描
	if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FE)
	{
		Delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FE)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) != 0x00FE)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				Delay_ms(10);
				key_contining_time ++;
			}
			switch(Temp)
			{
				case 0XEE: Key_Value = 1; break;
				case 0XDE: Key_Value = 2; break;
				case 0XBE: Key_Value = 3; break;
				case 0X7E: Key_Value = 4; break;
			}
		}
	}
		
	// 设置第二行为低电平，其他行为高电平
	GPIO_SetBits(ROW_GPIO_PORT, ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN); // 所有行设为高电平
	GPIO_ResetBits(ROW_GPIO_PORT, ROW2_PIN );    // 选择当前行为低电平
	// 第二行键盘扫描
	if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FD)
	{
		Delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FD)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FD)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				Delay_ms(10);
				key_contining_time ++;
			}
			switch(Temp)
			{
				
				case 0XED: Key_Value = 5; break;
				case 0XDD: Key_Value = 6; break;
				case 0XBD: Key_Value = 7; break;
				case 0X7D: Key_Value = 8; break;
			}
		}
	}
	
	// 设置当前行为低电平，其他行为高电平
	GPIO_SetBits(ROW_GPIO_PORT, ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN); // 所有行设为高电平
	GPIO_ResetBits(ROW_GPIO_PORT, ROW3_PIN );    // 选择当前行为低电平
	// 第三行键盘扫描
	if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FB)
	{
		Delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FB)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FB)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				Delay_ms(10);
				key_contining_time ++;
			}
			switch(Temp)
			{
				case 0XEB: Key_Value = 9; break;
				case 0XDB: Key_Value = 10; break;
				case 0XBB: Key_Value = 11; break;
				case 0X7B: Key_Value = 12; break;
			}
		}
	}
	// 设置当前行为低电平，其他行为高电平
	GPIO_SetBits(ROW_GPIO_PORT, ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN); // 所有行设为高电平
	GPIO_ResetBits(ROW_GPIO_PORT, ROW4_PIN );    // 选择当前行为低电平
	// 第四行键盘扫描
	if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00F7)
	{
		Delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00F7)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00F7)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				Delay_ms(10);
				key_contining_time ++;
			}
			switch(Temp)
			{
				case 0XE7: Key_Value = 13; break;
				case 0XD7: Key_Value = 14; break;
				case 0XB7: Key_Value = 15; break;
				case 0X77: Key_Value = 16; break;
			}
		}
	}


	if(key_contining_time>LONG_PRESS_THRESHOLD)
	{
		Key_Value |= 0x80;
	}
	// 选择所有行为低电平，便于后续判断
	GPIO_ResetBits(ROW_GPIO_PORT, ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN);  
    return Key_Value ;  // 没有按键按下		
}





#elif (INIT_KEYPAD_GPIO_PINS_WITH_INTRRUPT)




/**
  * @brief  
  *         
  *         
  * @param  None
  * @retval None
  */
void Keypad_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_Keypad | RCC_APB2Periph_AFIO, ENABLE); // Enable clock for GPIO ports used by the keypad

    GPIO_InitTypeDef GPIO_InitStruct;

    // Initialize rows (ROW) as push-pull outputs
    GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
	GPIO_Write(ROW_GPIO_PORT, 0x0); // 行引脚设为低电平

    // Initialize columns (COL) as pull-up inputs
    GPIO_InitStruct.GPIO_Pin  = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
	GPIO_Write(ROW_GPIO_PORT, 0xFFF0); // 行引脚设为低电平

	// *********************列扫描情况下键盘的中断配置*********************************/
	 // 配置EXTI线4到7
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);



	EXTI_InitTypeDef EXTI_InitStructure;
    // 配置EXTI线5,6,7为中断模式，下降沿触发
    EXTI_InitStructure.EXTI_Line    = EXTI_Line4 ;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line    = EXTI_Line5 | EXTI_Line6 | EXTI_Line7 ;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);


	// *********************列扫描情况下键盘的中断配置*********************************/


	/*********************行扫描情况下键盘的中断配置*********************************
	// 使能列中断
	GPIO_EXTILineConfig(COL_GPIO_PORT_SOURCE, COL1_PIN_SOURCE);
	GPIO_EXTILineConfig(COL_GPIO_PORT_SOURCE, COL2_PIN_SOURCE);
	GPIO_EXTILineConfig(COL_GPIO_PORT_SOURCE, COL3_PIN_SOURCE);
	GPIO_EXTILineConfig(COL_GPIO_PORT_SOURCE, COL4_PIN_SOURCE);


	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = ROW1_PIN_EXTI_LINE | ROW2_PIN_EXTI_LINE | ROW3_PIN_EXTI_LINE | ROW4_PIN_EXTI_LINE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	GPIO_EXTILineConfig(ROW_GPIO_PORT_SOURCE, ROW1_PIN_SOURCE);
	GPIO_EXTILineConfig(ROW_GPIO_PORT_SOURCE, ROW2_PIN_SOURCE);
	GPIO_EXTILineConfig(ROW_GPIO_PORT_SOURCE, ROW3_PIN_SOURCE);
	GPIO_EXTILineConfig(ROW_GPIO_PORT_SOURCE, ROW4_PIN_SOURCE);
	*********************行扫描情况下键盘的中断配置*********************************/
	Key_NVIC_Config();
}



static void Key_NVIC_Config(void) /* 主要是配置中断源的优先级与打开使能中断通道 */
{
	/* 配置中断优先级分组(设置抢占优先级和子优先级的分配)，在函数在misc.c */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2) ;
    //中断优先级分组为2 所以抢占优先级的范围为0~3 子优先级的范围为0~7
    //同时优先级的数字越小，优先级越高
    /* 配置初始化结构体 在misc.h中 */


   	// *********************列扫描情况下键盘的中断配置*********************************/

	//对第一列的中断优先级和子优先级进行设置
	NVIC_InitTypeDef NVIC_InitStruct ;
    NVIC_InitStruct.NVIC_IRQChannel = COL1_PIN_EXTI_IRQN  ; //EXTI4_IRQn
    //配置抢占优先级 
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
    //配置子优先级 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    // 使能中断通道 
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    // 调用初始化函数 
    NVIC_Init(&NVIC_InitStruct) ;

	//对第二列，第三列，第四列的中断优先级和子优先级进行设置
    NVIC_InitStruct.NVIC_IRQChannel = COL2_PIN_EXTI_IRQN  ; //EXTI4_IRQn
    //配置抢占优先级 
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
    //配置子优先级 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    // 使能中断通道 
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    // 调用初始化函数 
    NVIC_Init(&NVIC_InitStruct) ;



// *********************列扫描情况下键盘的中断配置*********************************/

/*********************行扫描情况下键盘的中断配置*********************************
	//对ROW1的中断优先级和子优先级进行设置
	NVIC_InitTypeDef NVIC_InitStruct ;
    NVIC_InitStruct.NVIC_IRQChannel = ROW1_PIN_EXTI_IRQN  ; //EXTI0_IRQn
    //配置抢占优先级 
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
    //配置子优先级 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    // 使能中断通道 
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
    // 调用初始化函数 
    NVIC_Init(&NVIC_InitStruct) ;

	//对ROW2的中断优先级和子优先级进行设置
	NVIC_InitStruct.NVIC_IRQChannel = ROW2_PIN_EXTI_IRQN  ; //EXTI1_IRQn
    // 配置抢占优先级 
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
    // 配置子优先级 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    //使能中断通道 /
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
    // 调用初始化函数 
    NVIC_Init(&NVIC_InitStruct) ;

	//对ROW3的中断优先级和子优先级进行设置
	NVIC_InitStruct.NVIC_IRQChannel = ROW3_PIN_EXTI_IRQN  ; //EXTI2_IRQn
    // 配置抢占优先级 
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
	//配置子优先级 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    //使能中断通道 
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
    // 调用初始化函数 
    NVIC_Init(&NVIC_InitStruct) ;

	//对ROW4的中断优先级和子优先级进行设置
	NVIC_InitStruct.NVIC_IRQChannel = ROW4_PIN_EXTI_IRQN  ; //EXTI3_IRQn
    //配置抢占优先级 
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1 ;
    // 配置子优先级 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;
    // 使能中断通道 
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE ;
    // 调用初始化函数 
    NVIC_Init(&NVIC_InitStruct) ;

***************************行扫描情况下键盘的中断配置**************************************************/    
}




//第一列键盘触发之后会进入该中断函数
void EXTI4_IRQHandler(void) 
{
	uint8_t Temp = 0;
	uint8_t key_contining_time = 0;
    // 进入确定按键的检测模式
	//将第一列列引脚设置为开漏输出0模式，然后行引脚设置为上拉输入
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = COL1_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
	
    // Initialize rows (ROW) as push-pull outputs
    GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
	GPIO_Write(ROW_GPIO_PORT, 0xFFEF); // 所有行设为低电平

	Delay_ms(10);
	if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) !=0x000F)
	{
		Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x000F);
		while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) != 0x000F)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
		{
			Delay_ms(10);
			key_contining_time ++;
		}
		switch(Temp)
		{
			case 0XE : Key_Value = 1; break;
			case 0XD : Key_Value = 5; break;
			case 0XB : Key_Value = 9; break;
			case 0X7 : Key_Value = 13; break;
		}
	}

    // Initialize rows (ROW) as push-pull outputs
    GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);

    // Initialize columns (COL) as pull-up inputs
    GPIO_InitStruct.GPIO_Pin  = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
	GPIO_Write(ROW_GPIO_PORT, 0xFFF0); // 行引脚设为低电平
	// 清除 EXTI4 中断标志
	EXTI_ClearITPendingBit(COL1_PIN_EXTI_LINE);
}

#if 1
//第二列，第三列，第四列键盘触发之后会进入该中断函数
void EXTI9_5_IRQHandler(void) 
{
    if (EXTI_GetITStatus(COL2_PIN_EXTI_LINE) != RESET) 
	{
		//将第二列列引脚设置为开漏输出0模式，然后行引脚设置为上拉输入
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = COL2_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
		
		// Initialize rows (ROW) as push-pull outputs
		GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
		GPIO_Write(ROW_GPIO_PORT, 0xFFDF); // 所有行设为低电平

		Delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) !=0x000F)
		{
			uint8_t Temp = 0;
			uint8_t key_contining_time = 0;
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x000F);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) != 0x000F)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				Delay_ms(10);
				key_contining_time ++;
			}
			switch(Temp)
			{
				case 0XE : Key_Value = 2; break;
				case 0XD : Key_Value = 6; break;
				case 0XB : Key_Value = 10; break;
				case 0X7 : Key_Value = 14; break;
			}
		}

		// Initialize rows (ROW) as push-pull outputs
		GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);

		// Initialize columns (COL) as pull-up inputs
		GPIO_InitStruct.GPIO_Pin  = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
		GPIO_Write(ROW_GPIO_PORT, 0xFFF0); // 行引脚设为低电平
        EXTI_ClearITPendingBit(COL2_PIN_EXTI_LINE);
    }

    if (EXTI_GetITStatus(COL3_PIN_EXTI_LINE) != RESET)
	{
		//将第三列列引脚设置为开漏输出0模式，然后行引脚设置为上拉输入
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = COL3_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
		
		// Initialize rows (ROW) as push-pull outputs
		GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
		GPIO_Write(ROW_GPIO_PORT, 0xFFBF); //行引脚设为低电平，第三列引脚设置为上拉输入

		Delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) !=0x000F)
		{
			uint8_t Temp = 0;
			uint8_t key_contining_time = 0;
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x000F);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) != 0x000F)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				Delay_ms(10);
				key_contining_time ++;
			}
			switch(Temp)
			{
				case 0XE : Key_Value = 3 ; break;
				case 0XD : Key_Value = 7 ; break;
				case 0XB : Key_Value = 11; break;
				case 0X7 : Key_Value = 15; break;
			}
		}

		// Initialize rows (ROW) as push-pull outputs
		GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);

		// Initialize columns (COL) as pull-up inputs
		GPIO_InitStruct.GPIO_Pin  = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
		GPIO_Write(ROW_GPIO_PORT, 0xFFF0); // 行引脚设为低电平
        EXTI_ClearITPendingBit(COL3_PIN_EXTI_LINE);
    }
    if (EXTI_GetITStatus(COL4_PIN_EXTI_LINE) != RESET) 
	{
		//将第四列列引脚设置为开漏输出0模式，然后行引脚设置为上拉输入
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = COL4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
		
		// Initialize rows (ROW) as push-pull outputs
		GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);
		GPIO_Write(ROW_GPIO_PORT, 0xFF7F); //行引脚设为低电平，第三列引脚设置为上拉输入

		Delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) !=0x000F)
		{
			uint8_t Temp = 0;
			uint8_t key_contining_time = 0;
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x000F);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x000F) != 0x000F)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				Delay_ms(10);
				key_contining_time ++;
			}
			switch(Temp)
			{
				case 0XE : Key_Value = 4 ; break;
				case 0XD : Key_Value = 8 ; break;
				case 0XB : Key_Value = 12; break;
				case 0X7 : Key_Value = 16; break;
			}
		}

		// Initialize rows (ROW) as push-pull outputs
		GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);

		// Initialize columns (COL) as pull-up inputs
		GPIO_InitStruct.GPIO_Pin  = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
		GPIO_Write(ROW_GPIO_PORT, 0xFFF0); // 行引脚设为低电平
        EXTI_ClearITPendingBit(COL4_PIN_EXTI_LINE);
    }
}

#endif
/**
  * @brief  Scans the the first row of the keypad to detect key presses and determines whether the press
  *         is a short press or a long press based on the duration.
  * @param  None
  * @retval Key_Value: The value of the pressed key (1-16), with the MSB set (0x80) 
  *         if it is a long press. Returns 0 if no key is pressed.
  */
/******************************使用行扫描作为中断服务函数**********
void EXTI0_IRQHandler(void) 
{
    // 检查 EXTI0 中断是否被触发
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
    {
        // TODO: 在这里处理按键逻辑，例如翻转 LED 状态
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));

        // 清除 EXTI0 中断标志
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
*****************************************************************************/




























#endif




/*
1.GPIO输入位操作：  
GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  //读 1位 IO
2.GPIO输入总线操作：
GPIO_ReadInputData(GPIO_TypeDef* GPIOx);  //读整组IO 
3.GPIO读输出ODR寄存器 位操作：
GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
4.GPIO读输出ODR寄存器 总线操作：
GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
*/

