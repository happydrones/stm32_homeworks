#ifndef __TM1640_H__
#define __TM1640_H__

#include "stm32f10x.h" 
typedef enum{
	addr_Auto_Mode =0x40,
	addr_Fixed_Mode = 0x44
} addr_command;

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
extern uint8_t SMG_Code_Table[18] ;
#define GPIO_Group_TM1640   GPIOG
#define TM1640_SCLK         GPIO_Pin_7
#define TM1640_DIN          GPIO_Pin_6
#define TM1640_number_length   8 //显示屏数字个数

void TM1640_start(void);//发送数据帧头
void TM1640_End(void);//发送数据帧尾
void TM1640_Write_Byte(uint8_t TM1640_Data);
void TM1640_Init(void); //初始化引脚定义和模式配置
void TM1640_Clear(void); //清除显示屏
void TM1640_SetBrightness(Brightness_level_t Brightness_level_x);
void TM1640_Display_Init(void);
void TM1640_DisplayNumber(uint8_t start_digit, uint8_t digit_count, uint32_t number, uint8_t has_decimal_point);
void TM1640_DisplayTime(uint8_t Hours, uint8_t Minutes, uint8_t Seconds); //显示时间
void TM1640_DisplayOriginalNum(uint8_t start_position, uint8_t  number_array[], uint8_t number_size) ; //显示原始数字

#endif

