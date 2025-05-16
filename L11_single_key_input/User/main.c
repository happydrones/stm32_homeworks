/**
  ******************************************************************************
  * @file    mian.c
  * @author  wangshenghui
  * @version V1.0.0
  * @date    18-October-2024
  * @brief   This file provides all the GPIO firmware functions.
  ******************************************************************************
  * @attention
  *
  * 
  * 
  * 
  * 
  * 
  * 
  *
  ******************************************************************************
  */

#include "sys.h"


uint16_t show_number=0;

int main(void)
{
	//初始化公共引脚
	Common_Pin_Init(&common_Pin);
	//初始化加号按键
	Key_Init(&up_key);
	TM1640_Init(); //初始化引脚定义和模式配置
	TM1640_Display_Init();
	while(1)
	{
		Key_Scan(&up_key);
		if(1 ==up_key.key_flag)
		{
			show_number +=1;
			up_key.key_flag = 0;
			TM1640_DisplayNumber(1,4,show_number,1);
		}
	}

}




/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1);  //延时1秒

*/

/************************************************************************
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出

选择IO口哪一位：
GPIO_Pin_0 
GPIO_Pin_1 
GPIO_Pin_2 
GPIO_Pin_3 
GPIO_Pin_4 
GPIO_Pin_5 
GPIO_Pin_6 
GPIO_Pin_7 
GPIO_Pin_8 
GPIO_Pin_9 
GPIO_Pin_10 
GPIO_Pin_11 
GPIO_Pin_12 
GPIO_Pin_13 
GPIO_Pin_14 
GPIO_Pin_15
GPIO_Pin_All

现在IO口那组端口：
GPIOA
GPIOB
GPIOC
GPIOD
GPIOE
GPIOF
GPIOG
************************************************************************/


