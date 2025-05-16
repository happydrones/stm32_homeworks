#include "pwm.h"
#include "led.h"
#include "delay.h"


//#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>

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
