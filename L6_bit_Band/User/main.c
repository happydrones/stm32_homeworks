/**
  ******************************************************************************
  * @file    main.c
  * @author  oscar
  * @version V0.0.1
  * @date    12-November-2024
  * @brief   THis is file achieve the function of bit banding.
  ******************************************************************************
  * @attention
  * 首先使用位带操作控制的时候，仍然需要GPIOA的时钟使能， 否则无法工作
  * 
  ******************************************************************************
  */
#include "stm32f10x.h"   
#include "sys.h"
#include "led.h"
#include "delay.h"
#include "Keypad.h"

//使用GPIO进行置位时所用到的数组
uint16_t pins[] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,\
                       GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7,
                       GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11,
                       GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15};

uint8_t led_number;
					   
					   

					   
					   
/*
* @brief  通过位带操作控制GPIOA的LED灯，实现流水灯效果。
*         
*         
*/
int main(void)
{
	LED_Init(GPIOA);

	
	while(1)
	{

        #if 0
		//流水灯的功能
		// 通过for循环实现流水灯效果
        for ( led_number = 0; led_number < 8; led_number++) 
        {
            LED_On(GPIOA, pins[led_number]);  // 点亮当前pin
            delay_s(1);       // 延时500毫秒
            LED_Off(GPIOA, pins[led_number]);  // 熄灭当前pin 
		}
		led_number= 0;

        #elif 1
		//通过位带操作控制GPIOA的LED灯，实现流水灯效果
        
        for(uint8_t i=0;i<16;i++)
		{
			PAout(i)=0;
			delay_ms(200);
			PAout(i)=1;			
		}
		
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


