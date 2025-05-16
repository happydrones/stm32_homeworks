#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "sys.h"
#include "led.h"
#include "delay.h"
#include "pwm.h"
#include "esc.h"
#include "keypad.h"
#include "tm1640.h"


void PC_PA_13_14_15_Gpio(void); //设置 PA 13 14 15   PC 13 14 15 io功能
uint8_t angle=30;
uint8_t key_value;
/*
* @brief  主要是用来测试GPIO输出的程序，首先是开启GPIOA时钟，
*         然后配置GPIO_A pin0为推挽输出模式，接着循环点亮LED，
*         然后延时1秒，然后熄灭LED，再延时1秒，循环往复。
*/
int main(void)
{
//	TM1640_Init();
//	Keypad_Init();
//	PC_PA_13_14_15_Gpio();
//	GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_15|GPIO_Pin_14;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	TM1640_Display_Init();
//	while(1)
//	{
//		TM1640_DisplayNumber(1, 4, (angle-25)*18/5,1);
//		key_value = Keypad_Scan();
//		Pwm_generate(GPIOA,GPIO_Pin_All,50,angle,5);
//		if(4 == key_value)
//		{
//			if(angle<80)
//			{
//			angle=angle+5;
//			TM1640_DisplayNumber(1, 4, (angle-30)*18/5,1);
//			key_value=0;
//			delay_ms(10);
//			}
//		}
//		if(12 ==key_value)
//		{
//			if(angle>=25)
//			{
//			angle=angle-5;
//			TM1640_DisplayNumber(1, 3, (angle-30)*18/5,1);
//		    key_value=0;
//			}	
//		}
//		
//	}
	PC_PA_13_14_15_Gpio();
	while(1)
	{
		
	}



}


void PC_PA_13_14_15_Gpio(void) //设置 PA 13 14 15   PC 13 14 15 io功能
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
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);
	delay_ms(200);
	GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);
	delay_ms(200);
	GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);
	delay_ms(200);
	GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);
	delay_ms(200);
	GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);	
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


