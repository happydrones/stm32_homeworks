#include "pwm.h"
#include "delay.h"

void Pwm_Port_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	if (GPIOx == GPIOA)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_Init(GPIOx, &GPIO_InitStructure);
		GPIO_Write(GPIOx, 0xFFFF);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	else if (GPIOx == GPIOC)
    { 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_Write(GPIOC, 0xFFFF);
    }
	else if (GPIOx == GPIOG)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_Init(GPIOx, &GPIO_InitStructure);
		GPIO_Write(GPIOx, 0xFFFF);
    }

}

/*
 * @brief 利用软件延时生成PWM输出
 * @param GPIOx: 输出端口
 * @param GPIO_Pin: 输出引脚
 * @param PWM_Frequency: PWM频率
 * @param PWM_Duty: PWM占空比
 * @param loop_times: 循环次数
 */
void Pwm_generate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,uint16_t PWM_Frequency, uint8_t PWM_Duty,uint16_t loop_times)
{
    //判断PWM_Duty是否在1-100之间
    if (PWM_Duty < 1 || PWM_Duty > 100)
    {
        // 这里可以设置一个错误标志或者直接 return
        // 例如可以通过一个LED闪烁或者设置一个全局错误标志，或者直接跳出函数
        return;

    }   
    uint16_t high_time, low_time;
    uint16_t T =100000/PWM_Frequency; //周期大小，单位为10us
    high_time = T * PWM_Duty/100; //高电平时间(ms)
    low_time = T - high_time; //低电平时间(ms)
    while (loop_times)
    {
        GPIO_SetBits(GPIOx, GPIO_Pin);
        delay_10us(high_time);
        GPIO_ResetBits(GPIOx, GPIO_Pin);
        delay_10us(low_time);
        loop_times --;
    }	
};

