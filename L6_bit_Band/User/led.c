#include "led.h"





/*
* @brief 初始化LED硬件接口
* @param GPIOx: 选择GPIOx组别 范围
*/
void LED_Init(GPIO_TypeDef* GPIOx)
{
    //初始化对应的GPIO时钟
    if (GPIOx == GPIOA)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if (GPIOx == GPIOB)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if (GPIOx == GPIOC)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    else if (GPIOx == GPIOD)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    else if (GPIOx == GPIOE)    
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    else if (GPIOx == GPIOF)    
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    else if (GPIOx == GPIOG)    
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    else
        return;
    //设置GPIO为输出模式
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //config GPIO
	if (GPIOx == GPIOA)
	{
		GPIO_Init(GPIOA , &GPIO_InitStructure);
		GPIO_Write(GPIOA,0xFFFF);
	}
    else if (GPIOx == GPIOB)
	    GPIO_Init(GPIOB, &GPIO_InitStructure);
    else if (GPIOx == GPIOC)
	    GPIO_Init(GPIOC, &GPIO_InitStructure);
    else if (GPIOx == GPIOD)
	    GPIO_Init(GPIOD, &GPIO_InitStructure);
    else if (GPIOx == GPIOE)
	    GPIO_Init(GPIOE, &GPIO_InitStructure);
    else if (GPIOx == GPIOF)
	    GPIO_Init(GPIOF, &GPIO_InitStructure);
    else if (GPIOx == GPIOG)
	    GPIO_Init(GPIOG, &GPIO_InitStructure);
    else
        return;
	
};


/*
* @brief 点亮LED
* @param GPIOx: 选择GPIOx组别 范围
* @param LED_number: GPIO_Pin_x
*/
void LED_On(GPIO_TypeDef* GPIOx,  uint16_t LED_number)
{
    GPIO_ResetBits(GPIOx, LED_number);
};


/*
* @brief 熄灭LED
* @param GPIOx: 选择GPIOx组别 范围  
* @param LED_number: 选择LED引脚号
*/
void LED_Off(GPIO_TypeDef* GPIOx,  uint16_t LED_number)
{
    GPIO_SetBits(GPIOx, LED_number);
};

