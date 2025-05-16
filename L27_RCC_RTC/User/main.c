/**
  ******************************************************************************
  * @file    main.c
  * @author  oscar
  * @version v0.1.0
  * @date    2025-04-25
  * @brief   This file is a template for STM32F10x.
  *          
  *
  ******************************************************************************
  * @details
  * @changelog
  * ------------v0.0.1   No key control, only display time   2025-04-24
  * ------------v0.1.0  Add key control, add setting mode   2025-04-25
  *
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
  */
#include "stm32f10x.h"   
#include "led.h"
#include "1602lcd.h"
#include "delay.h"
#include "sys_config.h"
#include "rtc.h"
#include "matrix_keypad.h"


#define RCC_SysTclk  72  //Please fill in the AHB clock frequency set in RCC here (in MHz)

extern u16 ryear; //4-bit year
extern u8 rmon, rday, rhour, rmin, rsec, rweek; //2-digit month, day, hour, minute, second, week
uint8_t Key_Value = 0; //Key scan value
uint8_t setting_mode = 0; //Setting mode
enum{normal, set_sec, set_min, set_hour, set_day, set_month, set_year};
uint16_t blink_count = 0; //Blink counter
uint8_t show_nothing[2] = {0x00, 0x00}; //Display nothing
uint8_t week;
int main(void)
{
	//u8  shi=8,fen=30,miao=0,week=1;
  	RCC_Configuration();//Configure system clock to 72MHZ, set to external high-speed clock
	RCC_ClockSecuritySystemCmd(ENABLE); //Enable or disable clock security system  
  	//RCC_HSI_SetSysCLK(); //Configure system clock to 64MHZ, set to internal high-speed clock

	RTC_Config(); //实时时钟初始化
	// RTC_Set(2025,4,25,12,57,30); //设置时间3013
	Keypad_Init(); //按键初始化
	Lcd_1602_Init();  //1602液晶屏初始化函数
	Display_Lcd_1602(1,1,"2023-12-07 Thur.",16); 	
  	Display_Lcd_1602(2,1,"  00:00:00      ",16);	
	while(1)
	{
		if(setting_mode == normal)
			{       
				RTC_Get();//读出当前时间值
				Display_Lcd_1602_Number(1,1,ryear,4); 	//1602显示 年
				Display_Lcd_1602_Number(1,6,rmon,2);   //1602显示 月
				Display_Lcd_1602_Number(1,9,rday,2);   //1602显示 日
				Display_Lcd_1602_Number(2,3,rhour,2);  //1602显示 时
				Display_Lcd_1602_Number(2,6,rmin,2);   //1602显示 分
				Display_Lcd_1602_Number(2,9,rsec,2);	//1602显示 秒	

				// week =RTC_Get_Week(ryear,rmon,rday);
				// Display_Lcd_1602_Number(2,12,week,3); //1602显示 星期
				// Display_Lcd_1602_Number(2,12,rweek,3); //1602显示 星期
				switch(rweek) 
				{
					case 0:Display_Lcd_1602(1,12,"Sun. ",16);  break;
					case 1:Display_Lcd_1602(1,12,"Mon. ",16);  break;
					case 2:Display_Lcd_1602(1,12,"Tues.",16);  break;
					case 3:Display_Lcd_1602(1,12,"Wed. ",16);  break;
					case 4:Display_Lcd_1602(1,12,"Thur.",16);  break;
					case 5:Display_Lcd_1602(1,12,"Fri. ",16);  break;
					case 6:Display_Lcd_1602(1,12,"Sat. ",16);  break;
				
					//default:{Jianzhi = 22;}   break;
				}	
			}
        Key_Value = Keypad_Scan();
		//按动K13进入setting mode
        if (Key_Value == 13)
        {
            setting_mode = set_sec;
			Key_Value =0;
        }
		
        //首先进入setting mode ,然后按一次方向键，进入设置秒模式，将setting mode置为2
		while(setting_mode == set_sec)
		{
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = normal;
				Key_Value =0;
				break;
			}
			
			if (blink_count == 1)
			{
				Display_Lcd_1602_Number(2,9,rsec,2);	//1602显示 秒	
			}
			else if (blink_count == 30000)
			{
				Display_Lcd_1602(2,9,"  ",2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			if (Key_Value == 4)
			{
				rsec++;
				Key_Value = 0;
				Display_Time_LCD1602(2, 3, rhour, rmin, rsec);
			}
		

				
			if (Key_Value == 12 )
			{
				rsec--;
				Key_Value = 0;
				Display_Time_LCD1602(2, 3, rhour, rmin, rsec);
			}
			if ( Key_Value == 8)
			{
				Display_Lcd_1602_Number(2,9,rsec,2);
				setting_mode = set_min;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				setting_mode = normal;
				Key_Value =0;
				break; 
			}
		}

		//进入setting mode的rmin,
		while(setting_mode == set_min)
		{
			Key_Value = Keypad_Scan();
			
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = normal;
				Key_Value =0;
				break;
			}
			//显示刷新
			if (blink_count == 1)
			{
				Display_Lcd_1602_Number(2,6,rmin,2);	//1602显示 分
			}
			else if (blink_count == 30000)
			{
				Display_Lcd_1602(2,6,"  ",2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			
			//按键判断
			if (Key_Value == 4 )
			{
				rmin++;
				Key_Value = 0;
				Display_Time_LCD1602(2, 3, rhour, rmin, rsec);
			}
			if (Key_Value == 12 )
			{
				rmin--;
				Key_Value = 0;
				Display_Time_LCD1602(2, 3, rhour, rmin, rsec);
			}

			if ( Key_Value == 8)
			{
				Display_Lcd_1602_Number(2,6,rmin,2);
				setting_mode = set_hour;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				Display_Lcd_1602_Number(2,9,rmin,2);
				setting_mode = set_sec;
				Key_Value =0;
				break; 
			}
			
		}
		//进入setting mode的rhour,
		while(setting_mode == set_hour)
		{
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = normal;
				Key_Value =0;
				break;
			}
			//显示刷新
			if (blink_count == 1)
			{
				Display_Lcd_1602_Number(2,3,rhour,2);	//1602显示 时
			}
			else if (blink_count == 30000)
			{
				Display_Lcd_1602(2,3,"  ",2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			
			//进入setting mode的rhour,
			if (Key_Value == 4 )
			{
				rhour++;
				Key_Value = 0;
				Display_Time_LCD1602(2, 3, rhour, rmin, rsec);
			}
			if (Key_Value == 12 )
			{
				rhour--;
				Key_Value = 0;
				Display_Time_LCD1602(2, 3, rhour, rmin, rsec);
			}
			if ( Key_Value == 8)
			{
				Display_Lcd_1602_Number(2,3,rhour,2);
				setting_mode = set_day;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				Display_Lcd_1602_Number(2,3,rhour,2);
				setting_mode = set_min;
				Key_Value =0;
				break; 
			}			
		}
		//进入setting mode的rday,
		while(setting_mode == set_day)
		{
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = normal;
				Key_Value =0;
				break;
			}
			//显示刷新
			if (blink_count == 1)
			{
				Display_Lcd_1602_Number(1,9,rday,2);	//1602显示 时
			}
			else if (blink_count == 30000)
			{
				Display_Lcd_1602(1,9,"  ",2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			
			if (Key_Value == 4 )
			{
				rday++;
				Key_Value = 0;
				Display_Lcd_1602_Number(1,9,rday,2);
			}
			if (Key_Value == 12 )
			{
				rday--;
				Key_Value = 0;
				Display_Lcd_1602_Number(1,9,rday,2);
			}
			if ( Key_Value == 8)
			{
				Display_Lcd_1602_Number(2,9,rday,2);
				setting_mode = set_month;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				Display_Lcd_1602_Number(2,9,rday,2);	
				setting_mode = set_hour;
				Key_Value =0;
				break; 
			}			
		}
		//进入set_month,
		while(setting_mode == set_month)
		{
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = normal;
				Key_Value =0;
				break;
			}
			//显示刷新
			if (blink_count == 1)
			{
				Display_Lcd_1602_Number(1,6,rmon,2);	//1602显示 时
			}
			else if (blink_count == 30000)
			{
				Display_Lcd_1602(1,6,"  ",2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			
			//进入setting mode的rmonth,
			if (Key_Value == 4 )
			{
				rmon++;
				Key_Value = 0;
				Display_Lcd_1602_Number(1,6,rmon,2);
			}
			if (Key_Value == 12 )
			{
				rmon--;
				Key_Value = 0;
				Display_Lcd_1602_Number(1,6,rmon,2);
			}
			if ( Key_Value == 8)
			{
				Display_Lcd_1602_Number(1,6,rmon,2);
				setting_mode = set_year;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				Display_Lcd_1602_Number(1,6,rmon,2);
				setting_mode = set_day;
				Key_Value =0;
				break; 
			}			
		}
		//进入setting mode的ryear,
		while(setting_mode == set_year)
		{
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				setting_mode = normal;
				Key_Value =0;
				break;
			}
			//显示刷新
			if (blink_count == 1)
			{
				Display_Lcd_1602_Number(1,1,ryear,4);	//1602显示 时
			}
			else if (blink_count == 30000)
			{
				Display_Lcd_1602(1,1,"    ",4);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			
			//进入调节区域
			if (Key_Value == 4 )
			{
				ryear++;
				Key_Value = 0;
				Display_Lcd_1602_Number(1,1,ryear,4);
			}
			if (Key_Value == 12 )
			{
				ryear--;
				Key_Value = 0;
				Display_Lcd_1602_Number(1,1,ryear,4);
			}
			if ( Key_Value == 8)
			{
				Display_Lcd_1602_Number(1,1,ryear,4);
				setting_mode = normal;
				Key_Value =0;
				break; 
			}
			if ( Key_Value == 16)
			{
				Display_Lcd_1602_Number(1,1,ryear,4);
				setting_mode = set_month;
				Key_Value =0;
				break; 
			}			
		}
		// //进入亮度调节设置模式
		// while(setting_mode == 5)
		// {
		// 	Key_Value = Keypad_Scan();
		// 	//退出设置模式
		// 	if(Key_Value ==13)
		// 	{
		// 		setting_mode = 0;
		// 		Key_Value =0;
		// 		break;
		// 	}
		// 	if(Key_Value ==14)
		// 	{
		// 		setting_mode = 0;
		// 		Key_Value =0;
		// 		break;
		// 	}

		// 	if (blink_count == 1)
		// 	{
		// 		TM1640_DisplayTime(rhour, rmin,  rsec);
		// 	}
		// 	else if (blink_count == 10000)
		// 	{
		// 		TM1640_Clear();
		// 	}
		// 	else if (blink_count == 20000)
		// 	{
		// 		blink_count = 0; 
		// 	}
		// 	blink_count ++;
		// 	if (Key_Value == 4 )
		// 	{
		// 		Brightness_level ++;
		// 		Key_Value = 0;
		// 		TM1640_SetBrightness((Brightness_level_t) (((Brightness_level)%8)+0x88));
		// 		TM1640_DisplayTime(rhour, rmin,  rsec);
		// 	}
		// 	if (Key_Value == 12 )
		// 	{
		// 		Brightness_level --;
		// 		Key_Value = 0;
		// 		TM1640_SetBrightness((Brightness_level_t) (((Brightness_level)%8)+0x88));
		// 		TM1640_DisplayTime(rhour, rmin,  rsec);
		// 	}

		// }
			
	}	

}
/*************************************************************************

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


