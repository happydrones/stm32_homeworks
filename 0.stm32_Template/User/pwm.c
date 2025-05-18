#include "pwm.h"
#include "led.h"
#include "delay.h"


//频率：PWM_f   1-10000 Hz     PWM_Duty :1-100
void GPIO_Out_PWM(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,u16 PWM_f,u16 PWM_Duty)
{  
	 u8 PWM_Resolution =100;  //分辨率 100
	 u16 PWM_Low =0;          //PWM低电平宽度 局部变量
	 u16 T_Num = 0;           //对应频率周期需要多少个us级延迟函数调用 局部变量
	// T_Num = (1000000/PWM_f)/PWM_Resolution;
	 T_Num = 10000/PWM_f;     //对应频率周期需要多少个us级延迟函数调用  
	 PWM_Low = PWM_Resolution - PWM_Duty;
	 PWM_Duty= PWM_Duty*T_Num; //高电平占比对应多少个微妙级延迟函数
	 PWM_Low = PWM_Low*T_Num;  //低电平占比对应多少个微妙级延迟函数
	 LED_GPIO_Init();
	 while(1)
	 {
		 GPIO_SetBits(GPIOx,GPIO_Pin);         // 输出 1 		 
		 Delay_us(PWM_Duty);
		 GPIO_ResetBits(GPIOx,GPIO_Pin);     //PB0 输出 0
	     Delay_us(PWM_Low);	 
	 }
}

void GPIO_Out_Speet_Test(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{  

	 while(1)
	 {
		 GPIO_SetBits(GPIOx,GPIO_Pin);         // 输出 1 		 
         GPIO_ResetBits(GPIOx,GPIO_Pin);     //PB0 输出 0
	 }
}



void PWM_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); // 开启 GPIOA 和 AFIO 时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                        // 开启 TIM2 时钟

    // 配置 PA15 为复用推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;      // 复用推挽
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 使能 TIM2 的完全重映射，使 TIM2_CH1 映射到 PA15
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
}




void TIM2_PWM_Init(uint16_t Auto_reload_value, uint16_t Prescaler)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef		 TIM_OCInitStructure;

    // 基础定时器配置
    TIM_TimeBaseStructure.TIM_Period = Auto_reload_value-1;
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 输出比较配置（PWM 模式 1）
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = Auto_reload_value / 2;  // 初始占空比 50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    // 启用预装载
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE); // 启动定时器
}



