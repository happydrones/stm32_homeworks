#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H	

#include "stm32f10x.h"	 

#define KEY_UP_EXTI_GPIO_RCC  		RCC_APB2Periph_GPIOC //GPIOC
#define KEY_UP_EXTI_GPIO_PORT  	    GPIOC
#define KEY_UP_GPIO_PORTSOURCE      GPIO_PortSourceGPIOC
#define KEY_UP_EXTI_GPIO_PIN   		GPIO_Pin_0
#define KEY_UP_EXTI_LINE          	EXTI_Line0
#define KEY_UP_GPIO_PINSOURCE       GPIO_PinSource0
#define KEY_UP_EXTI_IRQN  			EXTI0_IRQn

#define KEY_DOWN_EXTI_GPIO_RCC  	RCC_APB2Periph_GPIOC //GPIOC
#define KEY_DOWN_EXTI_GPIO_PORT  	GPIOC
#define KEY_DOWN_GPIO_PORTSOURCE	GPIO_PortSourceGPIOC
#define KEY_DOWN_EXTI_GPIO_PIN   	GPIO_Pin_3
#define KEY_DOWN_EXTI_LINE          EXTI_Line3
#define KEY_DOWN_GPIO_PINSOURCE		GPIO_PinSource3
#define KEY_DOWN_EXTI_IRQN 			EXTI3_IRQn

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 

//	--------------------------------------------------------------------------
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 




//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入



void NVIC_Configuration(void); //嵌套中断控制器的设置
void RCC_Configuration(void); //RCC时钟类的设置
static void NVIC_Config(void); /* 主要是配置中断源的优先级与打开使能中断通道 */
void PC_PA_13_14_15_Gpio(void); //设置 PA 13 14 15   PC 13 14 15 io功能

#endif
