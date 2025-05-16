



#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "delay.h"
#include "pwm.h"
#include "matrix_keypad.h"
#include "led.h"
#include "sys_config.h"
#include "flash.h"
#include "1602lcd.h"
#include "encoder.h"
#include "tm1640.h"


#define  addr_time_data 0x0807F800  //时间的flash地址 存储在0x0807F800地址 page255
#define  addr_brightness_data 0x0807F000  //亮度的flash地址 存储在0x0807F000地址 page254
uint8_t show_number;
uint8_t encoder_value;
uint8_t setting_mode;
uint8_t Hours,Minutes,Seconds;
uint16_t loops_of_per_secend;
uint16_t blink_count;
uint8_t show_nothing[2] = {0x00, 0x00};
uint8_t  Brightness_level =5; //亮度设置，默认5，最大8
uint32_t time[3];
uint32_t *pTime;
uint32_t *pTemp_time;
int main(void)
{
	RCC_Configuration(); 
	ENCODER_Init();
	TM1640_Init();
	TM1640_Display_Init();
	Seconds =*((uint8_t *)(addr_time_data));
	Minutes =*((uint8_t *)(addr_time_data)+4);
	Hours   =*((uint8_t *)(addr_time_data)+8);
	Brightness_level = FLASH_Read(addr_brightness_data);
	TM1640_SetBrightness((Brightness_level_t) (((Brightness_level)%8)+0x88));
	//PC_PA_13_14_15_Gpio(); //设置 PA 13 14 15   PC 13 14 15 io功能
	
	while(1)	
	{
		encoder_value =ENCODER_READ();
		if(setting_mode == 0)
		{
			
			loops_of_per_secend++;
			if(loops_of_per_secend >=40000)
			{	
				Seconds++;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
				time[0] = Seconds;	
				time[1] = Minutes;
				time[2] = Hours;
				//将时间写入到flash中
				/********************************************************/
				// 1. 解锁Flash控制寄存器
				FLASH_Unlock();
				FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
				pTime = (uint32_t*)addr_time_data;
				FLASH_ErasePage((uint32_t)pTime);     //擦除指定地址页，擦除必须以页单位，会擦除整页    
				for (int i = 0; i < 3; i++) 
				{
					pTemp_time =pTime;
					FLASH_ProgramWord((uint32_t)pTime, time[i]);  // 写入4字节数据
					pTime += 1;  // 每次写入4字节，更新写入地址
					
				}
				
				// 4. 锁定Flash控制寄存器
				FLASH_Lock();
				loops_of_per_secend =0;
				if(Seconds >= 60)
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
				
			
			}
		}

	   //按动旋转编码器进入setting mode，秒设置
        if (encoder_value == 3)
        {
            setting_mode = 1;
			encoder_value =0;
        }
		if(long_press_flag == 1)
		{
			setting_mode = 5;
			encoder_value =0;
			long_press_flag = 0;
		}
   		/************************运行时的主循环***************************/
		
		
		
    	/***秒设置模式 ,旋转滚轮调节秒，短按旋钮将setting mode置为2，进入分设置*******/
		while(setting_mode == 1)
		{
			//显示刷新
			if (blink_count == 1)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			else if (blink_count == 20000)
			{
				TM1640_DisplayOriginalNum(7, show_nothing , 2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			encoder_value = ENCODER_READ();
			//Display_Lcd_1602_Number(2,14,encoder_value,2);
			
			//退出设置模式
			if ( long_press_flag == 1)
			{
				setting_mode = 0;
				encoder_value =0;
				long_press_flag = 0;
				break; 
			}
			//按键判断
			if (encoder_value == 2 )
			{
				Seconds++;
				if(Seconds>59) Seconds =0;
				encoder_value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if (encoder_value == 1 )
			{
				Seconds--;
				if(Seconds>59) Seconds =59;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
				encoder_value = 0;
			}
			if ( encoder_value == 3)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
				setting_mode = 2;
				encoder_value =0;
				break; 
			}
		}
		/***秒设置模式 ,旋转滚轮调节秒，短按旋钮将setting mode置为2，进入分设置*******/

		/***minutes设置模式 ,旋转滚轮调节分，短按旋钮将setting mode置为3，进入小时设置*******/
		while(setting_mode == 2)
		{
			if (blink_count == 1)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			else if (blink_count == 20000)
			{
				TM1640_DisplayOriginalNum(4, show_nothing , 2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			encoder_value = ENCODER_READ();
			
			//退出设置模式
			if ( long_press_flag == 1)
			{
				setting_mode = 0;
				encoder_value =0;
				long_press_flag = 0;
				break; 
			}
			
			//按键判断
			if (encoder_value == 2 )
			{
				Minutes++;
				if(Minutes>59) Minutes =0;
				encoder_value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if (encoder_value == 1 )
			{
				Minutes--;
				if(	Minutes>59) Minutes =59;
				encoder_value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}

			if ( encoder_value == 3)
			{
				setting_mode = 3;
				encoder_value =0;
				break; 
			}
		}
		/***minutes设置模式 ,旋转滚轮调节分，短按旋钮将setting mode置为3，进入小时设置*******/
	
		/***hours设置模式 ,旋转滚轮调节小时，短按旋钮将setting mode置为0，进入运行模式*******/
		while(setting_mode == 3)
		{
           	//Write_Order_Lcd_1602(0x1 |0xC0);
			//Write_Order_Lcd_1602(0x0f);
			if (blink_count == 1)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			else if (blink_count == 20000)
			{
				TM1640_DisplayOriginalNum(1, show_nothing , 2);
			}
			else if (blink_count == 60000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			encoder_value = ENCODER_READ();
			//退出设置模式
   			if ( long_press_flag == 1)		
			{
				setting_mode = 0;
				encoder_value =0;
				long_press_flag = 0;
				break; 
			}
			//进入setting mode的Hours,
			if (encoder_value == 2 )
			{
				Hours++;
				if (Hours>23) Hours =0;
				encoder_value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if (encoder_value == 1 )
			{
				Hours--;
				if (Hours>23) Hours =23;
				encoder_value = 0;
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}

			if ( encoder_value == 3)
			{
				setting_mode = 5;
				encoder_value =0;
				break; 
			}
		}
		/***hours设置模式 ,旋转滚轮调节小时，短按旋钮将setting mode置为0，进入运行模式*******/
		
		
		/***亮度设置模式 ,旋转滚轮调节小时，短按旋钮将setting mode置为0，进入运行模式*******/
		while(setting_mode == 5)
		{
			if (blink_count == 1)
			{
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			else if (blink_count == 20000)
			{
				TM1640_Clear();
			}
			else if (blink_count == 40000)
			{
				blink_count = 0; 
			}
			blink_count ++;
			encoder_value = ENCODER_READ();
			
			if (encoder_value == 1 )
			{
				Brightness_level ++;
				encoder_value = 0;
				TM1640_SetBrightness((Brightness_level_t) (((Brightness_level)%8)+0x88));
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			if (encoder_value == 2 )
			{
				Brightness_level --;
				if(Brightness_level ==0){Brightness_level =7;}
				encoder_value = 0;
				TM1640_SetBrightness((Brightness_level_t) (((Brightness_level)%8)+0x88));
				TM1640_DisplayTime(Hours, Minutes,  Seconds);
			}
			//退出设置模式
			if(encoder_value ==3)
			{
				FLASH_Write(addr_brightness_data ,Brightness_level);
				setting_mode = 0;
				encoder_value =0;
				break;
			}
		}
		/***亮度设置模式 ,旋转滚轮调节小时，短按旋钮将setting mode置为0，进入运行模式*******/
	} //while(1)
} //main()


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


