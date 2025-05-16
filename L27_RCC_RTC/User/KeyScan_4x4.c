#include "KeyScan_4x4.h"
#include "delay.h"

void Key_4x4_Scan_GPIO_Init(u16 Key_Ground_GPIO_Pin)   //矩阵键盘行扫描GPIO配置函数
{
	GPIO_InitTypeDef  GPIO_InitStructure; 	
	RCC_APB2PeriphClockCmd(Key_GPIO_RCC,ENABLE);         //打开键盘GPIO时钟       
	GPIO_InitStructure.GPIO_Pin   = Key_Ground_GPIO_Pin; //矩阵键盘行 公共地 IO                        
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;    //选择IO接口工作方式       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置IO接口速度（2/10/50MHz）    	
	GPIO_Init(Key_GPIOPORT, &GPIO_InitStructure);        //写入GPIO参数配置   

	GPIO_WriteBit(Key_GPIOPORT,Key_Ground_GPIO_Pin,(BitAction)(0)); //公共地 IO 输出低电平 0	
	//RCC_APB2PeriphClockCmd(Key_GPIO_RCC,ENABLE);       
	GPIO_InitStructure.GPIO_Pin   = 0x00FF & (~Key_Ground_GPIO_Pin); //选择矩阵键盘转换为独立键盘后其他所有端口                        
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;       //选择IO接口工作方式  上拉输入模式    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(Key_GPIOPORT, &GPIO_InitStructure);	
	
	GPIO_SetBits(Key_GPIOPORT,0x00FF & (~Key_Ground_GPIO_Pin)); //除去公共地其他IO输出 1	
}

/*********************************************************************
*函数名称： KeyScan_4x4_Value
*函数功能： 独立键盘返回键值
*函数调用： KeyScan_4x4_Value();
*参数列表： 无

*返 回 值： 返回键值 位 实际的物理按键 PCB班上 名字标号
*结    果：  
*备    注： 

*********************************************************************/

u8 KeyScan_4x4_Value(void)  //矩阵键盘键值函数
{
	//static u8 Key_Value = 0; //键值  实验一，键值显示实验 需要加static修饰
	 u8 Key_Value = 0; //键值  
	 u8 Temp = 0;     //GPIO数据缓存
	 u8 Key_Time_Flag = 0; //长按今年识别延迟10ms 累计时间标志位
//******************************************************************** 
	 Key_4x4_Scan_GPIO_Init(GPIO_Pin_0);//矩阵键盘扫描 行给 0 初始化 扫描第一行给Pin_0 给 0
	
	if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFE) //读整组IO !=0X00FE)
	{
	   Delay(10); //消抖
		 if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFE) //读整组IO !=0X00FE)
		 { 
			  Temp  = GPIO_ReadInputData(Key_GPIOPORT)&0XFF;
	      //Delay(5);	
			    
					while(((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFE)&&(Key_Time_Flag <= Key_Long_Time))//松手检测 + 长短按键识别
					{
		          Delay_ms(10); 
              Key_Time_Flag++; //长按今年识别延迟10ms 累计时间标志						
					}				 
				  switch(Temp) 
					{
						case 0xee: Key_Value = 1;   break;
						case 0xde: Key_Value = 2;   break;
						case 0xbe: Key_Value = 3;   break;
						case 0x7e: Key_Value = 4;   break;
						default:{Key_Value = 22;}   break;
					}			  
		 }	
	}		 
//********************************************************************	
	
   //扫描第二行  0X00FD    0000 0000 1111 1101
   //PC = 0X00FD;
	 Key_4x4_Scan_GPIO_Init(GPIO_Pin_1);//矩阵键盘扫描 行给 0 初始化 扫描第一行给Pin_0 给 0
	
	if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFD) //读整组IO !=0X00FE)
	{
	   Delay(10);//消抖
		 if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFD) //读整组IO !=0X00FE)
		 { 
			  Temp  = GPIO_ReadInputData(Key_GPIOPORT)&0XFF;
	      //Delay(5);						
					while(((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFD)&&(Key_Time_Flag <= Key_Long_Time))//松手检测 + 长短按键识别
					{
		          Delay_ms(10);  
              Key_Time_Flag++; //长按今年识别延迟10ms 累计时间标志						
					}	 
				  switch(Temp) 
					{
						case 0xED: Key_Value = 5;   break;
						case 0xDD: Key_Value = 6;   break;
						case 0xBD: Key_Value = 7;   break;
						case 0x7D: Key_Value = 8;   break;
						default:{Key_Value = 22;}   break;
					}			  		 
		 }	
	}		 
//********************************************************************
//********************************************************************	
	
   //扫描第三行  0X00FB    0000 0000 1111 1011
   //PC = 0X00FB;
	 Key_4x4_Scan_GPIO_Init(GPIO_Pin_2);//矩阵键盘扫描 行给 0 初始化 扫描第一行给Pin_0 给 0
	
	if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFB) //读整组IO !=0X00FE)
	{
	   Delay(10);//消抖
		 if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFB) //读整组IO !=0X00FE)
		 { 
			  Temp  = GPIO_ReadInputData(Key_GPIOPORT)&0XFF;
	      //Delay(5);						
					while(((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XFB)&&(Key_Time_Flag <= Key_Long_Time))//松手检测 + 长短按键识别
					{
		          Delay_ms(10);  
              Key_Time_Flag++; //长按今年识别延迟10ms 累计时间标志						
					}	 
				  switch(Temp) 
					{
						case 0xEB: Key_Value = 9;   break;
						case 0xDB: Key_Value = 10;   break;
						case 0xBB: Key_Value = 11;   break;
						case 0x7B: Key_Value = 12;   break;
						default:{Key_Value = 22;}   break;
					}			  		 
		 }	
	}		 
//********************************************************************	
//********************************************************************	
	
   //扫描第四行  0X00F7    0000 0000 1111 0111
   //PC = 0X00F7;
	 Key_4x4_Scan_GPIO_Init(GPIO_Pin_3);//矩阵键盘扫描 行给 0 初始化 扫描第一行给Pin_0 给 0
	
	if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XF7) //读整组IO !=0X00FE)
	{
	   Delay(10);//消抖
		 if((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XF7) //读整组IO !=0X00FE)
		 { 
			  Temp  = GPIO_ReadInputData(Key_GPIOPORT)&0XFF;
	      //Delay(5);						
					while(((GPIO_ReadInputData(Key_GPIOPORT)&0XFF) != 0XF7)&&(Key_Time_Flag <= Key_Long_Time))//松手检测 + 长短按键识别
					{
		          Delay_ms(10);  
              Key_Time_Flag++; //长按今年识别延迟10ms 累计时间标志						
					}	 
				  switch(Temp) 
					{
						case 0xE7: Key_Value = 13;   break;
						case 0xD7: Key_Value = 14;   break;
						case 0xB7: Key_Value = 15;   break;
						case 0x77: Key_Value = 16;   break;
						default:{Key_Value = 22;}   break;
					}			  		 
		 }	
	}		 
//********************************************************************	
  if(Key_Time_Flag>=Key_Long_Time)  //判断长按按键，如果长按，给键值BD7位 置1
		Key_Value |=0x80;	
	
	Key_4x4_Scan_GPIO_Init(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);//矩阵键盘扫描 四行全给 0 初始化  

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

