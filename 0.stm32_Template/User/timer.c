#include "timer.h"

volatile uint8_t timer_flag;
void timer3_init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2) ;
    //在72hz时钟下，最大的单次计算时间为
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // enable TIM1 clock
    TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimBaseStructure.TIM_Prescaler = 7199; // 72 MHz / (7199+1) = 10kHz 得到分频的频率为10kHz
    TIM_TimBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimBaseStructure.TIM_Period = 999; // 10khzx(9+1)hz =1ms 然后计数是10，那么单次计算时间就是100ms
    TIM_TimBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimBaseStructure);
    //使能定时器2的中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //使能TIm2的中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    //使能定时器
    TIM_Cmd(TIM2, ENABLE); // enable TIM1
    
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        // do something here
        timer_flag = 1;

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
