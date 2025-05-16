#include "ec11.h"



void Encoder_EC11_Init(void)
{ 
		GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构	
		//GPIO RCC时钟打开
		RCC_APB2PeriphClockCmd(Encoder_GPIO_RCC,ENABLE);  //打开编码器GPIO RCC时钟   
		//编码器左转GPIO 
		GPIO_InitStructure.GPIO_Pin  = Encoder_L_Pin;  //选择端口号                        
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //选择IO接口工作方式 //上拉电阻       
		GPIO_Init(Encoder_L_GPIOPORT,&GPIO_InitStructure);	
		//编码器右转GPIO 
		GPIO_InitStructure.GPIO_Pin  = Encoder_R_Pin;  //选择端口号                        
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //选择IO接口工作方式 //上拉电阻       
		GPIO_Init(Encoder_R_GPIOPORT,&GPIO_InitStructure);	
		//编码器独立按键 GPIO 
		GPIO_InitStructure.GPIO_Pin  = Encoder_Key_Pin; //选择端口号                        
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //选择IO接口工作方式 //上拉电阻       
		GPIO_Init(Encoder_Key_GPIOPORT,&GPIO_InitStructure);					
}
	
u8 Encoder_EC11_Key(void)
{ 
	u8 EC_11_Key_Ralue = 0; //键值缓存局部变量
	u8 Encoder_R_Flag  = 0; //缓存右转判断局部变量
  u16 EC_11_Key_Out  = 0; //编码器卡死在导状态，限定规定的时长，强制退出松手检测
	static u8 exit = 0;  // 识别长按按键 松开
	
	if(!Encoder_L) //判断是否旋转旋钮，同时判断是否有旋钮锁死
		{ 
				Encoder_R_Flag=Encoder_R;	//把旋钮另一端电平状态记录
        Delay_ms(3);//去抖			
				if(!Encoder_L)
					{ 
							if(Encoder_R_Flag==0)
							{ //用另一端判断左或右旋转
								EC_11_Key_Ralue=1;//右转
							}
							else
							{
								EC_11_Key_Ralue=2;//左转
							}
							
							//EC_11_Key_Out=0; //初始锁编码器卡死标志位
							while(!Encoder_L&& (EC_11_Key_Out<1000))//编码器选择松手检测 1秒如果编码器旋转还在合上状态，强制退出松手检测
							{ //等待放开旋钮，同时累加判断锁死
								EC_11_Key_Out++;
								Delay_ms(1); 
							}
							if(EC_11_Key_Out>=1000)//当编码器处于卡死一直导通状态，编码器动作取消
								EC_11_Key_Ralue=0;			
		      }
	}
		

	if(exit ==1)
	{
    if(Encoder_Key) //判断旋钮独立按键是否按下
      exit = 0;			
	}
	else
	{
		if(!Encoder_Key) //判断旋钮独立按键是否按下
			{   
			Delay_ms(10);//去抖动
			if(!Encoder_Key)
				{ exit = 0;  // 识别长按按键 松开
					//Delay_ms(10);//去抖动
				 EC_11_Key_Ralue=3;//在按键按下时加上按键的状态值
					u8 EC_11_KeyLong = 0;   //识别独立按键长按 时间
					while(Encoder_Key==0)//松手检测
				 {
							EC_11_KeyLong++;
							Delay_ms(100);//去抖动
							if(EC_11_KeyLong>=20)  // 100ms * 20  2秒以上不松开按键 为长按
							{
								EC_11_Key_Ralue=10;//编码器独立按键长按2秒 返回 10
								exit = 1;  // 识别长按按键 松开							
								break;
							}			
				 } 
				}
	  }	
	
	
	}

	return EC_11_Key_Ralue;
}

/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/
