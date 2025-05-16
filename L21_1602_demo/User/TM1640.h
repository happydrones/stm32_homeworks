#ifndef __TM1640_H
#define __TM1640_H	 


#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>

#define TM1640_GPIOPORT    	GPIOG	       //定义IO接口
#define TM1640_DIN	        GPIO_Pin_6	 //定义IO接口
#define TM1640_SCLK	        GPIO_Pin_7	 //定义IO接口

#define TM1640_GPIO_RCC     RCC_APB2Periph_GPIOG   //定义IO 时钟


void TM1640_Init(void);//初始化
void TM1640_Start(void);
void TM1640_Stop(void);
void TM1640_Write_Byte(u8 TM1640_Dat);
void Disp_Smg_Number_TM1640(u8 x_smg,u8 count_smg,u32 number,u8 Point);
void Disp_Smg_Number_TM1640_MODE_0X44(u8 x_smg,u8 count_smg,u32 number,u8 Point);//固定地址模式实现在数码管上显示任意十进制数
void TM1640_HG_Display(u8 X_SMG);//TM1640 任意位置显示“-”
void TM1640_Ld_Display(u8 X_SMG);//亮度 模式 数码管显示界面 Ld-
#endif

