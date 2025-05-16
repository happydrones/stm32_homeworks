#include "EXIT_NVIC.h"
#include "1602lcd.h"
#include "delay.h"

u16 EXTI_Cont=0; //中断进入次数标志位
extern u8 EXTI_Test_Num;  //程序 正在执行的 位置 标志  （主程序：等于0，中断服务函数0  等于1 ，中断服务函数2 等于2）

/*********************************************************************
*函数名称：NVIC_Configuration(void)
*函数功能： 
*函数调用：
*参数列表：无
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/
void NVIC_Configuration(void)
{   
	  // 5.配置NVIC优先级组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	  
}

void EXTI_Key_Config(void)
{ 
	// 5.配置NVIC优先级组
	NVIC_Configuration();
//	// 5.配置NVIC优先级组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	//1.打开EXTI外部GPIO,AFIO,RCC时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //打开外在中断GPIO组时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//打开AFIO时钟 
	
	//2.EXTI外部中断线GPIO模式设置
  GPIO_InitTypeDef GPIO_InitStructure; //定义GPIO的初始化结构体
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;            //选择端口号   
	
	//GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            //选择端口号 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //选择IO接口工作方式 //上拉电阻 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //设置IO接口速度（2/10/50MHz） 可以不配置速度
	GPIO_Init(GPIOC,&GPIO_InitStructure);	

	//3.选择EXTI外部中断信号源
  EXTI_InitTypeDef  EXTI_InitStructure;   //定义结构体变量	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);  //选择GPIO外部中断中断输入口	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);  //选择GPIO外部中断中断输入口
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);  //选择GPIO外部中断中断输入口
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);  //选择GPIO外部中断中断输入口
		
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;              //定义中断线
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;               //中断使能
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;     //中断模式为 中断
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //下降沿触发
	
	EXTI_Init(& EXTI_InitStructure);	
//***********************************************************************
   //KE2 使用上面选择EXTI外部中断信号源
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;              //定义中断线	
	EXTI_Init(& EXTI_InitStructure);
//***********************************************************************		
   //KE3 使用上面选择EXTI外部中断信号源
  EXTI_InitStructure.EXTI_Line=EXTI_Line2;              //定义中断线	
	EXTI_Init(& EXTI_InitStructure);
//***********************************************************************		
   //KE4 使用上面选择EXTI外部中断信号源
  EXTI_InitStructure.EXTI_Line=EXTI_Line3;              //定义中断线	
	EXTI_Init(& EXTI_InitStructure);	
//***********************************************************************			
	//4.配置NVIC中断优先级
  NVIC_InitTypeDef NVIC_InitStructure;
   
  NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;   //中断线    
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;    //使能中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //抢占优先级 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;         //响应优先级 2
	
	NVIC_Init(& NVIC_InitStructure);
	
//***********************************************************************		
   //KE2 	使用上面配置NVIC中断优先级
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;   //中断线
	NVIC_Init(& NVIC_InitStructure);
//***********************************************************************		
   //KE3 	使用上面配置NVIC中断优先级	 
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;   //中断线
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;  //抢占优先级 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;         //响应优先级 2	

	NVIC_Init(& NVIC_InitStructure);
//***********************************************************************		
   //KE4 	使用上面配置NVIC中断优先级
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;   //中断线
	NVIC_Init(& NVIC_InitStructure);
//***********************************************************************			
}

//EXTI0_IRQHandler
//外部中断服务函数
void EXTI0_IRQHandler(void)
{
	//EXTI_Cont ++;//中断进入次数标志位
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			EXTI_Cont ++;//中断进入次数标志位 
			Display_Lcd_1602_Number(2,11,1,5);//1602任意位置写字十进制数
			Delay_ms(1000); //延迟  X_ms*1  默认状态不配置rcc 默认时钟
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
		EXTI_Test_Num   = 1;  //程序 正在执行的 位置 标志  （主程序：等于0，中断服务函数0  等于1 ，中断服务函数2 等于2）
	}

}/*
//外部中断服务函数
void EXTI1_IRQHandler(void)
{
	//EXTI_Cont ++;//中断进入次数标志位
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
		{
			EXTI_Cont ++;//中断进入次数标志位
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}*/
//外部中断服务函数
void EXTI2_IRQHandler(void)
{
	//EXTI_Cont ++;//中断进入次数标志位
	if (EXTI_GetITStatus(EXTI_Line2) == SET)
	{
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == 0)
		{
			EXTI_Cont --;//中断进入次数标志位		
			Display_Lcd_1602_Number(2,11,2,5);//1602任意位置写字十进制数
			Delay_ms(1000); //延迟  X_ms*1  默认状态不配置rcc 默认时钟		
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
  EXTI_Test_Num   = 2;  //程序 正在执行的 位置 标志  （主程序：等于0，中断服务函数0  等于1 ，中断服务函数2 等于2）
}
/*
//外部中断服务函数
void EXTI3_IRQHandler(void)
{
	//EXTI_Cont ++;//中断进入次数标志位
	if (EXTI_GetITStatus(EXTI_Line3) == SET)
	{
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			EXTI_Cont --;//中断进入次数标志位
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
 */
/*******************************************
//其他中外部中断服务函数 模版
void EXTI4_IRQHandler(void)
{
	//EXTI_Cont ++;//中断进入次数标志位
	if (EXTI_GetITStatus(EXTI_Line3) == SET)
	{
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			EXTI_Cont --;//中断进入次数标志位
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

void  EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
**********************************************************************/
