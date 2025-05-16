#include "sys.h"
uint8_t Pwm_Duty = 0;

uint16_t Pins[] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,
                       GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7,
                       GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11,
                       GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15};

uint8_t led_number;
uint8_t Duty = 100;
uint32_t pins = 0x0001;
uint8_t show_number =0;

/*
* @brief  主要是用来测试GPIO输出的程序，首先是开启GPIOA时钟，
*         然后配置GPIO_A pin0为推挽输出模式，接着循环点亮LED，
*         然后延时1秒，然后熄灭LED，再延时1秒，循环往复。
*/
int main(void)
{
	delay_10us(100);
	TM1640_Init();
	delay_10us(1000);
	TM1640_Display_Init();
	delay_10us(1000);
	
	
	
	while(1)
	{
//		TM1640_Init();
//		TM1640_SetBrightness( Brightness_level_2);
//		delay_ms(1000);
//		TM1640_Display_Init();
//		TM1640_SetBrightness( Brightness_level_6);
//		delay_ms(100);
		TM1640_DisplayNumber(1,4,show_number,1);
		
       

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


