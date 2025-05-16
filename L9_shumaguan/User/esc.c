#include "esc.h"
#include "delay.h"



/*
 * @brief  根据电调连接的端口初始化PWM的控制信号
 * @param  GPIOx: 电调连接的GPIO端口    
 * @param  GPIO_Pin: 电调连接的GPIO引脚
 * @attention  我设置的电调初始化电调频率为50Hz，占空比为5%，循环次数为250次，可以根据实际情况修改*/
void esc_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x)
{
    uint8_t Pwm_esc_frequency = 50;
    uint8_t pwm_Esc_zore_Duty = 5;
    uint8_t loop_times = 250;
    Pwm_Port_Init(GPIOx,GPIO_Pin_x);
    Pwm_generate(GPIOx,  GPIO_Pin_x, Pwm_esc_frequency,  pwm_Esc_zore_Duty, loop_times);
    
}


/*
 * @brief  设置电调的转速
 * @param  GPIOx: 电调连接的GPIO端口    
 * @param  GPIO_Pin: 电调连接的GPIO引脚
 * @param  speed: 电调的转速，范围为1-100，单位为%
 * @attention  这里设置的转速是相对于最大转速的百分比，例如设置100%转速，实际上电调的转速为最大转速。     
 */
void esc_set_speed(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint16_t speed)
{
    if (speed < 1 || speed > 100)
    {
        // 这里可以设置一个错误标志或者直接 return
        // 例如可以通过一个LED闪烁或者设置一个全局错误标志，或者直接跳出函数
        return;

    }  
    uint8_t Pwm_esc_frequency = 50;
    uint8_t loop_times = 100;

  
    uint16_t high_time, low_time;
    uint16_t T =100000/Pwm_esc_frequency; //周期大小，单位为10us
    high_time = T * 5/100 + T * speed/2000; //高电平时间(ms)
    low_time = T - high_time; //低电平时间(ms)
    while (loop_times)
    {
        GPIO_SetBits(GPIOx, GPIO_Pin);
        delay_10us(high_time);
        GPIO_ResetBits(GPIOx, GPIO_Pin);
        delay_10us(low_time);
        loop_times --;
    }	
}
