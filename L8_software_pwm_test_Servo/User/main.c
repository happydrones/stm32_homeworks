#include "stm32f10x.h"   
#include "sys_config.h"
#include "led.h"
#include "delay.h"
#include "pwm.h"
#include "1602lcd.h"
#include "encoder.h"

const uint8_t frequency_rate =10;
uint8_t angle=5;
uint8_t key_value=0;
int main(void)
{
	RCC_Configuration();
	//init_encoder
	ENCODER_Init();
	//初始化lcd屏幕
	Lcd_1602_Init();
	Display_Lcd_1602(1,1,"test_Servo   wsh  ",16);
	Display_Lcd_1602(2,1,"turn_en11       ",16);
	Display_Lcd_1602_Number(2,14,angle,2);
	PC_PA_13_14_15_Gpio();//设置 PA 13 14 15   PC 13 14 15 io功能
	LED_GPIO_Init();  // gpio输出 IO配置
	 while(1)
	 {
		 key_value =ENCODER_READ();
		 //角度增加
		 while(1)
		 {
			 key_value =ENCODER_READ();
			 if(key_value!=0)
			 {
				 break;
			 }
			 GPIO_Out_PWM(GPIOA,GPIO_Pin_15,50,angle);
		 }
		 if(key_value==1)
		 {
			 angle++;
			 if(angle>10)
			 {
				 angle =5;
			 }
			 Display_Lcd_1602_Number(2,14,angle,2);
			 
		 }
		 //角度减小
		 if(key_value==2)
		 {
			 angle--;
			 if(angle<5)
			 {
				 angle =10;
			 }
			 Display_Lcd_1602_Number(2,14,angle,2);
			 
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


