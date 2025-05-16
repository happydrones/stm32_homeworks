#include "led.h"
#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "sys.h"
#include "delay.h"
//******************************************************

   //第一步：GPIO初始化配置	 
/*********************************************************************
*函数名称： 
*函数功能： 
*函数调用： 
*参数列表：无
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/	
   

void LED_GPIO_Init(void)
{
		//第一步：设置时钟  
			 //完成该节课作业， 需要打开所有组io口时钟 ，GPIO  A  -  G
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|
														 RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);//启动APB2总线 PA组IO总时钟
			
		/*	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//启动APB2总线 PA组IO总时钟	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//启动APB2总线 PA组IO总时钟	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//启动APB2总线 PA组IO总时钟	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//启动APB2总线 PA组IO总时钟	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//启动APB2总线 PA组IO总时钟		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);//启动APB2总线 PA组IO总时钟			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);//启动APB2总线 PA组IO总时钟
		*/	
				
			//第二步：设置GPIO工作模式
		GPIO_InitTypeDef  GPIO_InitStruct; 

		//GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;                     //选择第 0 位IO 
		GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_All;                     //选择第 0 位IO 	
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //选择推挽输出
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //选择输出速度  50MHz
			
		GPIO_Init(GPIOA, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度	
		GPIO_Init(GPIOB, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
		GPIO_Init(GPIOC, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度	
		GPIO_Init(GPIOD, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
		GPIO_Init(GPIOE, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度	
		GPIO_Init(GPIOF, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度
		GPIO_Init(GPIOG, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PBA 推挽输出 50MHz 速度	
}
/*********************************************************************
*函数名称： 
*函数功能： 
*函数调用： 
*参数列表：无
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/
void LED_Out (void)
{

/*		 
	#if  1


  #else
		 

  #endif		 
	*/	 
		 
	//第三步：GPIO输出
//-----------------------------------------------------------		 
#if 0 
		 //方法1：GPIO写位操作  Bit_SET 1   Bit_RESET  0	 
	
		 GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);   //PB0 输出 1 
		//GPIO_WriteBit(GPIOA,GPIO_Pin_0,1);   //PB0 输出 1
		 Delay(60000);  //延迟   不是毫秒只是起到延迟的效果	
     GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);   //PB0 输出 0		 
		 //GPIO_WriteBit(GPIOA,GPIO_Pin_0,0);   //PB0 输出 0
		 Delay(60000);  //延迟   不是毫秒只是起到延迟的效果
		
//-----------------------------------------------------------		 
#elif 0
		 //方法2：GPIO置位操作  		 
	//GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4);         //PB0 输出 1
		GPIO_SetBits(GPIOA,GPIO_Pin_All);         //PB0 输出 1  
		 Delay(60000);  //延迟   不是毫秒只是起到延迟的效果	
		GPIO_ResetBits(GPIOA,GPIO_Pin_All);     //PB0 输出 0
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4);     //PB0 输出 0
		 Delay(60000);  //延迟   不是毫秒只是起到延迟的效果	
	 
//-----------------------------------------------------------	
#elif 0
		//方法3：GPIO总线整组操作 
		GPIO_Write(GPIOA,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
		GPIO_Write(GPIOB,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
		GPIO_Write(GPIOC,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
		GPIO_Write(GPIOD,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
		GPIO_Write(GPIOE,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
		GPIO_Write(GPIOF,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
		GPIO_Write(GPIOG,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
								
		Delay(60000);  //延迟   不是毫秒只是起到延迟的效果
		GPIO_Write(GPIOA,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1	 
		GPIO_Write(GPIOB,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1	
		GPIO_Write(GPIOC,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1	 
		GPIO_Write(GPIOD,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1	
		GPIO_Write(GPIOE,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1	 
		GPIO_Write(GPIOF,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1	
		GPIO_Write(GPIOG,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1	 
		Delay(60000);  //延迟   不是毫秒只是起到延迟的效果

//-----------------------------------------------------------
#elif 0 
	//方法4：GPIO位带操作 ，位操作
	    PAout(0)  = 0;  //PA0  输出 0 低电平
      PBout(15) = 0;  //PB15 输出 0 低电平
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(0)  = 1;  //PA0  输出 1 高电平
      PBout(15) = 1;  //PB15 输出 1 高电平			
      Delay(60000);  //延迟   不是毫秒只是起到延迟的效果	
			//  A  = PAin(0);// PA0 输入 
//-----------------------------------------------------------		
#elif 0       //课后作业第二题：位带操作实现 16路流水灯
	
	u8 i=0;
//**************************************************	
	// 把PA组io口所有数据初始为 1 
	for(i=0;i<16;i++)
	{			
	    PAout(i)  = 1;  //PA0  输出 0 低电平  	
	}
//**************************************************	
	
	for(i=0;i<16;i++)
	{
		  PAout(i)  = 0;  //PA0  输出 0 低电平    
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(i)  = 1;  //PA0  输出 0 低电平  	
	}

 /* 
	    PAout(0)  = 0;  //PA0  输出 0 低电平    
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(0)  = 1;  //PA0  输出 0 低电平    
			
			
			PAout(1)  = 0;  //PA0  输出 0 低电平    
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(1)  = 1;  //PA0  输出 0 低电平 

			PAout(2)  = 0;  //PA0  输出 0 低电平    
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(2)  = 1;  //PA0  输出 0 低电平
			
			PAout(3)  = 0;  //PA0  输出 0 低电平    
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(3)  = 1;  //PA0  输出 0 低电平    
			
			
			PAout(4)  = 0;  //PA0  输出 0 低电平    
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(4)  = 1;  //PA0  输出 0 低电平 

			PAout(5)  = 0;  //PA0  输出 0 低电平    
		  Delay(60000);  //延迟   不是毫秒只是起到延迟的效果			
	    PAout(5)  = 1;  //PA0  输出 0 低电平
	*/		
		    
#elif 0       //课后作业第三题：数组实现 16路流水灯 

   u16 LED_16[16] = {0xfffe,0xfffd,0xfffb,0xfff7,0xffef,0xffdf,0xffbf,0xff7f,0xfeff,0xfdff,0xfbff,0xf7ff,0xefff,0xdfff,0xbfff,0x7fff};	 
  static u8 i = 0;	
 /*
	 	for(i=0;i<16;i++)
	{
    GPIO_Write(GPIOA,LED_16[i]);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0 
    Delay(60000);  //延迟   不是毫秒只是起到延迟的效果				
	}
	*/
	  
	  GPIO_Write(GPIOA,LED_16[i++]);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0 
    Delay(60000);  //延迟   不是毫秒只是起到延迟的效果	
	  if(i>=16)
      i=0;			
//-----------------------------------------------------------		
		#elif 1       //课后作业第三题：左移，右移实现 16路流水灯 

    //static u8 i = 0;	
		static u16 LED_DAT_16 =0x0001;
		
    GPIO_Write(GPIOA,~LED_DAT_16);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0 
    Delay(30000);  //延迟   不是毫秒只是起到延迟的效果		
		
		LED_DAT_16 = LED_DAT_16<<1;
		 
		
	  if(LED_DAT_16 == 0x0000)
			LED_DAT_16 =0x0001;
		 
	
//-----------------------------------------------------------		

#endif		 		 
}
/*********************************************************************
*函数名称：PC_PA_13_14_15_Gpio
*函数功能：设置 PA 13 14 15   PC 13 14 15 为io功能
*函数调用：PC_PA_13_14_15_Gpio();
*参数列表：无
*返 回 值：无
*结    果：
*备    注：
*********************************************************************/

void PC_PA_13_14_15_Gpio(void) //设置 PA 13 14 15   PC 13 14 15 io功能
{

	  //rtc作为io，需要先取消rtc备用纽扣电池配置好后再装电池或不装
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE );
	  	  //RCC_APB2Periph_AFIO IO功能复用AFIO 时钟 改变默认功能 恢复IO口功能
    PWR_BackupAccessCmd( ENABLE );/* 允许修改RTC和后备寄存器*/
    RCC_LSEConfig( RCC_LSE_OFF ); /* 关闭外部低速时钟,PC14+PC15可以用作普通IO*/
    BKP_TamperPinCmd(DISABLE);  /* 关闭入侵检测功能,PC13可以用作普通IO*/

	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //恢复PA13  PA14  PA15 IO功能，默认位jtag swd下载功能
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    PWR_BackupAccessCmd(DISABLE);/* 禁止修改RTC和后备寄存器*/
    //BKP_ITConfig(DISABLE);       /* 禁止TAMPER 中断*/

}


/*************************************************************************

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出

选择IO口哪一位：
GPIO_Pin_0 
GPIO_Pin_1 
GPIO_Pin_2 
GPIO_Pin_3 
GPIO_Pin_4 
GPIO_Pin_5 
GPIO_Pin_6 
GPIO_Pin_7 
GPIO_Pin_8 
GPIO_Pin_9 
GPIO_Pin_10 
GPIO_Pin_11 
GPIO_Pin_12 
GPIO_Pin_13 
GPIO_Pin_14 
GPIO_Pin_15
GPIO_Pin_All

现在IO口那组端口：
GPIOA
GPIOB
GPIOC
GPIOD
GPIOE
GPIOF
GPIOG
************************************************************************/
