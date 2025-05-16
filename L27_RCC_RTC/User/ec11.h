#ifndef __ENCODER_H
#define __ENCODER_H	 
#include "sys_config.h"
#include "delay.h"

#define Encoder_GPIO_RCC      RCC_APB2Periph_GPIOE    //定义IO 时钟

#define Encoder_L_GPIOPORT    GPIOE		//定义IO接口组
#define Encoder_L_Pin         GPIO_Pin_6	//定义IO接口

#define Encoder_R_GPIOPORT	  GPIOE		//定义IO接口组
#define Encoder_R_Pin	        GPIO_Pin_5	//定义IO接口

#define Encoder_Key_GPIOPORT	GPIOE		//定义IO接口组
#define Encoder_Key_Pin	      GPIO_Pin_4	//定义IO接口

#define Encoder_R	        GPIO_ReadInputDataBit(Encoder_R_GPIOPORT,Encoder_R_Pin)      //GPIO输入 正转
#define Encoder_L	        GPIO_ReadInputDataBit(Encoder_L_GPIOPORT,Encoder_L_Pin)      //GPIO输入 反转
#define Encoder_Key	      GPIO_ReadInputDataBit(Encoder_Key_GPIOPORT,Encoder_Key_Pin)	 //GPIO输入 独立按键 
 
void Encoder_EC11_Init(void);//初始化
u8 Encoder_EC11_Key(void);
		 				    
#endif
