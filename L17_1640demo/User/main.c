/**
  ******************************************************************************
  * @file    mian.c
  * @author  wangshenghui
  * @version V1.2.0
  * @date    18-October-2024
  * @brief   The TM1604.c file contains the driver functions for connecting a Tianwei 1640 chip to a common cathode seven-segment display
  ******************************************************************************
  * @brief 
  * The current mian.c function file uses four directional keys, 
  * and its function is to reverse the corresponding light 
  * when the corresponding key is pressed.
  * the data will be display on 
  * @details 
  * 按动方向键对应的leds闪烁，实现四个方向键按动下去，对应的led闪烁
  * @details 
  * 实现了厨房小定时的调节时间的功能
  * @attention
  * 注意事项：
  * 1. 该程序为个人开发，如果你使用该程序，请保留作者信息
  ******************************************************************************
  */

#include "stm32f10x.h"   
#include "sys.h"
#include "led.h"
#include "delay.h"
#include "pwm.h"
#include "esc.h"
#include "key.h"
#include "TM1640.h"
#include "lcd1602.h"


uint8_t Hours, Minutes, Seconds;
uint16_t loops_of_per_secend =0;
uint8_t  setting_mode = 0;
// 0 运行模式，1 设置秒，2 设置分，3 设计小时

uint8_t Key_Value;
uint8_t number;


int main(void)
{
	
	//intit matrix keypad
	Keypad_Init();
	//显示时间
	Hours = 0;
	Minutes = 0;
	Seconds = 0;
	//uint8_t number_array[8] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x07,0x07};
	//1602液晶屏显示部分
	Lcd_1602_GPIO_Config();
	Lcd_1602_Init();
	Display_Lcd_1602(1,1, " Easy Board");
	Display_Lcd_1602(2,1,"counter:");
	number =0;
	
	while(1)
	{
		Key_Value = Keypad_Scan();
		if (Key_Value == 4 )
			{
				number++;
				Key_Value = 0;
				Display_Lcd_1602_Number(2,9,number,3);
			}
		
		
		
		




/****************按键控制数码管显示函数****************
	Display_Lcd_1602(1,1," Easy Board 51  ",16);




		if(setting_mode == 0)
		{
		
			loops_of_per_secend++;
			if(loops_of_per_secend >= 60000)
			{	
				Seconds++;
				loops_of_per_secend =0;
				if(Seconds == 60)
				{
					Seconds = 0;
					Minutes++;
					if(Minutes == 60)
					{
						Minutes = 0;
						Hours++;
						if(Hours == 24)
						{
							Hours = 0;
						}
					}
				}
			TM1640_DisplayTime(Hours, Minutes,  Seconds);	
			}
			
        }

        Key_Value = Keypad_Scan();
        if (Key_Value == 13)
        {
            setting_mode = 1;
			Key_Value =0;
        }
        //首先进入setting mode ,然后按一次方向键，进入设置秒模式，将setting mode置为2
		while(setting_mode == 1)
		{
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = 0;
				Key_Value =0;
				break;
				
			}
			
			if (blink_count == 1)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			else if (blink_count == 30000)
			{
				TM1640_DisplayOriginalNum(7, show_nothing , 2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			if (Key_Value == 4 )
			{
				Seconds++;
				Key_Value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if (Key_Value == 12 )
			{
				Seconds--;
				Key_Value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if ( Key_Value == 8)
			{
				setting_mode = 2;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				setting_mode = 0;
				Key_Value =0;
				break; 
			}
		}
		//进入setting mode的Minutes,
		while(setting_mode == 2)
		{
			Key_Value = Keypad_Scan();
			
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = 0;
				Key_Value =0;
				break;
			}
			//显示刷新
			if (blink_count == 1)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			else if (blink_count == 30000)
			{
				TM1640_DisplayOriginalNum(4, show_nothing , 2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			
			//按键判断
			if (Key_Value == 4 )
			{
				Minutes++;
				Key_Value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if (Key_Value == 12 )
			{
				Minutes--;
				Key_Value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}

			if ( Key_Value == 8)
			{
				setting_mode = 3;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				setting_mode = 1;
				Key_Value =0;
				break; 
			}
			
		}
		//进入setting mode的Hours,
		while(setting_mode == 3)
		{
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = 0;
				Key_Value =0;
				break;
			}
			//显示刷新
			if (blink_count == 1)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			else if (blink_count == 30000)
			{
				TM1640_DisplayOriginalNum(1, show_nothing , 2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			
			//按键判断
			if (Key_Value == 4 )
			{
				Hours++;
				Key_Value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if (Key_Value == 12 )
			{
				Hours--;
				Key_Value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}

			if ( Key_Value == 8)
			{
				setting_mode = 0;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				setting_mode = 2;
				Key_Value =0;
				break; 
			}
			
		}
**********************************按键控制数码管函数************/



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


