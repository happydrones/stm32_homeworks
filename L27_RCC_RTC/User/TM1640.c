#include "TM1640.h"
#include "delay.h"

#define AC_Time  5  

//写数据模式
typedef enum
{
   Addr_Fix_Mode = 0X44,  //地址固定  
   Addr_Auto_Mod = 0X40,  //地址自动增加 1 模式
}Addr_Mode_t;


//亮度调节
typedef enum
{
   Brightness_level_0      =  0X80,  //亮度 0 熄灭  
   Brightness_level_1      =  0X88,  //亮度 1 
   Brightness_level_2      =  0X89,  //亮度 2 
   Brightness_level_3      =  0X8A,  //亮度 3 
   Brightness_level_4      =  0X8B,  //亮度 4 
   Brightness_level_5      =  0X8C,  //亮度 5 
   Brightness_level_6      =  0X8D,  //亮度 6 
   Brightness_level_7      =  0X8E,  //亮度 7 
   Brightness_level_8      =  0X8F,  //亮度 8 
   
}  Brightness_level_t;

//显示寄存器地址
typedef enum
{ 
	//All_Place_Addr     = 16,     //TM1640 最大支持16位数码管
	Place_Addr_01      =  0XC0,  
	Place_Addr_02      =  0XC1, 
	Place_Addr_03      =  0XC2, 
	Place_Addr_04      =  0XC3, 
	Place_Addr_05      =  0XC4, 
	Place_Addr_06      =  0XC5, 
	Place_Addr_07      =  0XC6, 
	Place_Addr_08      =  0XC7, 
	Place_Addr_09      =  0XC8, 
	Place_Addr_10      =  0XC9, 
	Place_Addr_11      =  0XCA, 
	Place_Addr_12      =  0XCB, 
	Place_Addr_13      =  0XCC,
	Place_Addr_14      =  0XCD,
	Place_Addr_15      =  0XCE,
	Place_Addr_16      =  0XCF,
} Place_Addr_t;

 
void TM1640_Start()
{  
	 //TM1640起始信号   ，SCLK 高电平期间，DIN 由高变低		
  GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //	SCLK  =  1;   时钟   高电平
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1));  // DIN   =  1;   数据 IO

	//Delay_us(AC_Time);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0));  // DIN   =  0;   数据 IO	
	//Delay_us(AC_Time);

}
void TM1640_Stop()
{  
	//TM1640起始信号 ，SCLK 高电平期间，DIN 由低变高 	
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //	SCLK  =  1;   时钟   高电平
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0));  // DIN   =  0;   数据 IO	
	
	//Delay_us(AC_Time);
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1));  // DIN   =  1;   数据 IO	
	//Delay_us(AC_Time);
}

void TM1640_Write_Byte(u8 TM1640_Dat)
{			
u8 i = 0;
 for(i=0;i<8;i++)
   {
       GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(0)); //	SCLK  =  0;  时钟 IO 
		   //Delay_us(AC_Time);
       if((TM1640_Dat & 0X01)==0X01)
       GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1));  //  DIN   =  1;  数据 IO	
       else
           GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0));  //  DIN   =  0;  数据 IO  

			 
       TM1640_Dat = TM1640_Dat >>1;
			 
			 
       //Delay_us(AC_Time);    
       GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //	SCLK  =  1;  时钟 IO  
       //Delay_us(AC_Time);    
   }
//*********************************
	 //写完一字节数据，必须要把DIN,SLK拉低，否则会导致固定地址模式不能显示“.”
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(0));  //  DIN   =  0;  数据 IO   
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(0)); //	SCLK  =  0;  时钟 IO 
//*********************************		
}

void TM1640_Init(void){ //TM1640接口初始化
	u8 i =0; //for循环次数 局部变量
	GPIO_InitTypeDef  GPIO_InitStructure; 	
  RCC_APB2PeriphClockCmd(TM1640_GPIO_RCC,ENABLE);       
  GPIO_InitStructure.GPIO_Pin = TM1640_DIN | TM1640_SCLK; //选择端口号（0~15或all）                        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //选择IO接口工作方式       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(TM1640_GPIOPORT, &GPIO_InitStructure);

	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_DIN,(BitAction)(1)); //接口输出高电平1	
	GPIO_WriteBit(TM1640_GPIOPORT,TM1640_SCLK,(BitAction)(1)); //接口输出高电平1	
	  
	
	
	TM1640_Start();
	TM1640_Write_Byte(0x40); //设置数据，0x40,0x44分别对应地址自动加一和固定地址模式
	TM1640_Stop();
	
	TM1640_Start();
	TM1640_Write_Byte(0XC0);  //TM1640 初始化，数据清零 0x00

	for(i=0;i<16;i++)  //All_Place_Addr     = 16,     //TM1640 最大支持16位数码管
	{
		TM1640_Write_Byte(0X00);  //TM1640 初始化，数据清零 0x00		
	}
	TM1640_Stop();
	
	TM1640_Start();
	TM1640_Write_Byte(Brightness_level_4); // 控制显示，开显示，0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f  分别对应脉冲宽度为:
					 				                       //------------------1/16,  2/16,  4/16,  10/16, 11/16, 12/16, 13/16, 14/16	 //0x80关显示
	                                       //Brightness_level_0-8   Brightness_level_0 关显示  1最暗 8最亮
	TM1640_Stop();	
	
	
				
}

/*********************************************************************
*函数名称： Disp_Smg_Number_TM1640
*函数功能： 把任意一个八位以内的十进制数，在数码管上x坐标任意位置，任意扫描时间，通过动态扫描显示
*函数调用： void Disp_Smg_Number_TM1640(u8 x_smg,u8 count_smg,u32 number,u8 Point);
*参数列表： 
             u8 x_smg       数码管写入位置X坐标     取值范围1-8
             u8 count_smg   写入几位十进制数        取值范围1-8
             u32 number     写入的十进制数值        取值范围0-99999999 
             u8 Point       给位数指示灯            0 关闭个位数指示点   1打开个位数指示点 

*返 回 值：无
*结    果： 在八位数码管任意位置通动态扫描写一个八位以内的任意数
*备    注： 

*********************************************************************/


void Disp_Smg_Number_TM1640(u8 x_smg,u8 count_smg,u32 number,u8 Point)
{
u8 i;	
u8 number1[8]; //定义一个存储八位数的每一位的数字用的数组
u8  SMG_Code_Table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76};
//u8  wei_dat[8]={0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0XC7};       //定义八位数码管位选数据数组

number1[0] = number % 10;                      //个        
number1[1] = number % 100 / 10;                //十   
number1[2] = number % 1000 / 100;              //百
number1[3] = number % 10000 / 1000;            //千
number1[4] = number % 100000 / 10000;          //万 
number1[5] = number % 1000000 / 100000;        //十万
number1[6] = number % 10000000 / 1000000;      //百万 
number1[7] = number % 100000000 / 10000000;     //千万 


  TM1640_Start();
	TM1640_Write_Byte(0x40); //设置数据，0x40,0x44分别对应地址自动加一和固定地址模式
	TM1640_Stop();	 

   TM1640_Start();

   TM1640_Write_Byte(0XC0+x_smg-1); //设置首地址	
	 // TM1640_Write_Byte(wei_dat[x_smg-1]); //设置首地址

for(i=0;i < count_smg;i++)
{
//********************************************************************	
  //清除显示寄存器
		
	  if((Point==1) && (i==(count_smg-1)) )
		{
		 TM1640_Write_Byte(SMG_Code_Table[number1[count_smg-i-1]] |  0x80);  //0x80 共阴数码管“.”编码   
		}
	  else	
    {		
		 TM1640_Write_Byte(SMG_Code_Table[number1[count_smg-i-1]]);  //TM1640 初始化，数据清零 0x00
		}			
 
//********************************************************************	
}
    	TM1640_Stop(); 
}

void Disp_Smg_Number_TM1640_MODE_0X44(u8 x_smg,u8 count_smg,u32 number,u8 Point)
{
u8 i;	
u8 number1[8]; //定义一个存储八位数的每一位的数字用的数组
u8  SMG_Code_Table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76};
//u8  wei_dat[8]={0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0XC7};       //定义八位数码管位选数据数组

number1[0] = number % 10;                      //个        
number1[1] = number % 100 / 10;                //十   
number1[2] = number % 1000 / 100;              //百
number1[3] = number % 10000 / 1000;            //千
number1[4] = number % 100000 / 10000;          //万 
number1[5] = number % 1000000 / 100000;        //十万
number1[6] = number % 10000000 / 1000000;      //百万 
number1[7] = number % 100000000 / 10000000;     //千万 

  TM1640_Start();
	TM1640_Write_Byte(0x44); //设置数据，0x40,0x44分别对应地址自动加一和固定地址模式
	TM1640_Stop();	 


	 // TM1640_Write_Byte(wei_dat[x_smg-1]); //设置首地址

for(i=0;i < count_smg;i++)
{
//********************************************************************	
  //清除显示寄存器
   TM1640_Start();

   TM1640_Write_Byte(0XC0+x_smg-1+i); //设置首地址	
	
	  if((Point==1) && (i==(count_smg-1)) )
		{
		 TM1640_Write_Byte(SMG_Code_Table[number1[count_smg-i-1]] |  0x80);  //0x80 共阴数码管“.”编码   
		}
	  else	
    {		
		 TM1640_Write_Byte(SMG_Code_Table[number1[count_smg-i-1]]);  //TM1640 初始化，数据清零 0x00
		}		
			TM1640_Stop();	
 
//********************************************************************	
}

}


void TM1640_HG_Display(u8 X_SMG)
{
  TM1640_Start();
	TM1640_Write_Byte(0x44); //设置数据，0x40,0x44分别对应地址自动加一和固定地址模式
	TM1640_Stop();	 

//********************************************************************	
  //清除显示寄存器
   TM1640_Start();
   TM1640_Write_Byte(0XC0+X_SMG-1); //设置首地址	
   TM1640_Write_Byte(0X40);  //0x40 共阴数码管“-”编码   
	 TM1640_Stop();	 
//********************************************************************	       

}
//亮度 模式 数码管显示界面 
void TM1640_Ld_Display(u8 X_SMG)
{
  TM1640_Start();
	TM1640_Write_Byte(0x44); //设置数据，0x40,0x44分别对应地址自动加一和固定地址模式
	TM1640_Stop();	 

//********************************************************************	
  //清除显示寄存器  		 //共阴数码管 ：  "L"  0X38   “d”  0x5E
   TM1640_Start();
   TM1640_Write_Byte(0XC0+X_SMG-1); //设置首地址	
   TM1640_Write_Byte(0X38);  //0x40 共阴数码管“L”编码   
   TM1640_Write_Byte(0X5E);  //0x40 共阴数码管“d”编码   	  
   TM1640_Write_Byte(0X40);  //0x40 共阴数码管“-”编码   
	 TM1640_Stop();	 
//********************************************************************	       
}
