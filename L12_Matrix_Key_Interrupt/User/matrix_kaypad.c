#include "matrix_keypad.h"
#include "delay.h"

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

