#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "delay.h"

#define  Key_up (GPIOC->IDR&GPIO_Pin_0)
#define  Key_down (GPIOC->IDR&GPIO_Pin_2)

void PC_PA_13_14_15_Gpio(void); //设置 PA 13 14 15   PC 13 14 15 io功能
uint8_t i=0;

int main(void)
{
	 RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // 使能AFIO时钟

    // 2. 禁用JTAG，禁用SWD
    AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG); // 清除SWJ_CFG位
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE ; // disable SWD and JTAG
	//PC_PA_13_14_15_Gpio(); //设置 PA 13 14 15   PC 13 14 15 io功能
	 RCC->APB2ENR |=((uint32_t)0x00000004); //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 GPIOA->CRL	=0x33333333;	   		    //  GPIO_InitTypeDef GPIO_init_struct;
	 GPIOA->CRH	=0x33333333;				//	GPIO_init_struct.GPIO_Mode=GPIO_Mode_Out_PP;
	 GPIOA->BSRR=0xFFFFFFFF;				//	GPIO_init_struct.GPIO_Pin =GPIO_Pin_0;
											//	GPIO_init_struct.GPIO_Speed =GPIO_Speed_50MHz;
											//	GPIO_Init(GPIOC,&GPIO_init_struct);
	
	//公共按键PC7配置为下拉输入初始化
	RCC->APB2ENR |=((uint32_t)0x00000010); //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIOC->CRL &= ~(0xF << (7 * 4));  // 清除 MODE 和 CNF
	GPIOC->CRL |= (0x7 << (7 * 4));  // 设置 CNF=10, MODE=00 (上拉输入)
	GPIOC->BRR |=(0x1 << 7);         //设置PC7为0
	//配置PC0 与PC2为上拉输入模式
	GPIOC->CRL	 |=0x00000808;
	GPIOC->CRL   &=0xFFFFF8F8;
	GPIOC->ODR   |=0x00000005;
	
	 
	while(1)	 
	{
		/**************使用寄存器操作实现流水灯******************************
		for(uint8_t i=0;i<=16;i++)
		{
			GPIOA->BRR = (1 << i); // 将第 i 位复位为低电平
            delay_ms(80);
			GPIOA->BSRR = (1 << i); // 将第 i 位设置为高电平
            delay_ms(80); // 调整延迟，使LED变化可见
             // 熄灭第 i 个引脚
            
		}
		**************使用寄存器操作实现流水灯******************************/
		// **************使用按键实现亮灯平移******************************
			if(Key_up==0)
			{
				delay_ms(10);
				if(0 ==Key_up)
				{
					while(Key_up ==0);
					i++;
					if(i>15)
					{
						i =0;
					}

					
				}
			}
		    if(Key_down==0)
			{
				delay_ms(10);
				if(0 ==Key_down)
				{
					while(Key_down ==0);
					i--;
					if(i>15)
					{
						i =15;
					}

					
				}
			}
			GPIOA->ODR =~(0x000000001<<i);
		//***************使用按键实现亮灯平移******************************//
	}


}





/*********************************************************************
*函数名称：PC_PA_13_14_15_Gpio
*函数功能：设置 PA 13 14 15   PC 13 14 15 为io功能
*函数调用：PC_PA_13_14_15_Gpio();
*参数列表：无
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/

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


