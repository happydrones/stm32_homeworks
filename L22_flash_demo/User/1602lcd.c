#include "sys_config.h"
#include "1602lcd.h"
#include "delay.h"
#include <stdio.h> // 用于 sprintf 函数

/**********************************************************************
*                        单片机IO口位定义
**********************************************************************
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
  *         this function can be executed before any write or read operation.
  *         if lcd is not connected, this function will stuck in a loop.
  * @param  None
  *   
  * @retval Node
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
/*********************************************************************
*函数名称： Write_Order_Lcd_1602
*函数功能：1602液晶屏写指令函数
*函数调用：Write_Order_Lcd_1602(uint8 Order_Dat);
*参数列表：uint8 Order_Dat  要写入的一字节指令数据
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/
void Write_Order_Lcd_1602(u8 Order_Dat)//1602液晶屏写指令函数
{
	LCD1602_IsBusy();  //1602液晶屏判忙函数   
	E_Lcd_1602   =  0; //1602 E  引脚
	RW_Lcd_1602  =  0; //1602 RW 引脚
	RS_Lcd_1602  =  0; //1602 RS 引脚
	GPIO_Write(LCD_1602_Data_Bus_GPIOPORT,Order_Dat);        //写数据在总线
	E_Lcd_1602   =  1; //1602 E  引脚
	delay_ms(10);  //延迟  X_ms*1  这里延迟可以不用， 加上目的是解决TM1640 和1602总线复用导致的1640亮度自动变暗 
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
/*********************************************************************
*函数名称： Display_Lcd_1602
*函数功能：1602液晶屏在任意行，任意列，一个任意位数的字符串函数
*函数调用：Display_Lcd_1602(uint8 X_1602,uint8 Y_1602,uint8 *P_1602,uint8 Count_1602);
*参数列表：
            X_1602  行坐标 取值范围  1-2
            Y_1602  列坐标 取值范围  1-16
            *P_1602 字符串指针  要求字符串不能高过16位  取值范围 1-16
            Count_1602  字符串位数，就是我们要写几个字符 取值范围 1-16
 
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/

//Display_Lcd_1602(1,1," Easy Board 51  ",16); 	
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

/*********************************************************************
*函数名称： Display_Lcd_1602_Number
*函数功能：1602液晶屏在任意行，任意列，写一个任意8位以内位的十进制数
*函数调用：Display_Lcd_1602_Number(uint8 X_1602,uint8 Y_1602,uint32 Number,uint8 Count_1602);
*参数列表：
            X_1602  行坐标 取值范围  1-2
            Y_1602  列坐标 取值范围  1-16
            Number  十进制数字  取值范围 0-99999999
            Count_1602  几位数， 取值范围 1-8
 
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/

void Display_Lcd_1602_Number(u8 X_1602,u8 Y_1602,u32 Number,u8 Count_1602)
{
	u8 i;	
	u8 number1[8]; //定义一个存储八位数的每一位的数字用的数组

	number1[0] = Number % 10;                      //个        
	number1[1] = Number % 100 / 10;                //十   
	number1[2] = Number % 1000 / 100;              //百
	number1[3] = Number % 10000 / 1000;            //千
	number1[4] = Number % 100000 / 10000;          //万 
	number1[5] = Number % 1000000 / 100000;        //十万
	number1[6] = Number % 10000000 / 1000000;      //百万 
	number1[7] = Number % 100000000 / 10000000;     //千万 	
	
	   if(X_1602==1)
			 Y_1602 |=0x80;       //第一行    0X80 
		 else
			 Y_1602 |=0xC0;       //第二行 0X80   +0X40   =0XC0	
		 
	for(i=0;i<=Count_1602-1;i++)
	{
		Write_Order_Lcd_1602(Y_1602-1);
	    Write_Data_Lcd_1602(0x30+number1[Count_1602-1-i]);//1602液晶屏写数据函数
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



void Display_Time_LCD1602(u8 X_1602, u8 Y_1602, u8 Hours, u8 Minutes, u8 Seconds) {
    char timeBuffer[10]; // 缓冲区，用于存储时间字符串（包含 \0）
    
    // 将时间格式化为 "HH-MM-SS"
    sprintf(timeBuffer, "%02d:%02d:%02d", Hours, Minutes, Seconds);

    // 调用 Display_Lcd_1602 函数显示
    Display_Lcd_1602(X_1602, Y_1602, (u8 *)timeBuffer, 8); // 显示时间（长度为8）
}
