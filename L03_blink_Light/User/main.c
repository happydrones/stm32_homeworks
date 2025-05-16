/**
  ******************************************************************************
  * @file    main.c
  * @author  oscar
  * @version V0.0.1
  * @date    12-November-2024
  * @brief   THis is file achieves the blinking of LEDs using the STM32F103C8T6 MCU.
  ******************************************************************************
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "delay.h"       // 延时函数头文件

void PC_PA_13_14_15_Gpio(void);//设置 PA 13 14 15   PC 13 14 15 io功能

int main(void)
{
    //PC_PA_13_14_15_Gpio(); //设置 PA 13 14 15   PC   13 14 15 io功能	
    //GPIO输出操作步骤
	//第一步：设置时钟   
	
//第一题
#if 0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB 
                          |RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD
                          |RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOF 
                          |RCC_APB2Periph_GPIOG, ENABLE);//启动APB2总线 PA组IO总时钟
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //恢复PA13  PA14  PA15 IO功能，默认位jtag swd下载功能
	//第二步：设置GPIO工作模式
GPIO_InitTypeDef  GPIO_InitStruct;

//GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;                     //选择第 0 位IO 
GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;                     //选择第 0 位IO 	
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //选择推挽输出
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //选择输出速度  50MHz
	
GPIO_Init(GPIOA, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度	
GPIO_Init(GPIOB, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
GPIO_Init(GPIOC, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
GPIO_Init(GPIOD, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
GPIO_Init(GPIOE, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度  
GPIO_Init(GPIOF, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
GPIO_Init(GPIOG, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
	 while(1)
	 {
       GPIO_SetBits(GPIOA, GPIO_Pin_0);   //PA0输出高电平
       GPIO_SetBits(GPIOB, GPIO_Pin_0);   //PB0输出高电平
       GPIO_SetBits(GPIOC, GPIO_Pin_0);   //PC0输出高电平
       GPIO_SetBits(GPIOD, GPIO_Pin_0);   //PD0输出高电平
       GPIO_SetBits(GPIOE, GPIO_Pin_0);   //PE0输出高电平
       GPIO_SetBits(GPIOF, GPIO_Pin_0);   //PF0输出高电平
       GPIO_SetBits(GPIOG, GPIO_Pin_0);   //PG0输出高电平
       delay_ms(1000);                    //延时1秒
       GPIO_ResetBits(GPIOA, GPIO_Pin_0); //PA0输出低电平
       GPIO_ResetBits(GPIOB, GPIO_Pin_0); //PB0输出低电平
       GPIO_ResetBits(GPIOC, GPIO_Pin_0); //PC0输出低电平
       GPIO_ResetBits(GPIOD, GPIO_Pin_0); //PD0输出低电平
       GPIO_ResetBits(GPIOE, GPIO_Pin_0); //PE0输出低电平
       GPIO_ResetBits(GPIOF, GPIO_Pin_0); //PF0输出低电平 
       GPIO_ResetBits(GPIOG, GPIO_Pin_0); //PG0输出低电平
       delay_ms(1000);                    //延时1秒
	 }
#endif 
   
 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //恢复PA13  PA14  PA15 IO功能，默认位jtag swd下载功能
	//第二步：设置GPIO工作模式
	GPIO_InitTypeDef  GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_All;       //选择第 0 位IO                   //选择第 0 位IO 	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //选择推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //选择输出速度  50MHz
		
	GPIO_Init(GPIOA, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度	
	GPIO_Write(GPIOA, 0xff);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度	)
  while(1)
  {

	      GPIO_ResetBits(GPIOA, GPIO_Pin_0); //PA0输出低电平
		  delay_ms(100);
		  GPIO_SetBits(GPIOA, GPIO_Pin_0);   //PA0输出高电平
		  delay_ms(100);                    //延时1秒
  }

}


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


