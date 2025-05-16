#include "key.h"
#include "delay.h"
#include "led.h"

struct key_struct up_key = {GPIOC, GPIO_Pin_0,0};
struct key_struct down_key = {GPIOC, GPIO_Pin_2,0};
struct key_struct left_key = {GPIOC, GPIO_Pin_1,0};
struct key_struct right_key = {GPIOC, GPIO_Pin_3,0};
struct key_struct common_Pin = {GPIOC, GPIO_Pin_7,0};

void Common_Pin_Init(struct key_struct* Key)
{
    GPIO_InitTypeDef GPIO_key_InitStructure;
    GPIO_key_InitStructure.GPIO_Pin = Key->GPIO_Pin;
    GPIO_key_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_Init(GPIOC, &GPIO_key_InitStructure);
    GPIO_ResetBits(Key->GPIO_Group, Key->GPIO_Pin);
}

void Key_Init(struct key_struct* Key)
{
    GPIO_InitTypeDef GPIO_key_InitStructure;
    GPIO_key_InitStructure.GPIO_Pin = Key->GPIO_Pin;
    GPIO_key_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    if (Key->GPIO_Group == GPIOA)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_Init(GPIOA, &GPIO_key_InitStructure);
    }
    else if (Key->GPIO_Group == GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        GPIO_Init(GPIOB, &GPIO_key_InitStructure);
    }
    else if (Key->GPIO_Group == GPIOC)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_Init(GPIOC, &GPIO_key_InitStructure);
        
		
    }
    else if (Key->GPIO_Group == GPIOD)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
        GPIO_Init(GPIOD, &GPIO_key_InitStructure);
    }
    else if (Key->GPIO_Group == GPIOE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
        GPIO_Init(GPIOE, &GPIO_key_InitStructure);
    }
    else if (Key->GPIO_Group == GPIOF)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
        GPIO_Init(GPIOF, &GPIO_key_InitStructure);
    }
    else if (Key->GPIO_Group == GPIOG)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
        GPIO_Init(GPIOG, &GPIO_key_InitStructure);
    }
}


/*
 * @ brief 按键检测函数
 * @ param Key 按键结构体
 * @ return 按键状态，0：未按下，1：按下
 */
void Key_Scan(struct key_struct* Key)
{
	if((GPIO_ReadInputDataBit(Key->GPIO_Group, Key->GPIO_Pin))==0)
	{
        delay_ms(10);
        if((GPIO_ReadInputDataBit(Key->GPIO_Group, Key->GPIO_Pin))==0)
        {
            Key->key_flag =1;
        }
	}
}
