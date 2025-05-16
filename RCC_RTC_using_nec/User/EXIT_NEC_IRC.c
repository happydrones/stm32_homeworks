#include "EXIT_NEC_IRC.h"
#include "delay.h"

u8 Key_NEC_IRC_Data = 0;   //NEC红外遥控键值
u8 Key_NEC_IRC_Add  = 0;   //NEC红外遥控地址
/*********************************************************************
*函数名称：NVIC_Configuration(void)
*函数功能：选择中断优先等级分组 
*函数调用：NVIC_Configuration();
*参数列表：无
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/
//********************************************************************* 
void NVIC_Configuration(void)
{   
	  // 5.配置NVIC优先级组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	  
}
//*********************************************************************
/*********************************************************************
*函数名称：EXTI_NEC_IRC_Key_Config(void)
*函数功能：NEC中断红外解码初始化
*函数调用：EXTI_NEC_IRC_Key_Config();
*参数列表：无
*返 回 值：无
*结    果：
*备    注：想要获取红外遥控数据，必须在主程序调用该函数打开中断配置
*********************************************************************/
//*********************************************************************
void EXTI_NEC_IRC_Key_Config(void)
{ 
	// 5.配置NVIC优先级组
	NVIC_Configuration();
//	// 5.配置NVIC优先级组
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	//1.打开EXTI外部GPIO,AFIO,RCC时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //打开外在中断GPIO组时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//打开AFIO时钟 
	
	//2.EXTI外部中断线GPIO模式设置
  GPIO_InitTypeDef GPIO_InitStructure; //定义GPIO的初始化结构体
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;            //选择端口号   
	
	//GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            //选择端口号 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //选择IO接口工作方式 //上拉电阻 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //设置IO接口速度（2/10/50MHz） 可以不配置速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);	

	//3.选择EXTI外部中断信号源
  EXTI_InitTypeDef  EXTI_InitStructure;   //定义结构体变量	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);  //选择GPIO外部中断中断输入口	

		
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;              //定义中断线
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;               //中断使能
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;     //中断模式为 中断
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //下降沿触发
	
	EXTI_Init(& EXTI_InitStructure);	
   		
	//4.配置NVIC中断优先级
  NVIC_InitTypeDef NVIC_InitStructure;
   
  NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;   //中断线    
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;    //使能中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //抢占优先级 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;         //响应优先级 2
	
	NVIC_Init(& NVIC_InitStructure);
	
   
}
//*********************************************************************
/*********************************************************************
*函数名称：u32 Get_NEC_RxLow_level(void) 
*函数功能：NEC红外协议 测量低电平时间
*函数调用：u32 Get_NEC_RxLow_level();
*参数列表：无
*返 回 值：低电平时间单位微妙
*结    果：
*备    注：
*********************************************************************/
//*********************************************************************
u32 Get_NEC_RxLow_level(void) 
{
u32 time  =0;  //红外电平时间
                      	
SysTick->VAL=0x00;               //清空定时器的计数器 写入任意值都是清除定时器，同时计满标志位（COUNTFLAG）也会自动清零 
SysTick->LOAD= 0xffffff; //重装计数初值（当主频是72MHz，72次为1微秒 24位减法定时器）
SysTick->CTRL=0x00000005;        //时钟源HCLK，打开定时器    	
while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0);
SysTick->CTRL=0;//关闭定时器 	
time = (0x00ffffff-(SysTick->VAL)&0x00ffffff)/72 ; //当主频是72MHz，72次为1微秒 24位减法定时器

/* //不能用函数形式，误差太大，解码遥控时序 必须直接从寄存器读出时间方式   
	 while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)
	 {
		  time_NEC++;  //红外电平时间
	    SysTick_Delay_us(10);
	 }
*/
	 return time;	 
}
//*********************************************************************
/*********************************************************************
*函数名称：u32 Get_NEC_RxHigh_level(void) 
*函数功能：NEC红外协议 测量高电平时间
*函数调用：Get_NEC_RxHigh_level();
*参数列表：无
*返 回 值：高电平时间单位微妙
*结    果： 
*备    注：
*********************************************************************/
//*********************************************************************
u32 Get_NEC_RxHigh_level(void) 
{
u32 time =0;  //红外电平时间	
SysTick->VAL=0x00;               //清空定时器的计数器 写入任意值都是清除定时器，同时计满标志位（COUNTFLAG）也会自动清零 
SysTick->LOAD= 0xffffff; //重装计数初值（当主频是72MHz，72次为1微秒 24位减法定时器）
SysTick->CTRL=0x00000005;        //时钟源HCLK，打开定时器
	
while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 1);
SysTick->CTRL=0;//关闭定时器 	
time = (0x00ffffff-(SysTick->VAL)&0x00ffffff)/72 ; //当主频是72MHz，72次为1微秒 24位减法定时器

	return time;
}
//*********************************************************************
/*********************************************************************
*函数名称：EXTI9_5_IRQHandler(void) 
*函数功能：NEC红外协议 中断函数解码
*函数调用：中断函数无需调用自动进入
*参数列表：无
*返 回 值：无
*结    果： 全局变量，在main函数通过extern引用即可获得红外遥控数据
            红遥控地址：Key_NEC_IRC_Add   红外遥控键值数据：Key_NEC_IRC_Data
*备    注： 该解码函数包含快加快减功能 
            长短按识别功能可以在主程序上进行时间累计判断实现
*********************************************************************/
//*********************************************************************
void EXTI9_5_IRQHandler(void)
{
   u32 time_NEC=0,j,i;
	 u8 data=0X00;	
   u8 NEC_IRC_4Byte[4];	    //缓存NEC协议数据
	 u8 Start_Repeat_Flag = 0;  //判断起始信号还是重复信号  Start   1   
   static u8 NEC_Last_Data  = 0;    //上一次键值	
	
	if (EXTI_GetITStatus(EXTI_Line9) == SET)
	{
		 	EXTI_ClearITPendingBit(EXTI_Line9);  //清除中断标志位	
		//如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)
		{
					/*1. 判断引导码或重复信号*/
					time_NEC = Get_NEC_RxLow_level(); //NEC红外协议 获取低电平时间
					if(time_NEC<8000||time_NEC>10000) return; //如果低电平时间 小于8000us或者大于us毫秒丢弃
					time_NEC = Get_NEC_RxHigh_level();//NEC红外协议 获取高电平时间
			    if(time_NEC<1500||time_NEC>5500)return;  //如果高电平时间小于1500us或大于5500us丢弃
			    //Star信号 低电平9000us 高电平4500us     Repeat信号低电平9000us 高电平2500us
			
					if(time_NEC<3500)  //Repeat重复信号
					{ 
          Key_NEC_IRC_Data = NEC_Last_Data;    //保存上一次键值											
			    return; //识别到是Repeat重复信号，退出不进行数据解码
					}
					else						//否则Start信号 
					{	
						 
					  Start_Repeat_Flag = 1;  //判断起始信号还是重复信号  Start   1    
					}	
			    
          //EXTI_Cont= time_NEC; //测试识别到的电平时间 *1us 通过1602液晶显示出来观察实际时间		
					
					/*2. 接收用户码和按键码*/
					if(Start_Repeat_Flag == 1) //判断起始信号还是重复信号  Start   1   
					{
					for(i=0;i<4;i++)
					{
							for(j=0;j<8;j++)
							{
									time_NEC= Get_NEC_RxLow_level(); //NEC红外协议 获取低电平时间
									if(time_NEC<460||time_NEC>660)return;  //数据 0  数据1 电平都是560us
									
									time_NEC=Get_NEC_RxHigh_level(); //NEC红外协议 获取高电平时间
									//560us高电平  0    1680us高电平 1
									if(time_NEC>460&&time_NEC<660)
									{
										data>>=1;  //最高位写 0
									}
									else if(time_NEC>1590&&time_NEC<1790)
									{
										 data>>=1;          
										 data|=0x80; //1000 0000  最高位写1
									}
							}
							NEC_IRC_4Byte[i]= data;
					}
					//if((~NEC_IRC_4Byte[0] == NEC_IRC_4Byte[1]) && (~NEC_IRC_4Byte[2] == NEC_IRC_4Byte[3]))
					//if( (~0xff) == (0x00))
					
					//接收完数据 效验并更新键值数据
					if( (!(NEC_IRC_4Byte[0] & NEC_IRC_4Byte[1])) && (!(NEC_IRC_4Byte[2] & NEC_IRC_4Byte[3])))				
					{
					  Key_NEC_IRC_Add  = NEC_IRC_4Byte[0];   //NEC红外遥控地址								
            Key_NEC_IRC_Data = NEC_IRC_4Byte[2];   //NEC红外遥控键值	
						
            NEC_Last_Data = Key_NEC_IRC_Data;      //保存上一次键值	给Repeat 重复给上一次键值，实现快+ 快- 功能										
					}			 
					
					}
				
		}

	}

}


 
