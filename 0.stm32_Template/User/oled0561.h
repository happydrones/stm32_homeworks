/**
 *******************************************************************************
 * @file    oled0561.h
 * @author  Oscar
 * @version V1.0.0  EOL: 2025-07-10
 * @date    2025-07-1
 * @brief   This file is designed to drive OLED 128x64 display modules 
 * 			based on the SH1106 controller.
 *       	It supports displaying Chinese characters, 
 * 			numbers, ASCII codes, and several commonly used unit symbols. 
 ******************************************************************************
 * @note    
 *          
 *   
 * @attention 
 *         1. The loop-based delay functions are suitable for small delays, 
 *         2. in order to achieve high precision and accuracy,
 *            make sure the system clock is setted at 72MHz.
 *<h2><center>&copy; COPYRIGHT 2025 Oscar happydrones123@gmail.com </center></h2>
 *******************************************************************************
 */
#ifndef __OLED_H
#define __OLED_H
//icluding--------------------------------
#include "sys_config.h"
#include "i2c.h"

#include "stdio.h"
#include <string.h>


typedef enum {
  FONT_SIZE_6x8,
  FONT_SIZE_8x16
} FontSize;

/** @defgroup OLED_Hardware_Defines
  * @{
***/
#define OLED_I2C_PERIPH            I2C1
#define OLED_I2C_CLK               RCC_APB1Periph_I2C1
#define OLED_I2C_GPIO_CLK          RCC_APB2Periph_GPIOB
#define OLED_I2C_SCL_PIN           GPIO_Pin_6
#define OLED_I2C_SCL_PORT          GPIOB
#define OLED_I2C_SDA_PIN           GPIO_Pin_7
#define OLED_I2C_SDA_PORT          GPIOB
/**
  * @}
***/
          
/** @defgroup OLED_I2C_Parameters
  * @{
***/
#define OLED_I2C_ADDRESS			    0x78    /**< OLED I2C slave address */
#define OLED_CONTROL_BYTE_CMD		  0x00    /**< Control byte for sending a command */
#define OLED_CONTROL_BYTE_DATA 		0x40    /**< Control byte for sending data */
/**
  * @}
***/

/** @defgroup SH1106_Commands
  * @{
  */
 #define OLED_CMD_SET_PAGE_START    0xB0  /**< Set page start address command */
 #define OLED_CMD_SET_COL_HIGH      0x10  /**< Set higher column address command */
 #define OLED_CMD_SET_COL_LOW       0x00  /**< Set lower column address command */
 #define SH1106_COLUMN_OFFSET       2     /**< SH1106 has a 2-pixel column offset */
 /**
   * @}
***/

/** @defgroup OLED_Screen_Dimensions
  * @{
  */
 #define SCREEN_MAX_PAGE              7     /**< Max pages (0-7) for 64-pixel height (64/8 - 1) */
 #define SCREEN_MAX_COLUMN            127   /**< Max columns (0-127) for 128-pixel width */
 /**
   * @}
***/


/** @defgroup Font_Metrics
  * @{
  */
 #define FONT8X16_WIDTH               8
 #define FONT8X16_HEIGHT              16
 #define FONT8X16_BYTES               16
 #define ASCII8X16_OFFSET             (ASCII_START_CHAR * FONT8X16_BYTES)
 
 #define FONT6X8_WIDTH                6
 #define FONT6X8_HEIGHT               8
 #define FONT6X8_BYTES                8
 #define ASCII6X8_OFFSET              (ASCII_START_CHAR * FONT6X8_BYTES)
 /**
   * @}
***/
/**
  * @note The following ASCII_START_CHAR macro is assumed to be defined elsewhere,
  * typically as 32 (' '). If not, define it here.
  */
 #ifndef ASCII_START_CHAR
 #define ASCII_START_CHAR           ' '
 #define CLEAR_BYTE                 0x00
 #endif

void Oled0561_Init(void);      
void Oled_Display_ON (void);    //OLED屏开显示
void Oled_Display_OFF (void);   //OLED屏关显示
void Oled_Display_Clear(void);  //清屏操作
void OLED_Set_Brightness(u8 brightness);   //OLED屏亮度设置（0~255）
void OLED_SetPos(uint8_t row,uint8_t column);
void OLED_DisplayChar6x8(uint8_t row, uint8_t column, char character);
void OLED_DisplayChar8x16(uint8_t page, uint8_t column, char character);//显示8x16的单个字符 
void Oled_Display_String_6X8(u8 row, u8 column, u8 *str);
void Oled_Display_String_8x16(u8 row, u8 column, u8 *str);
void Oled_display_number(u8 row, u8 column, const float num, FontSize size);
void Oled_display_8X16integer(u8 row,u8 column, u32 num);
void Oled_display_8X16number(u8 row, u8 column, float num);

// 然后创建统一的上层函数
void OLED_DisplayString(uint8_t row, uint8_t column, char *str, FontSize size);
void OLED_DisplayNumber(uint8_t row, uint8_t column, uint32_t num, FontSize size);

#endif
