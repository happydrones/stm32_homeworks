#include "key.h"
#include "delay.h"

void Key_Init(void)//初始化
{
	GPIO_InitTypeDef  GPIO_InitStructure; 	
  RCC_APB2PeriphClockCmd(Key_GPIO_RCC,ENABLE);  //打开 	独立键盘GPIO时钟       
  GPIO_InitStructure.GPIO_Pin   = Key_Ground; //选择端口号 矩阵键盘做独立键盘 公共地 IO                        
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; //选择IO接口工作方式       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(Key_GPIOPORT, &GPIO_InitStructure);

	GPIO_WriteBit(Key_GPIOPORT,Key_Ground,(BitAction)(0)); //公共地 IO 输出低电平0	
	
  
  //RCC_APB2PeriphClockCmd(Key_GPIO_RCC,ENABLE);       
  GPIO_InitStructure.GPIO_Pin   = K4_Pin|K8_Pin|K12_Pin|K16_Pin; //选择端口号  选择所有独立按键端口                        
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //选择IO接口工作方式  上拉输入模式    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(Key_GPIOPORT, &GPIO_InitStructure);	
	
	GPIO_SetBits(Key_GPIOPORT,K4_Pin|K8_Pin|K12_Pin|K16_Pin);         //  所有独立键盘IO 输出 1	 可以省略
	
}

/*********************************************************************
*函数名称： Key_Independent_Value
*函数功能： 独立键盘返回键值
*函数调用： Key_Independent_Value(void);
*参数列表： 无

*返 回 值： 返回键值 位 实际的物理按键 PCB班上 名字标号
*结    果：  
*备    注： 

*********************************************************************/

u8 Key_Independent_Value(void) 
{
	 u8 Key_Value = 0; //键值
	
	   if(GPIO_ReadInputDataBit(Key_GPIOPORT, K4_Pin)==0)  //K4键按下
		 {
		     Delay_ms(10);//消抖
				 if(GPIO_ReadInputDataBit(Key_GPIOPORT, K4_Pin)==0)  //K4键按下
				 {		
					    while(GPIO_ReadInputDataBit(Key_GPIOPORT, K4_Pin)==0);    //松手检测 
							//while(!GPIO_ReadInputDataBit(Key_GPIOPORT, K4_Pin));    //松手检测
						  //while(GPIO_ReadInputDataBit(Key_GPIOPORT, K4_Pin)!=1);  //松手检测
				      Key_Value = 4;

				 }

	   }
	
	   if(GPIO_ReadInputDataBit(Key_GPIOPORT, K8_Pin)==0)  //K8键按下
		 {
		     Delay_ms(10);//消抖
				 if(GPIO_ReadInputDataBit(Key_GPIOPORT, K8_Pin)==0)  //K8键按下
				 {		
					    while(GPIO_ReadInputDataBit(Key_GPIOPORT, K8_Pin)==0)  //松手检测
							{
							     
							}
				      Key_Value = 8;
				 }

	   }



	   if(GPIO_ReadInputDataBit(Key_GPIOPORT, K12_Pin)==0)  //K12键按下
		 {
		     Delay_ms(10);//消抖
				 if(GPIO_ReadInputDataBit(Key_GPIOPORT, K12_Pin)==0)  //K12键按下
				 {		
					    while(GPIO_ReadInputDataBit(Key_GPIOPORT, K12_Pin)==0)  //松手检测
							{
							     
							}
				      Key_Value = 12;
				 }

	   }			 
		 
	   if(GPIO_ReadInputDataBit(Key_GPIOPORT,K16_Pin)==0)  //K16键按下
		 {
		     Delay_ms(10); //消抖
				 if(GPIO_ReadInputDataBit(Key_GPIOPORT,K16_Pin)==0)  //K16键按下
				 {		
					    while(GPIO_ReadInputDataBit(Key_GPIOPORT,K16_Pin)==0)  //松手检测
							{
							     
							}
				      Key_Value = 16;
				 }

	   }

	 
return Key_Value;
}

/*
1.GPIO输入位操作：  
GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  //读 1位 IO
2.GPIO输入总线操作：
GPIO_ReadInputData(GPIO_TypeDef* GPIOx);  //读整组IO 
3.GPIO读输出ODR寄存器 位操作：
GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
4.GPIO读输出ODR寄存器 总线操作：
GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
*/

