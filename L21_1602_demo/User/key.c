#include "key.h"
#include "delay.h"


void Keypad_Init(void)
{
	RCC_APB2PeriphClockCmd(Key_GPIO_RCC,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;

    // 初始化行（ROW）为推挽输出
	//只要传入的参数为16进制，然后 那一位是1，就会给将对应的模式
    GPIO_InitStruct.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ROW_GPIO_PORT, &GPIO_InitStruct);

    // 初始化列（COL）为上拉输入
    GPIO_InitStruct.GPIO_Pin = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(COL_GPIO_PORT, &GPIO_InitStruct);
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

