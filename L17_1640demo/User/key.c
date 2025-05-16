/**************************************************************************//**
* @file     key.c
* @brief    4x4 Matrix Keypad Driver for STM32 Microcontrollers
* @version  V1.00
* @date     19. October 2024
* @note
* This file contains functions for initializing and scanning a 4x4 matrix
* keypad connected to GPIO pins of an STM32 microcontroller. The keys can
* be scanned to detect key presses, and the corresponding GPIO configurations
* are set up for both input and output operations.
* @par
* This driver is designed to work with multiple GPIO ports (A, B, C, D, E, F, G)
* to support flexibility in wiring the keypad to different pins of the MCU.
* It also includes debounce logic with delays and can toggle an LED as feedback
* when a key is pressed.

*
******************************************************************************/

#include "key.h"
#include "delay.h"
#include "led.h"






// 初始化行引脚为输出，列引脚为上拉输入
void Keypad_Init(void)
{
	RCC_APB2PeriphClockCmd(KEYPAD_GPIO_CLK,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;

    // 初始化行（ROW）为推挽输出
	//只要传入的参数为16进制，然后 那一位是1，就会给将对应的模式
    GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);

    // 初始化列（COL）为上拉输入
    GPIO_InitStruct.GPIO_Pin = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
}

// 扫描矩阵键盘，返回按下的键值，如果没有按下则返回 0


#if 0

char Keypad_Scan(void)
{
	uint8_t key_contining_time =0 ;
	char key_value;
    for (int row = 0; row < 4; row++)
    {
        // 设置当前行为低电平，其他行为高电平
        GPIO_SetBits(ROW_GPIO_PORT, ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN); // 所有行设为高电平
        GPIO_ResetBits(ROW_GPIO_PORT, (0x01 << row));  // 选择当前行为低电平
        // 第一行键盘扫描
        if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL1_PIN) == 0)
        {
            delay_ms(15);
            if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL1_PIN) == 0)
			{
				while((GPIO_ReadInputDataBit(COL_GPIO_PORT, COL1_PIN) == 0)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
				{
					delay_ms(10);
					key_contining_time ++;
				}
				if(key_contining_time>LONG_PRESS_THRESHOLD)
				{
					Long_press_flag =2;
					key_value = key_map[row][0];
                    return key_value;					
				}
				else
				{
					if(Long_press_flag == 1)
					{
						Long_press_flag --;
						return key_value = 0;
					}
					if(Long_press_flag < 1)
					{
						Long_press_flag=0;
						return key_value = key_map[row][0];
						
					}
				}
			}
        }
		//第二行
        if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL2_PIN) == 0)
        {
            delay_ms(20);
            if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL2_PIN) == 0)
			{
				while((GPIO_ReadInputDataBit(COL_GPIO_PORT, COL2_PIN) == 0)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
				{
					delay_ms(10);
					key_contining_time ++;
				}
				if(key_contining_time>LONG_PRESS_THRESHOLD)
				{
					Long_press_flag =2;
					key_value = key_map[row][1];
                    return key_value;					
				}
				else
				{
					if(Long_press_flag == 1)
					{
						Long_press_flag --;
						return key_value = 0;
					}
					if(Long_press_flag < 1)
					{
						Long_press_flag=0;
						return key_value = key_map[row][1];
						
					}
				}
			}
        }
		//第三行
        if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL3_PIN) == 0)
        {
            delay_ms(20);
            if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL4_PIN) == 0)
			{
				while((GPIO_ReadInputDataBit(COL_GPIO_PORT, COL4_PIN) == 0)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
				{
					delay_ms(10);
					key_contining_time ++;
				}
				if(key_contining_time>LONG_PRESS_THRESHOLD)
				{
					Long_press_flag =1;
					key_value = key_map[row][2];
					Is_Pre_mode_long =2;	
				}
				else
				{
					if(Is_Pre_mode_long <2)
					{	
					key_value = key_map[row][2];
					}
					Is_Pre_mode_long --;
				}
			}
        }
		//判断第四列的按键
        if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL4_PIN) == 0)
        {
            delay_ms(20);
            if (GPIO_ReadInputDataBit(COL_GPIO_PORT, COL4_PIN) == 0)
			{
				while((GPIO_ReadInputDataBit(COL_GPIO_PORT, COL4_PIN) == 0)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
				{
					delay_ms(10);
					key_contining_time ++;
				}
				
				if(key_contining_time>LONG_PRESS_THRESHOLD)
				{
					Long_press_flag =1;
					key_value = key_map[row][3];

					
				}
				else
				{
					Long_press_flag = 0;
					if(Is_Pre_mode_long ==2)
					{
						key_value = 0;
						Is_Pre_mode_long --;
						delay_ms(10);
						return key_value;
					}
					else
					{
						key_value = key_map[row][3];
						
					}
				}
			}
        
		}
    }
	
    return key_value;  // 没有按键按下
}
#endif




/*
 * @ brief 按键扫描函数采用的逐行扫描
 * @ return 按键值，范围0~16，0：未按下，1：按下，16：长按
 * @ note 
 * 1. 按键扫描函数
 *
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
		delay_ms(15);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FE)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) != 0x00FE)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				delay_ms(10);
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
		
	// 设置当前行为低电平，其他行为高电平
	GPIO_SetBits(ROW_GPIO_PORT, ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN); // 所有行设为高电平
	GPIO_ResetBits(ROW_GPIO_PORT, ROW2_PIN );    // 选择当前行为低电平
	// 第二行键盘扫描
	if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FD)
	{
		delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FD)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FD)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				delay_ms(10);
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
		delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FB)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00FB)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				delay_ms(10);
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
		delay_ms(10);
		if ((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00F7)
		{
			Temp =(GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF);
			while(((GPIO_ReadInputData(COL_GPIO_PORT)&0x00FF) !=0x00F7)&&(key_contining_time <= LONG_PRESS_THRESHOLD))
			{
				delay_ms(10);
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




/*
 * @ brief 按键检测函数
 * @ param Key 按键结构体
 * @ return 按键状态，0：未按下，1：按下
 */
void Independant_Key_Scan(struct key_struct* Key)
{
	if((GPIO_ReadInputDataBit(Key->GPIO_Group, Key->GPIO_Pin))==0)
	{
        delay_ms(10);
        if((GPIO_ReadInputDataBit(Key->GPIO_Group, Key->GPIO_Pin))==0)
        {
            Key->key_flag =1;
            LED_Toggle( GPIOA, GPIO_Pin_0);
            delay_ms(100);
        }
	}
}


uint8_t test_static_key_word(uint8_t Flag)
{
	static uint8_t value =0;
	if(Flag ==1)
	{
		value++;
	}
	return value ;

}


