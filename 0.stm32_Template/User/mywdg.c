#include "mywdg.h"
#include "usart.h"



void wdg_Init()
{
	if((RCC_GetFlagStatus(RCC_FLAG_IWDGRST)) != RESET)
	{
		printf("Reset By IWDG \r\n");
		RCC_ClearFlag();

		
	}
	else
	{
		printf("Reset by user\r\n");
	}
	//1.解除写保护
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//2.设置分频值
	IWDG_SetPrescaler(IWDG_Prescaler_4);
	
	//3.设置重载值
	IWDG_SetReload(0x625);   //每秒喂狗一次
	//4.执行一次喂狗操作
	IWDG_ReloadCounter();
	//5.激活看门狗
	IWDG_Enable();
}
