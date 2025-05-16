/**
  ******************************************************************************
  * @file    1602lcd.c
  * @author  oscar
  * @version v0.0.1
  * @date    2025-05-1
  * @brief   该文件是针对STM32F10x的1602液晶屏驱动代码，主要用于初始化液晶屏GPIO端口，
  *          写入指令和数据，以及在液晶屏上显示字符串和数字。
  * 
  ******************************************************************************
  * @details 主要功能包括1602液晶屏的GPIO初始化、判忙检测、写指令和数据，以及在液晶屏上显示字符串和数字。
  *          通过读取液晶屏的状态来判断是否忙碌，并根据需要写入指令或数据。
  *          提供了在任意行、任意列显示字符串和数字的功能，并特别处理了与TM1640共用数据总线的情况。
  * 
  * @changelog
  * ------------v0.0.1   初始化液晶屏GPIO端口，实现指令和数据写入，显示字符串和数字功能   2025-05-02
  * 
  * Copyright (c) 2025-2025 oscar All rights reserved.
  ******************************************************************************
  */
#include "1602lcd.h"
#include "delay.h"
#include <stdio.h> // 用于 sprintf 函数

/**
  * @brief  Initializes the GPIO ports for the LCD1602 control and data lines.
  *         RS and RW are configured as push-pull outputs, and E is configured
  *         as a push-pull output. The data bus is configured as open-drain outputs.
  * @param  None
  * @retval None
  */
void Lcd_1602_GPIO_Config(void)
{
    GPIO_InitTypeDef  IO_Init;   
    RCC_APB2PeriphClockCmd(Lcd_1602_GPIO_RCC, ENABLE);//启动APB2总线 GPIO
    //RS控制线初始化 :  
    IO_Init.GPIO_Pin=RS_Lcd_1602_Pin; 
    IO_Init.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽模式           
    IO_Init.GPIO_Speed=GPIO_Speed_50MHz;        //GPIO_Speed_50MHz
    GPIO_Init(RS_Lcd_1602_GPIOPORT,&IO_Init); 	
	
    //RW控制线初始化 :  
    IO_Init.GPIO_Pin=RW_Lcd_1602_Pin; 
    IO_Init.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽模式           
    IO_Init.GPIO_Speed=GPIO_Speed_50MHz;        //GPIO_Speed_50MHz
    GPIO_Init(RW_Lcd_1602_GPIOPORT,&IO_Init); 		
	
    //E控制线初始化 :  
    IO_Init.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽模式           
    IO_Init.GPIO_Pin=E_Lcd_1602_Pin;            
    IO_Init.GPIO_Speed=GPIO_Speed_50MHz;        //GPIO_Speed_50MHz
    GPIO_Init(E_Lcd_1602_GPIOPORT,&IO_Init);   
 
    //8位数据总线初始化 : 开漏输出
	IO_Init.GPIO_Mode= GPIO_Mode_Out_OD;	    //开漏输出
    IO_Init.GPIO_Pin = LCD_1602_Data_Bus_Pin;
    IO_Init.GPIO_Speed=GPIO_Speed_50MHz;    //输入模式无需设置速度     
    GPIO_Init(LCD_1602_Data_Bus_GPIOPORT,&IO_Init); 

}


/**
  * @brief  Check if LCD1602 is busy (BF flag).
  *         This function can be executed before any write or read operation.
  *         If LCD1602 is not connected, this function will stuck in a loop.
  * @param  None
  * @retval None
  */
void LCD1602_IsBusy(void)  //1602液晶屏判忙函数
{
	u8 Busy_Dat;

    //8位数据总线初始化 : 上拉输入
	GPIO_InitTypeDef  IO_Init;
	IO_Init.GPIO_Mode=GPIO_Mode_IPU;	    //上拉输入
    IO_Init.GPIO_Pin= LCD_1602_Data_Bus_Pin;
   // IO_Init.GPIO_Speed=GPIO_Speed_50MHz;    //输入模式无需设置速度     
    GPIO_Init(LCD_1602_Data_Bus_GPIOPORT,&IO_Init); 
	GPIO_SetBits(LCD_1602_Data_Bus_GPIOPORT,LCD_1602_Data_Bus_Pin); //ODR输出1 选择上拉输入 
    RW_Lcd_1602  =  1; //1602 RW 引脚
    RS_Lcd_1602  =  0; //1602 RS 引脚		
	E_Lcd_1602   =  1; //1602 E  引脚	  
	
  	do
		{
		    E_Lcd_1602   =  1; //1602 E  引脚
			Busy_Dat = GPIO_ReadInputDataBit(LCD_1602_Data_Bus_GPIOPORT,GPIO_Pin_7);   //取P0数据
		    E_Lcd_1602   =  0; //1602 E  引脚 			
		}while(Busy_Dat);//DB7 = 1  忙   DB7 = 0  空闲
			
    //8位数据总线初始化 : 开漏输出
	IO_Init.GPIO_Mode= GPIO_Mode_Out_OD;	    //开漏输出
    IO_Init.GPIO_Pin = LCD_1602_Data_Bus_Pin;
    IO_Init.GPIO_Speed=GPIO_Speed_50MHz;    //输入模式无需设置速度     
    GPIO_Init(LCD_1602_Data_Bus_GPIOPORT,&IO_Init); 			
}

/**
 * @brief  Write a data byte to the LCD1602 display.
 * @param  Data_Dat: The 8-bit data to be written to the LCD1602.
 * @retval None
 * @note   This function writes a data byte to the LCD1602 data register.
 *         Before writing, it checks the busy flag using LCD1602_IsBusy().
 *         The function also includes a delay to prevent conflicts when 
 *         sharing the bus with TM1640, ensuring correct operation.
 * @attention Ensure the LCD1602 data bus pins are properly initialized 
 *            and configured before calling this function.
 */
void Write_Data_Lcd_1602(u8 Data_Dat)
{
	LCD1602_IsBusy();  //1602液晶屏判忙函数      
	E_Lcd_1602   =  0; //1602 E  引脚
    RW_Lcd_1602  =  0; //1602 RW 引脚
    RS_Lcd_1602  =  1; //1602 RS 引脚

    GPIO_Write(LCD_1602_Data_Bus_GPIOPORT,Data_Dat);        //写数据在总线
	E_Lcd_1602   =  1; //1602 E  引脚
	//Delay_ms(10);  //延迟  X_ms*1  这里延迟可以不用， 加上目的是解决TM1640 和1602总线复用导致的1640亮度自动变暗
	E_Lcd_1602   =  0; //1602 E  引脚
	GPIO_Write(LCD_1602_Data_Bus_GPIOPORT,0xffff);        //释放总线
   
}

/**
  * @brief  写入指令到1602液晶屏。
  *         该函数在执行任何数据写入或读取操作之前调用。
  *         如果1602液晶屏未连接，该函数将在判忙过程中陷入死循环。
  * @param  Order_Dat: 要写入的一字节指令数据。
  * @retval None
  * @note   该函数首先检查液晶屏是否忙碌，然后设置相应的控制引脚以写入指令。
  *         写入指令后，通过一个短暂的延迟来避免与TM1640总线复用时的冲突。
  *         最后释放数据总线。
  * @attention 确保在调用此函数之前已经正确初始化了液晶屏的GPIO端口。
  */
void Write_Order_Lcd_1602(u8 Order_Dat)//1602液晶屏写指令函数
{
	LCD1602_IsBusy();  //1602液晶屏判忙函数   
	E_Lcd_1602   =  0; //1602 E  引脚
	RW_Lcd_1602  =  0; //1602 RW 引脚
	RS_Lcd_1602  =  0; //1602 RS 引脚
	GPIO_Write(LCD_1602_Data_Bus_GPIOPORT,Order_Dat);        //写数据在总线
	E_Lcd_1602   =  1; //1602 E  引脚
	Delay_ms(10);  //延迟  X_ms*1  这里延迟可以不用， 加上目的是解决TM1640 和1602总线复用导致的1640亮度自动变暗 
	E_Lcd_1602   =  0; //1602 E  引脚
	GPIO_Write(LCD_1602_Data_Bus_GPIOPORT,0xffff);        //释放总线	
}

/**
 * @brief  Write a command byte to the LCD1602 display.
 * @param  Order_Dat: The 8-bit command to be written to the LCD1602.
 * @retval None
 * @note   This function writes a command byte to the LCD1602 instruction register.
 *         Before writing, it checks the busy flag using LCD1602_IsBusy().
 *         A delay is included to avoid conflicts with the TM1640, preventing 
 *         the TM1640 brightness from automatically dimming due to bus sharing.
 * @attention Ensure the LCD1602 data bus pins are properly initialized 
 *            and configured before calling this function.
 */
void Lcd_1602_Init(void)  //1602液晶屏初始化函数
{
	 Lcd_1602_GPIO_Config(); //1602液晶屏GPIO配置
	 //Delay_ms(15);	
     Write_Order_Lcd_1602(0X38); //设置16*2显示，5*7点阵，8位数据接口
	 //Delay_ms(5);
	 Write_Order_Lcd_1602(0X08);  //显示关闭
	 Write_Order_Lcd_1602(0X01);  //显示清屏
	 Write_Order_Lcd_1602(0X06); //显示光标移动设置
	 Write_Order_Lcd_1602(0X0C); //显示光标设置
}

/**
 * @brief  在LCD1602显示屏的指定位置写入多个字符数据。
 * @param  X_1602: 指定的行数，1表示第一行，2表示第二行。
 * @param  Y_1602: 指定的列数，作为起始点。
 * @param  P_1602: 字符数据的指针，指向要写入的数据。
 * @param  Count_1602: 要写入的字符数量。
 * @retval None
 * @note   该函数根据输入的行号和列号，在LCD1602显示屏的指定位置写入多个字符数据。
 *         它通过循环逐个写入数据，并在每次写入前更新列号Y_1602。
 *         如果X_1602为1，表示第一行，在原有列号基础上加上0x80；如果是2，表示第二行，则加上0xC0。
 *         函数使用Write_Order_Lcd_1602函数设置写入位置，使用Write_Data_Lcd_1602函数写入数据。
 *         P_1602指针在每次写入后递增，指向下一个要写入的字符数据。
 *         Y_1602在每次写入后递增，以便在下一次写入时更新列位置。
 * @attention 确保LCD1602数据总线引脚已经正确初始化并配置好，然后再调用此函数。
 */
void Display_Lcd_1602(u8 X_1602,u8 Y_1602,u8 *P_1602,u8 Count_1602)
{
	u8 i;		
	for(i=0;i<=Count_1602-1;i++)
	{
	   if(X_1602==1)
			 Y_1602 |=0x80;       //第一行    0X80 
		 else
			 Y_1602 |=0xC0;       //第二行 0X80   +0X40   =0XC0
		 
		Write_Order_Lcd_1602(Y_1602-1);
		Write_Data_Lcd_1602(*P_1602);//1602液晶屏写数据函数
		P_1602++;
		Y_1602++;		 
	}
//*****************************************************************
//修复硬件BUG，因为TM1640 输入 和1602的数据总线共用，TM1640需要推挽输出才能驱动，避免1602数据喷到1640时序导致1640不正常显示bug
//退出1602函数 就要把GPIO设置推挽输出	
    GPIO_InitTypeDef  IO_Init; 	
    IO_Init.GPIO_Mode=GPIO_Mode_Out_PP;        //推挽输出
    IO_Init.GPIO_Pin= LCD_1602_Data_Bus_Pin;
    IO_Init.GPIO_Speed=GPIO_Speed_50MHz;        
    GPIO_Init(LCD_1602_Data_Bus_GPIOPORT,&IO_Init); 
//*****************************************************************	
}

/**
 * @brief  在LCD1602显示屏的指定位置写入一个数字。
 * @param  X_1602: 指定的行数，1表示第一行，2表示第二行。
 * @param  Y_1602: 指定的列数，作为起始点。
 * @param  Number: 要写入的数字。
 * @param  Count_1602: 要显示的数字位数。
 * @retval None
 * @note   该函数根据输入的行号和列号，在LCD1602显示屏的指定位置写入一个数字的各个位。
 *         它首先将数字分解为各个位并存储在数组number1中。
 *         如果X_1602为1，表示第一行，在原有列号基础上加上0x80；如果是2，表示第二行，则加上0xC0。
 *         函数使用Write_Order_Lcd_1602函数设置写入位置，然后使用Write_Data_Lcd_1602函数逐位写入数字。
 *         数字的每一位通过加0x30转换为对应的ASCII码字符。
 *         Y_1602在每次写入后递增，以便在下一次写入时更新列位置。
 * @attention 确保LCD1602数据总线引脚已经正确初始化并配置好，然后再调用此函数。
 *            该函数假设Count_1602不超过8，否则可能会导致数组越界。
 */
void Display_Lcd_1602_Number(u8 X_1602, u8 Y_1602, u32 Number, u8 Count_1602)
{
    u8 i;
    u8 number1[8]; // 定义一个存储数字每一位的数组

    // 将数字分解为各个位并存储在数组中
    number1[0] = Number % 10;                      // 个位
    number1[1] = Number % 100 / 10;                // 十位
    number1[2] = Number % 1000 / 100;              // 百位
    number1[3] = Number % 10000 / 1000;            // 千位
    number1[4] = Number % 100000 / 10000;          // 万位
    number1[5] = Number % 1000000 / 100000;        // 十万位
    number1[6] = Number % 10000000 / 1000000;      // 百万位
    number1[7] = Number % 100000000 / 10000000;     // 千万位

    // 根据行号设置起始地址
    if (X_1602 == 1)
        Y_1602 |= 0x80;       // 第一行地址起始为0X80
    else
        Y_1602 |= 0xC0;       // 第二行地址起始为0XC0

    // 逐位写入数字到LCD1602
    for (i = 0; i < Count_1602; i++)
    {
        Write_Order_Lcd_1602(Y_1602 + i-1); // 设置写入位置
        Write_Data_Lcd_1602(0x30 + number1[Count_1602 - 1 - i]); // 写入数字的对应字符
    }

    //*****************************************************************
    // 修复硬件BUG，因为TM1640输入和1602的数据总线共用，TM1640需要推挽输出才能驱动。
    // 为了避免1602数据喷到1640时序导致1640不正常显示的bug，退出1602函数后要将GPIO设置为推挽输出。
    GPIO_InitTypeDef IO_Init;
    IO_Init.GPIO_Mode = GPIO_Mode_Out_PP;        // 设置为推挽输出
    IO_Init.GPIO_Pin = LCD_1602_Data_Bus_Pin;    // 选择对应引脚
    IO_Init.GPIO_Speed = GPIO_Speed_50MHz;       // 设置输出速度
    GPIO_Init(LCD_1602_Data_Bus_GPIOPORT, &IO_Init);
    //*****************************************************************
}



/**
 * @brief  在LCD1602显示屏的指定位置以HH:MM:SS格式显示时间。
 * @param  X_1602: 指定的行数，1表示第一行，2表示第二行。
 * @param  Y_1602: 指定的列数，作为起始点。
 * @param  Hours: 要显示的小时数。
 * @param  Minutes: 要显示的分钟数。
 * @param  Seconds: 要显示的秒数。
 * @retval None
 * @note   该函数根据输入的行号和列号，在LCD1602显示屏的指定位置以"HH:MM:SS"格式显示时间。
 *         它首先将时间格式化为字符串并存储在timeBuffer数组中。
 *         如果X_1602为1，表示第一行，在原有列号基础上加上0x80；如果是2，表示第二行，则加上0xC0。
 *         函数使用Write_Order_Lcd_1602函数设置写入位置，然后使用Write_Data_Lcd_1602函数写入格式化后的时间字符串。
 *         Y_1602在每次写入后递增，以便在下一次写入时更新列位置。
 * @attention 确保LCD1602数据总线引脚已经正确初始化并配置好，然后再调用此函数。
 *            该函数假设输入的时间值是有效的，并且总长度不超过8个字符（不包括结束符\0）。
 */
void Display_Time_LCD1602(u8 X_1602, u8 Y_1602, u8 Hours, u8 Minutes, u8 Seconds) {
    char timeBuffer[10]; // 缓冲区，用于存储时间字符串（包含 \0）
    
    // 将时间格式化为 "HH-MM-SS"
    sprintf(timeBuffer, "%02d:%02d:%02d", Hours, Minutes, Seconds);

    // 调用 Display_Lcd_1602 函数显示
    Display_Lcd_1602(X_1602, Y_1602, (u8*)timeBuffer, 8); // 显示时间（长度为8）
}
