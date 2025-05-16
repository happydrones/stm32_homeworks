#include "pwm.h"
#include "led.h"
#include "delay.h"
//频率：PWM_f   1-1000 Hz     PWM_Duty :1-100
void GPIO_Out_PWM(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,u16 PWM_f,u16 PWM_Duty)
{
	u16 PWM_Resolution =100;  //分辨率 1000,也就是占空比的最小单位是百分之一的增长
	u16 PWM_Low_rate =0;          //PWM低电平宽度 局部变量
	u16 T_Num = 0;				//对应频率周期需要多少个us级延迟函数调用 局部变量
	T_Num = (u16)(1000)/PWM_f;     //对应频率周期需要多少个us级延迟函数调用，单位时间是10us  
	PWM_Low_rate = PWM_Resolution - PWM_Duty;

	GPIO_SetBits(GPIOx,GPIO_Pin);         // 输出 1 		 
	Systick_delay_10us(PWM_Duty*T_Num);
	GPIO_ResetBits(GPIOx,GPIO_Pin);     //PB0 输出 0
	Systick_delay_10us(PWM_Low_rate*T_Num);	 
	

}

void GPIO_Out_Speet_Test(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{  

	 while(1)
	 {
		GPIO_SetBits(GPIOx,GPIO_Pin);         // 输出 1 		 
    	GPIO_ResetBits(GPIOx,GPIO_Pin);     //PB0 输出 0
 
	 }
}
