/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 主函数入口，实现了基于STM32F10x的时间显示与设置逻辑
  *                   - 显示日期与时间（年-月-日/时:分:秒）
  *                   - 通过旋转编码器进入设置模式，逐级设置秒、分、小时
  *                   - 长按旋钮可退出设置模式回到正常运行模式
  *
  * 使用外设与功能：
  * - LCD 1602 显示屏
  * - TM1640 数码管
  * - 旋转编码器，用于时间设置
  * - delay 等延时函数
  *
  * 主要全局变量：
  * - Hours, Minutes, Seconds：时、分、秒
  * - loops_of_per_secend：辅助计数，用于每 20 次循环增加一秒
  * - setting_mode：当前设置模式(0 表示正常模式, 1~3 表示设置秒、分、时)
  * - blink_count：设置模式下闪烁变量
  * - encoder_value：记录旋转编码器的操作(1 逆转，2 正转，3 短按)
  *
  * @note
  *  - 使用Keil MDK工程进行编译
  *  - 需要根据硬件原理图配置对应的引脚与初始化函数
  *  - 使用前需在 stm32f10x_conf.h 中使能相应外设驱动
  *
  * @attention
  *  - 本例程涉及时钟中断或延时函数应仔细确认系统时钟频率
  *  - 旋转编码器相关的读取函数需结合外部中断或轮询方式
  *
  * @date  2024-12-15
  * @version 1.0
  ******************************************************************************
  */
#include "stm32f10x.h"   
#include "delay.h"
#include "pwm.h"
//#include "matrix_keypad.h"
#include "led.h"
#include "1602lcd.h" 
#include "encoder.h"
#include "tm1640.h"

uint8_t Hours, Minutes, Seconds;
uint16_t loops_of_per_secend =0; //自动走时时间的计数器
uint8_t  setting_mode = 0;         //0 运行模式，1 设置秒，2 设置分，3 设计小时
uint16_t blink_count = 0;
uint8_t encoder_value;
uint8_t number = 0;
uint8_t show_number =0; 
int main(void)
{
	//初始化lcd屏幕
	Lcd_1602_GPIO_Config();
	Lcd_1602_Init();
	//Display_Lcd_1602(1,1,(u8*)("test.lcd"),8);
	Display_Lcd_1602(1,1,(u8*)("2024-12-15 Wed.  "),16);
    Display_Lcd_1602(2,1,(u8*)("hour:min:sec      "),16);
	ENCODER_Init();
	Display_Lcd_1602(2,9,(u8*)("              "),4);
	TM1640_Display_Init();
	TM1640_DisplayNumber(1,3,show_number,1);

	while(1)	
	{
		
#if 0
/***********************第一题******************/
		encoder_value =ENCODER_READ();
		if(encoder_value ==1)
		{
			show_number= show_number-encoder_count;
			encoder_count =0;
		}
		if(encoder_value ==2)
		{
			show_number= show_number+encoder_count;
			encoder_count =0;
		}
		if(encoder_value ==3)
		{
			show_number =0;
		}
		if(encoder_value !=0 )
		{
			TM1640_DisplayNumber(1,3,show_number,1);
		}
		/***********************第一题******************/
#endif
#if 1
/***********************第2题******************/
   /************************运行时的主循环***************************/
		encoder_value =ENCODER_READ();
		Display_Lcd_1602_Number(2,14,encoder_value,2);

		Display_Time_LCD1602(2,1,Hours,Minutes,Seconds);
		if(setting_mode == 0)
		{
		
			loops_of_per_secend++;
			if(loops_of_per_secend >=20)
			{	
				Seconds++;
				Display_Time_LCD1602(2, 1,Hours, Minutes, Seconds);	
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
			
			}
		}

	   //按动旋转编码器进入setting mode，秒设置
        if (encoder_value == 3)
        {
            setting_mode = 1;
			encoder_value =0;
        }
   /************************运行时的主循环***************************/
		
		
		
    /***秒设置模式 ,旋转滚轮调节秒，短按旋钮将setting mode置为2，进入分设置*******/
		while(setting_mode == 1)
		{
    	   	//Write_Order_Lcd_1602(0x7 |0xC0);
			//Write_Order_Lcd_1602(0x0f);
			//显示刷新
			if (blink_count == 1)
			{
				Display_Lcd_1602(2,7,(u8*)"    ",2);
			}
			else if (blink_count == 20000)
			{
				Display_Lcd_1602_Number(2,7,Seconds,2);
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
				Display_Lcd_1602_Number(2,7,Seconds,2);
			}
			if (encoder_value == 1 )
			{
				Seconds--;
				if(Seconds>59) Seconds =59;
				Display_Lcd_1602_Number(2,7,Seconds,2);
				encoder_value = 0;
			}
			if ( encoder_value == 3)
			{
				Display_Lcd_1602_Number(2,7,Seconds,2);
				setting_mode = 2;
				encoder_value =0;
				break; 
			}
		}
	/***秒设置模式 ,旋转滚轮调节秒，短按旋钮将setting mode置为2，进入分设置*******/

	/***minutes设置模式 ,旋转滚轮调节分，短按旋钮将setting mode置为3，进入小时设置*******/
		while(setting_mode == 2)
		{
			//Write_Order_Lcd_1602(0x4 |0xC0);
			//Write_Order_Lcd_1602(0x0f);
			if (blink_count == 1)
			{
				Display_Lcd_1602(2,4,(u8*)"    ",2);
			}
			else if (blink_count == 20000)
			{
				Display_Lcd_1602_Number(2,4,Minutes,2);
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
				Display_Lcd_1602_Number(2,4,Minutes,2);
			}
			if (encoder_value == 1 )
			{
				Minutes--;
				if(	Minutes>59) Minutes =0;
				encoder_value = 0;
				Display_Lcd_1602_Number(2,4,Minutes,2);
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
				Display_Lcd_1602(2,1,(u8*)"    ",2);
			}
			else if (blink_count == 20000)
			{
				Display_Lcd_1602_Number(2,1,Hours,2);
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
				Display_Lcd_1602_Number(2,1,Hours,2);
			}
			if (encoder_value == 1 )
			{
				Hours--;
				if (Hours>23) Hours =23;
				encoder_value = 0;
				Display_Lcd_1602_Number(2,1,Hours,2);
			}

			if ( encoder_value == 3)
			{
				setting_mode = 0;
				encoder_value =0;
				break; 
			}
		}
	/***hours设置模式 ,旋转滚轮调节小时，短按旋钮将setting mode置为0，进入运行模式*******/

#endif
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


