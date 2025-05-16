/**
  ******************************************************************************
  * @file    main.c
  * @author  oscar
  * @version v0.2.0
  * 
  * @date    2025-04-30
  * @brief	 Implemented a digital clock system based on STM32.
  *          
  *
  * @note    	注意使用串口调试数据的时候，帧格式，每次发送的数据必须以"\r\n"结尾
  *				才能够正常工作 					
  * @function   --show current time on 1602 LCD.
  *             --set time by keypad & UART host interface.
  * 
  *******************************************************************************
  * @version
  * 2025-05-01: Initial version by oscar.                				  v0.0.1
  * 2025-05-16: 将帧数据接收完成标志由"\r\n"改为使用串口空闲中断产生      v0.0.2
  * #todo: add 自动化脚本获取电脑时间，并设置RTC时间。
  * 
  *
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
***/

#include "stm32f10x.h"   
#include "delay.h"
#include "pwm.h"
#include "matrix_keypad.h"
#include "led.h"
#include "sys_config.h"
#include "i2c.h"
#include "oled0561.h"
#include "usart.h"
#include "1602lcd.h"
#include "rtc.h"

uint8_t max_same_char(const volatile  char * s);
typedef struct student
{
	char name[128];
	const int *p;
	int ID;
	
}student_t;


//创建一个联合体union
union memmory
{
	uint32_t number;
	uint8_t  a;

};

uint8_t setting_mode = 0; //Setting mode
enum mode{normal, set_sec, set_min, set_hour, set_day, set_month, set_year};
uint16_t blink_count = 0; //Blink counter

int main(void)
{
	RCC_Configuration();
	RTC_Config();
	Lcd_1602_Init();
	Display_Lcd_1602(1,1,"2025-05-15",10);
	Display_Lcd_1602(2,3,"14:13:50",8);
	Keypad_Init();
	USART1_Init(9600);
	while(1)	
	{
		//串口设置时间的接收处理
		//首先判断串口是否接收到了数据
		if(1 == Rx_Data_Flag)
		{
			//三个if分别对应串口接收到三个数据之后的不同设置
			Rx_Data_Flag =0;
			if(USART1_RX_BUF[0] == '0' && USART1_RX_BUF[1] == '1' && USART1_RX_BUF[2] == '\0')
			{
				printf("current time is %04d-%02d-%02d %02d:%02d:%02d\r\n", ryear, rmon, rday, rhour, rmin, rsec);
				USART1_RX_BUF[0] = 0;
				USART1_RX_BUF[1] = 0;
				USART1_RX_BUF[2] = 0;
			}
			if(USART1_RX_BUF[0] == '0' && USART1_RX_BUF[1] == '2' && USART1_RX_BUF[2] == '\0')
			{
				printf("start set time: T2025-5-12 15:35:25");
				USART1_RX_BUF[0] = 0;
				USART1_RX_BUF[1] = 0;
				USART1_RX_BUF[2] = 0;
			}
			if(USART1_RX_BUF[0] == 'T')
			{
				//(USART1_RX_)
				sscanf((char *)(USART1_RX_BUF + 1), "%hu-%hhu-%hhu %hhu:%hhu:%hhu", &ryear, &rmon, &rday, &rhour, &rmin, &rsec);
				if(0 ==RTC_Set(ryear,rmon,rday,rhour,rmin,rsec))
				{
					printf("time set sucessfully");
					
				}
					
			}
		}	

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
		//按动K13进入setting mode
        if (Key_Value == 13)
        {
            setting_mode = set_sec;
			Key_Value =0;
        }
		// if (((Key_Value)& 0x7f)==14)
		// {
		// 	setting_mode = 5;
		// 	Key_Value =0;
		// }
		
        //首先进入setting mode ,然后按一次方向键，进入设置秒模式，将setting mode置为2
		while(setting_mode == set_sec)
		{

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
	}//while
}//main


uint8_t max_same_char( const volatile  char * s)
{
	uint8_t same_char_count = 0;
	uint8_t count = 0;
	char prev_char = *s;
	while('\0' !=*s )
	{
		if(prev_char ==*(s))
		{
			count++;
			if(count>same_char_count)
			{
				same_char_count = count;
			}
		}
		else
		{
			prev_char =*(s);
			count =1;
		}
		s++;
		
	}
	return same_char_count;
}

