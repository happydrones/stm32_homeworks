#include "timer.h"
#include "stm32f10x.h"

volatile uint8_t timer_flag;
static	TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;
static	NVIC_InitTypeDef NVIC_InitStructure;

volatile uint32_t ic_rise = 0;
volatile uint32_t ic_fall = 0;
volatile uint32_t pulse_width = 0;

/*
 * @brief	timer2初始化函数
 * @param	Auto_reload_value	自动重装载值
 * @param	Prescaler				
 * @retval 无
 * @note	对定时器二的初始化，
 **/
void timer2_init(uint16_t Auto_reload_value,uint16_t Prescaler)
{
    //在72hz时钟下，最大的单次计算时间为
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // enable TIM1 clock

    //定时器2时基单元配置部分
    TIM_TimBaseStructure.TIM_Prescaler = Prescaler-1; // 72 MHz / (7199+1) = 10kHz 得到分频的频率为10kHz
    TIM_TimBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimBaseStructure.TIM_Period = Auto_reload_value-1; // 10khzx(9+1)hz =1ms 然后计数是10，那么单次计算时间就是100ms
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
    //使能定时器2
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


/***********************************输入捕获相关实验的配置************************************/
/*使用的定时是timer4输入捕获电机测速实验*/


/*
 * @brief	timer4输入捕获初始化函数
 * @param	None
 * @retval None 
 * */
void TIM4_InputCapture_Init(void) 
{
    // Enable clocks
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // GPIOB Pin6 -> TIM4_CH1 and TIM4_CH2 (indirect)
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_6;
    gpio.GPIO_Mode = GPIO_Mode_IPD; // pull-down input
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio);

    // NVIC config for TIM4 IRQ
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM4_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    //************时基单元配置初始化************
    // Timer base configuration
    TIM_TimeBaseInitTypeDef TIM4_TimeBaseStructure;
    TIM4_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM4_TimeBaseStructure.TIM_Prescaler = 72 - 1; // 1 MHz timer clock (assuming 72 MHz PCLK1)
    TIM4_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM4_TimeBaseStructure);
    //为了保证计时器参数设置生效

    //************通道一输入捕获配置************
    // Input capture config for CH1 (rising edge on TI1)
    TIM_ICInitTypeDef TIM4_CH1_ICStructure;
    //对通道一进行设置
    TIM4_CH1_ICStructure.TIM_Channel = TIM_Channel_1;
    //设置输入捕获的极性为上升沿
    TIM4_CH1_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    //信号选择直接输入到通道1
    TIM4_CH1_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // direct input from TIM4
    //捕捉信号是否进行分频，也就是每一个有一个有效
    TIM4_CH1_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    //捕捉通道的滤波器设置
    TIM4_CH1_ICStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM4, &TIM4_CH1_ICStructure);

    //通道2输入捕获配置
    // Input capture config for CH2 (falling edge on TI1 via indirect)
    TIM_ICInitTypeDef TIM4_CH2_ICStructure;
    TIM4_CH2_ICStructure.TIM_Channel = TIM_Channel_2;
    TIM4_CH2_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
    TIM4_CH2_ICStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI; // indirect input from TIM4
    TIM4_CH2_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM4_CH2_ICStructure.TIM_ICFilter = 0x0;
    TIM_ICInit(TIM4, &TIM4_CH2_ICStructure);
    //通道1和通道2是可以相互引用彼此的信号，共同映射到同一引脚
    // Slave mode: Reset counter on rising (TI1), capture on falling gives high pulse width
    TIM_SelectInputTrigger(TIM4, TIM_TS_TI1FP1);
    //TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);

    // Enable capture compare interrupts for both channels
    //通道1和通道2的中断使能
    TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);

    // Start timer
    TIM_Cmd(TIM4, ENABLE);
}

void TIM4_IRQHandler(void) 
{
    //判断是否是通道1的中断，如果是，则说明上升沿触发，CCR1快照了上升沿是的计数器值
    if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) {
        // Rise detected, CCR1 holds period from last reset
        ic_rise = TIM_GetCapture1(TIM4);
        TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
    }
    //判断是否是通道2的中断，如果是，则说明下降沿触发，CCR2快照了下降沿的计数器值
    if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET) {
        // Fall detected, CCR2 holds pulse width
        ic_fall = TIM_GetCapture2(TIM4);
        pulse_width = ic_fall; // since reset at rise, CCR2 is high time in microseconds
        TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
    }
}
