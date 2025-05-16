 /**
  ******************************************************************************
  * @file    main.c
  * @author  oscar
  * @version V0.1.0
  * @date    
  * @brief 
  * 
  * 1. achieve the function of keypad and display the time on the LCD1602
  * 2. uing the charactor binking to indicate the setting mode
  * 3. using the keypad to adjust the time
  * @next
  * uing flash to store and recover  the time 
  *        
  ******************************************************************************
  * @attention
  
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */



#include "stm32f10x.h"   
//#include "sys.h"
//#include "led.h"
#include "delay.h"
#include "key.h"
#include "1602lcd.h"
#include "matrix_keypad.h"

void PC_PA_13_14_15_Gpio(void);
void time_add(u8* Hours,u8* Minutes,u8* Seconds);
uint8_t Hours, Minutes, Seconds;
uint16_t loops_of_per_secend =0; //自动走时时间的计数器
uint8_t  setting_mode = 0;         //0 运行模式，1 设置秒，2 设置分，3 设计小时
uint8_t Key_Value;                 //按键值
uint16_t blink_count = 0;           //闪烁计数器
int main(void)
{
	RCC_Configuration();
	//lcd1602初始化
	Lcd_1602_GPIO_Config();
	Lcd_1602_Init();
	Display_Lcd_1602(1,1,(u8*)("2024-12-15 Wed.  "),16);
    Display_Lcd_1602(2,1,(u8*)("hour:min:sec        "),16);
	Display_Lcd_1602(2,1,(u8*)("                    "),16);
	//矩阵键盘初始化
	Keypad_Init();
	
	

	while(1)
	{
#if 1
		Key_Value =Keypad_Scan();

        Display_Time_LCD1602(2, 1,Hours, Minutes, Seconds);
		//setting_mode  0        1       2       3       5 
 		//             运行   调节秒   调节分  调节时 调节亮度
		if(setting_mode == 0)
		{
		
			loops_of_per_secend++;
			if(loops_of_per_secend >=10)
			{
				loops_of_per_secend =0;				
				Seconds++;	
				time_add(&Hours,&Minutes,&Seconds);
				Display_Time_LCD1602(2, 1,Hours, Minutes, Seconds);
			}
		}

	   //按动K13进入setting mode
        if (Key_Value == 13)
        {
            setting_mode = 1;
			Key_Value =0;
        }
		
        //标志位setting mode==1,然后按一次方向键，进入设置秒模式，将setting mode置为2
		while(setting_mode == 1)
		{
//			Write_Order_Lcd_1602(0x7 |0xC0);
//			Write_Order_Lcd_1602(0x0f);
			
			//闪烁指示位置，显示刷新
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
			
			//退出设置模式
			Key_Value = Keypad_Scan();
			if(Key_Value ==13)
			{
				Display_Lcd_1602_Number(2,7,Seconds,2);
				setting_mode = 0;
				Key_Value =0;
				break;
			}
			//按键判断
			if (Key_Value == 4 )
			{
				Seconds++;
				Key_Value = 0;
				Display_Lcd_1602_Number(2,7,Seconds,2);
			}
			while(Key_Value&0x80)
			{
				Seconds++;
				Display_Lcd_1602_Number(2,7,Seconds,2);
				Key_Value = 0;	
			}

				
			if (Key_Value == 12 )
			{
				Seconds--;
				Display_Lcd_1602_Number(2,7,Seconds,2);
				Key_Value = 0;
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
//			Write_Order_Lcd_1602(0x4 |0xC0);
//			Write_Order_Lcd_1602(0x0f);
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
			Key_Value = Keypad_Scan();
			
			//退出设置模式
			if(Key_Value ==13)
			{
				Display_Lcd_1602_Number(2,4,Minutes,2);
				setting_mode = 0;
				Key_Value =0;
				break;
			}
			
			//按键判断
			if (Key_Value == 4 )
			{
				Minutes++;
				Key_Value = 0;
				Display_Lcd_1602_Number(2,4,Minutes,2);
			}
			if (Key_Value == 12 )
			{
				Minutes--;
				Key_Value = 0;
				Display_Lcd_1602_Number(2,4,Minutes,2);
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
//            Write_Order_Lcd_1602(0x1 |0xC0);
//			Write_Order_Lcd_1602(0x0f);
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
			Key_Value = Keypad_Scan();
			//退出设置模式
			if(Key_Value ==13)
			{
				Display_Lcd_1602_Number(2,1,Hours,2);
				setting_mode = 0;
				Key_Value =0;
				break;
			}
			//进入setting mode的Hours,
			if (Key_Value == 4 )
			{
				Hours++;
				Key_Value = 0;
				Display_Lcd_1602_Number(2,1,Hours,2);
			}
			if (Key_Value == 12 )
			{
				Hours--;
				Key_Value = 0;
				Display_Lcd_1602_Number(2,1,Hours,2);
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
#endif 
	}//while

 
}//main

void PC_PA_13_14_15_Gpio(void) //
{

	  //rtc作为io，需要先取消rtc备用纽扣电池配置好后再装电池或不装
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE );
	  	  //RCC_APB2Periph_AFIO IO功能复用AFIO 时钟 改变默认功能 恢复IO口功能
    PWR_BackupAccessCmd( ENABLE );/* 允许修改RTC和后备寄存器*/
    RCC_LSEConfig( RCC_LSE_OFF ); /* 关闭外部低速时钟,PC14+PC15可以用作普通IO*/
    BKP_TamperPinCmd(DISABLE);  /* 关闭入侵检测功能,PC13可以用作普通IO*/

	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //恢复PA13  PA14  PA15 IO功能，默认位jtag swd下载功能
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    PWR_BackupAccessCmd(DISABLE);/* 禁止修改RTC和后备寄存器*/
    //BKP_ITConfig(DISABLE);       /* 禁止TAMPER 中断*/




}

void time_add(u8* Hours,u8* Minutes,u8* Seconds)
{
	if(*Seconds >=60)
	{
		*Seconds=0;
		(*Minutes)++;
		if(*Minutes>=60)
		{
			*Minutes =0;
			(*Hours)++;
			if(*Hours>=24)
			{
				*Hours =0;
			}
		}
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


