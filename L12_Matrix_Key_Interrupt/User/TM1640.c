/**
  ******************************************************************************
  * @file    TM1640.c
  * @author  oscarwang,wangshenghui
  * @version V1.2.0
  * @date    18-October-2024
  * @brief   The TM1604.c file contains the driver functions 
  *         for connecting a Tianwei 1640 chip to a common cathode seven-segment display
  * 		TM1604.c文件是包含天威1640芯片连接共阴数码管的驱动函数   
  ******************************************************************************
  * @attention
  * 1.The TM1640 chip is a common cathode seven-segment display, which is used to display numbers and characters.
  * 2.The TM1640 chip has a serial interface, which is used to communicate with the microcontroller.
  * 3.该文件为an小学生oscarwang,wangshenghui编写，希望尊重原作者的劳动成果，转载请注明出处。
  ******************************************************************************
  */
#include "TM1640.h"
#include "delay.h"
uint8_t SMG_Code_Table[18]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x00};
   //共阴数码管显示字符        0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F
/**
 * @brief : TM1640芯片初始化函数	
 * @param : 无
 * @return : 无
**/
void TM1640_start(void)
{
	
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_DIN,(BitAction)(1));
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_SCLK,(BitAction)(1));
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_DIN,(BitAction)(0));
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_SCLK,(BitAction)(0));

}
/*
 * @brief : TM1640芯片结束传输函数
 * @param : 无
 * @return : 无
**/
void TM1640_End(void)
{
	GPIO_WriteBit(GPIO_Group_TM1640, TM1640_SCLK, Bit_RESET);
	GPIO_WriteBit(GPIO_Group_TM1640, TM1640_DIN, Bit_RESET);
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_SCLK,(BitAction)(1));
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_DIN,(BitAction)(1));
}
/**
 * @brief 控制TM1640数码管的亮度
 * @param Brightness_level_x where x can be (0..8) to select the Brightness .
 *    
**/
void TM1640_SetBrightness(Brightness_level_t Brightness_level_x)
{
	//传输亮度设置
	TM1640_start();
	TM1640_Write_Byte(Brightness_level_x);
	TM1640_End();
	Delay_10us(1);
}
/**
 * @brief 向TM1640芯片写入一个字节的数据
 * @param TM1640_Data : 要写入的数据	
 * @return 无
**/
void TM1640_Write_Byte(uint8_t TM1640_Data)
{
	for (int i = 0; i < 8; i++)  
	{
		if (TM1640_Data & 0x01) 
		{
			GPIO_WriteBit(GPIO_Group_TM1640, TM1640_DIN, Bit_SET); // 设置DIN为1
		} else 
		{
			GPIO_WriteBit(GPIO_Group_TM1640, TM1640_DIN, Bit_RESET); // 设置DIN为0		
		}
		
		GPIO_WriteBit(GPIO_Group_TM1640, TM1640_SCLK, Bit_SET);
		GPIO_WriteBit(GPIO_Group_TM1640, TM1640_SCLK, Bit_RESET);
		TM1640_Data = TM1640_Data >>1;
	}
}
/**
 * @brief : 初始化TM1640芯片，包含引脚配置，数据传输命令设置，地址设置，亮度设置
 * @param : 无
 * @return : 无
**/
void TM1640_Init(void)
{
	//初始化串口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	GPIO_InitTypeDef  TM1640_InitStruct;
	TM1640_InitStruct.GPIO_Pin =TM1640_DIN | TM1640_SCLK;
	TM1640_InitStruct.GPIO_Mode =GPIO_Mode_Out_PP;
	TM1640_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_Group_TM1640,&TM1640_InitStruct);
	//默认设置为高电平
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_DIN,(BitAction)(1));
	GPIO_WriteBit(GPIO_Group_TM1640,TM1640_SCLK,(BitAction)(1));
	Delay_10us(1);
	TM1640_Display_Init();
}
/**
 * @brief: 清除TM1640数码管显示
 * @param : 无
 * @return : 无
**/
void TM1640_Clear(void)
{
	//数码管全部熄灭	
	TM1640_start();
	//传输数据命令设置
	addr_command data=addr_Auto_Mode;
	TM1640_Write_Byte(data);
	TM1640_End();
	//传输地址命令设置
	TM1640_start();
	Place_Addr_t addr_set=Place_Addr_01;
	TM1640_Write_Byte((uint8_t)(addr_set));
	//全部显示点亮
	for (uint8_t i = 0; i < 18; i++)
	{
		TM1640_Write_Byte((uint8_t)(0x00)); //全部数据清屏
	}
	TM1640_End();
}
/**
 * @brief : TM1640初始化函数，包含初始化显示内容，设置亮度等
 * @param : 无
 * @return : 无
**/
void TM1640_Display_Init(void)
{
    //数码管全部显示点亮
	TM1640_start();
	//传输数据命令设置
	addr_command data=addr_Auto_Mode;
	TM1640_Write_Byte(data);
	TM1640_End();
	//传输地址命令设置
	TM1640_start();
	Place_Addr_t addr_set=Place_Addr_01;
	TM1640_Write_Byte((uint8_t)(addr_set));
	//全部显示点亮
	for (uint8_t i = 0; i < 18; i++)
	{
		TM1640_Write_Byte((uint8_t)(0xFF));
	}
	TM1640_End();
	Delay_ms(500);
  //数码管全部熄灭	
	TM1640_start();
	//传输数据命令设置
	data=addr_Auto_Mode;
	TM1640_Write_Byte(data);
	TM1640_End();
	//传输地址命令设置
	TM1640_start();
	addr_set=Place_Addr_01;
	TM1640_Write_Byte((uint8_t)(addr_set));
	//全部显示点亮
	for (uint8_t i = 0; i < 18; i++)
	{
		TM1640_Write_Byte((uint8_t)(0x00)); //全部数据清屏
	}
	TM1640_End();
	
	//传输亮度设置
	TM1640_start();
	uint8_t brightness =(uint8_t)(Brightness_level_5);
	TM1640_Write_Byte(brightness);
	TM1640_End();
	Delay_10us(1);
}
/**
 * @brief 显示数字到TM1640数码管
 * @param start_digit 起始显示位置（数码管的位）
 * @param digit_count 要显示的数码管个数
 * @param number 要显示的数字
 * @param has_decimal_point 是否显示小数点（1：显示，0：不显示）
 */
void TM1640_DisplayNumber(uint8_t start_digit, uint8_t digit_count, uint32_t number, uint8_t has_decimal_point) {
    uint8_t i;    
    uint8_t digits[8];  // 存储每一位数字
    uint8_t segment_code[18] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x76,0x00}; // 数码管段码表

    digits[0] = number % 10;                      // 个位
    digits[1] = number % 100 / 10;                // 十位
    digits[2] = number % 1000 / 100;              // 百位
    digits[3] = number % 10000 / 1000;            // 千位
    digits[4] = number % 100000 / 10000;          // 万位
    digits[5] = number % 1000000 / 100000;        // 十万位
    digits[6] = number % 10000000 / 1000000;      // 百万位
    digits[7] = number % 100000000 / 10000000;    // 千万位

    TM1640_start();
    TM1640_Write_Byte(addr_Auto_Mode); // 设置数据命令，0x40为地址自动加一模式
    TM1640_End();
    
    TM1640_start();
    TM1640_Write_Byte(0xC0 + start_digit - 1);  // 设置首地址
    for (i = 0; i < digit_count; i++) {
        // 显示小数点
        if ((has_decimal_point == 1) && (i == (digit_count - 1))) {
            TM1640_Write_Byte(segment_code[digits[digit_count - i - 1]] | 0x80);  // 0x80用于显示共阴数码管的“.”编码
        } else {
            TM1640_Write_Byte(segment_code[digits[digit_count - i - 1]]);  // 发送对应数码管的段码
        }
    }
    TM1640_End();
}
/**
 * @brief TM1640显示时间函数HH-MM-SS
 * @param Hours  时
 * @param Minutes 分
 * @param Seconds 秒
 * @return 无
 * @note 无
**/
void TM1640_DisplayTime(uint8_t Hours, uint8_t Minutes, uint8_t Seconds)
{
	//数码管全部熄灭	
	TM1640_start();
	//传输数据命令设置 0b01000_000
	addr_command data=addr_Auto_Mode;
	TM1640_Write_Byte(data);
	TM1640_End();
	//传输地址命令设置
	TM1640_start();
	Place_Addr_t addr_set=Place_Addr_01;
	TM1640_Write_Byte((uint8_t)(addr_set));
	TM1640_Write_Byte((uint8_t)(SMG_Code_Table[Hours/10])); 
    TM1640_Write_Byte((uint8_t)(SMG_Code_Table[Hours%10]));
    TM1640_Write_Byte((uint8_t)(0x40)); 
    TM1640_Write_Byte((uint8_t)(SMG_Code_Table[Minutes/10])); 
    TM1640_Write_Byte((uint8_t)(SMG_Code_Table[Minutes%10])); 
    TM1640_Write_Byte((uint8_t)(0x40)); 
    TM1640_Write_Byte((uint8_t)(SMG_Code_Table[Seconds/10])); 
    TM1640_Write_Byte((uint8_t)(SMG_Code_Table[Seconds%10])); 
    TM1640_End();
}
/**
 * @brief TM1640直接显示输入数据
 * @param  Start_Position 起始显示位置（数码管的位）
 * @param Minutes 分
 * @param Seconds 秒
 * @return 无
 * @note 无
**/
void TM1640_DisplayOriginalNum(uint8_t start_position, uint8_t  number_array[], uint8_t number_size) 
{
    if (start_position+number_size-1 > TM1640_number_length) {
        return; // 如果开始位置无效，则返回
    }

	TM1640_start();
	//传输数据命令设置
	addr_command data=addr_Auto_Mode;
	TM1640_Write_Byte(data);
	TM1640_End();
	//传输地址命令设置
	TM1640_start();
	TM1640_Write_Byte(0xC0 + start_position - 1);
	
    for (uint8_t i = 0; i < number_size; i++) {
        // 发送对应数字到显示器
        TM1640_Write_Byte(number_array[i]);

    }
	TM1640_End();
}
