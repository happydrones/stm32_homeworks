/**
 *******************************************************************************
 * @file    oled0561.c
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
 *         1. this oled driver is only for SH1106 controller.
 *<h2><center>&copy; COPYRIGHT 2025 Oscar happydrones123@gmail.com </center></h2>
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "oled0561.h"
#include "ascii.h"


/**
 * @brief Initialize the OLED0561 display
 * @param  None 
 * @return None 
 * @note  This function initializes the OLED0561 display. It first turns off the display, 
 * 		  clears the screen, and then sets the initial display settings.
 */
void Oled0561_Init(void)
{
	//GPIO Init
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(OLED_I2C_GPIO_CLK,ENABLE);       
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); 	
    GPIO_InitStructure.GPIO_Pin = OLED_I2C_SCL_PIN | OLED_I2C_SDA_PIN; 		   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 		
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 		
	GPIO_Init(OLED_I2C_SCL_PORT, &GPIO_InitStructure);

	// IIC Init
	I2C_InitTypeDef  I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;						
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = HostAddress; 				
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;					
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	I2C_InitStructure.I2C_ClockSpeed = BusSpeed; 					
	I2C_Init(OLED_I2C_PERIPH,&I2C_InitStructure);
	I2C_Cmd(OLED_I2C_PERIPH,ENABLE);
	//OLED config
	Oled_Display_OFF();     
	Oled_Display_Clear();   
	Oled_Display_ON();

}

/**         Oled_Display_ON
 * @brief 	This function init the OLED0561 display.
 * @param 	None 
 * @return 	None 
 * @note  	This function only available for SH1106 controller.
 */
void Oled_Display_ON (void)
{
	u8 buf[28]={
	0xae,              		//0xae:关显示，0xaf:开显示
    0x00,0x10,       	    //开始地址（双字节）       
	0xd5,0x80,       	    //显示时钟频率？
	0xa8,0x3f,       	    //复用率？
	0xd3,0x00,       	    //显示偏移？
	0XB0,             	    //写入页位置（0xB0~7）
	0x40,            	    //显示开始线
	0x8d,0x14,        	    //VCC电源
	0xa1,               	//设置段重新映射？
	0xc8,         	        //COM输出方式？
	0xda,0x12,     		    //COM输出方式？
	0x81,0xff,				//对比度，指令：0x81，数据：0~255（255最高）
	0xd9,0xf1,				//充电周期？
	0xdb,0x30,				//VCC电压输出
	0x20,0x00,				//水平寻址设置
	0xa4,					//0xa4:正常显示，0xa5:整体点亮
	0xa6,					//0xa6:正常显示，0xa7:反色显示
	0xaf					//0xae:关显示，0xaf:开显示
	}; 						//
	I2C_Send_Buffer(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,buf,28);
}


/**
 * @brief Turn off the OLED0561 display.
 * @param None
 * @return None
 * @note  This function turns off the OLED0561 display by 
 *        sending the appropriate command to the SH1106 controller. 
 */
void Oled_Display_OFF (void)
{        //OLED屏关显示
	u8 buf[3]={
		0xae,                            //0xae:show off，0xaf:show on
		0x8d,0x10,                       //VCC电源
		}; 
	I2C_Send_Buffer(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,buf,3);
}

/**
 * @brief Set the brightness of the OLED display.
 * @param brightness: Brightness value (0~255).
 * @note  This function sends the brightness command to the SH1106 controller.
 */
void OLED_Set_Brightness(uint8_t brightness)
{             
    I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, 0x81);      // Command for setting brightness
    I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, brightness); // Brightness value (0~255)
}

/**
  * @brief  This function is used to set the cursor position.
  * @param  row :
  * @param  column :
  * @retval None
  */
void OLED_SetPos(uint8_t row,uint8_t column) 
{
    uint8_t data_buffer_temp[] =  {0xB0+row,((column&0xF0)>>4)|0x10,(column&0x0F)|0x00};//{设置Y位置,设置X位置高4位,设置X位置低4位}
    I2C_Send_Buffer(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,data_buffer_temp,3);
}
 

/**
 * @brief Clear the OLED display.
 * @param None
 * @note  This function clears the OLED display by 
 * 		sending the command to the SH1106 controller.
 */
void Oled_Display_Clear(void)
{   
    uint8_t Oled_clear_data[128]={0};
    memset(Oled_clear_data,CLEAR_BYTE,128);              
	for(uint8_t page = OLED_CMD_SET_PAGE_START;page < 0xB8;page++)
	{
        OLED_SetPos( page,SH1106_COLUMN_OFFSET);
		// write the data 0x00 to clear the screen
		I2C_Send_Buffer(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_DATA,Oled_clear_data,128);
	}
}

/**
 * @brief   Displays a 6x8 ASCII character on the OLED screen.
 * @param   row: The starting row (vertical position, 0-7).
 * @Note    A 6x8 character occupies exactly one page in height.
 * @param   column: The starting column (horizontal position, 0-122).
 * @Note    A character is 6 pixels wide.
 * @param   character: The ASCII character to display (e.g., 'A', '1').
 * @return  None
 */
void OLED_DisplayChar6x8(uint8_t row, uint8_t column, char character)
{
    // --- 1. Boundary Check ---
    // Check if the character will be drawn outside the screen boundaries.
    // Screen width is 128, character width is 6, so the max starting column is 128 - 6 = 122.
    // Screen height is 8 pages, so the max row is 7.
    if ((column > 122) || (row > 7))
    {
        return; // If out of bounds, return immediately without drawing.
    }

    // --- 2. Calculate Font Index ---
    // Calculate the index (row number) for the character in the ASCII_6x8 font array.
    // This assumes the font library starts with the ASCII space character (' ').
    uint8_t char_index = character - ASCII_START_CHAR;

    // --- 3. Set OLED Screen Write Address ---
    // Apply the hardware column offset required by the SH1106 driver.
    // If your driver is not SH1106 or doesn't have this offset, you can comment out this line.
    column += SH1106_COLUMN_OFFSET;

    // Set the page address (which is the `row` we passed in).
    // A 6x8 character only occupies one page, so no loop is needed like for 8x16 characters.
    I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, OLED_CMD_SET_PAGE_START + row);

    // Set the starting column address.
    I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, OLED_CMD_SET_COL_HIGH | (column >> 4));   // Set high 4 bits of column address.
    I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, OLED_CMD_SET_COL_LOW | (column & 0x0F)); // Set low 4 bits of column address.

    // --- 4. Write Character Data ---
    // Loop 6 times to write the 6 columns of data that form the character.
    for (uint8_t i = 0; i < 6; i++)
    {
        // Get the corresponding column data from the font library.
        uint8_t font_data = ASCII_6x8[char_index][i];
        // Send the data byte to the OLED.
        I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_DATA, font_data);
    }
}





/**             OLED_DisplayChar8x16
 * @brief  Displays an 8x16 ASCII character on the OLED screen.
 * @param  page: The starting page (vertical position, 0-6). 
 * @Note   An 8x16 character occupies two pages.
 * @param  column: The starting column (horizontal position, 0-120). 
 * @Note: A character is 8 pixels wide.
 * @param  character: The ASCII character to display (e.g., 'A', '1').
 * @renturn None
 */
void OLED_DisplayChar8x16(uint8_t page, uint8_t column, char character)
{
    uint16_t font_base_index;
    // --- 1. Boundary Check ---
    // Check if the character will be drawn outside the screen boundaries (horizontally or vertically).
    if ((column + FONT8X16_WIDTH > SCREEN_MAX_COLUMN + 1) || (page + (FONT8X16_HEIGHT / 8) > SCREEN_MAX_PAGE + 1))
    {
        return; // If out of bounds, return immediately without drawing.
    }
    
    // --- 2. Calculate Font Index ---
    // Calculate the starting index for the character in the font data array.
    font_base_index = (character - ASCII_START_CHAR) * FONT8X16_BYTES;

    // Apply the hardware column offset required by the SH1106 driver.
    column += SH1106_COLUMN_OFFSET;

    // --- 3. Drawing Loop ---
    // An 8x16 character needs to be written to two separate pages.
    for (uint8_t page_loop = 0; page_loop < (FONT8X16_HEIGHT / 8); page_loop++)
    {
        // Set the page address for the current segment of the character (top or bottom half).
        I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, OLED_CMD_SET_PAGE_START + page + page_loop);

        // Set the starting column address.
        I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, OLED_CMD_SET_COL_HIGH | (column >> 4));   // Set high 4 bits of column.
        I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_CMD, OLED_CMD_SET_COL_LOW | (column & 0x0F)); // Set low 4 bits of column.

        // Write the 8 columns of data that form this part of the character.
        for (uint8_t i = 0; i < FONT8X16_WIDTH; i++)
        {
            // Directly calculate the index for the font data. This removes the need for the old 'c' counter variable.
            // When page_loop=0, this fetches bytes 0-7. When page_loop=1, it fetches bytes 8-15.
            uint8_t Ascii_code = ASCII_8x16[font_base_index + (page_loop * FONT8X16_WIDTH) + i];
            I2C_Send_Byte(OLED_I2C_ADDRESS, OLED_CONTROL_BYTE_DATA, Ascii_code);
        }
    }
}





/**
 * @brief Display a string on the OLED display.
 * @param row: The starting row (vertical position, 0-7).
 * @Note  A 6x8 character occupies exactly one page in height.
 * @param column: The starting column (horizontal position, 0-122).
 * @Note  A character is 6 pixels wide.
 * @param str: The string to display.
 * @return None
 */
void Oled_Display_String_6X8(u8 row, u8 column, u8 *str)
{
    u8 r = 0;
    while (*str != '\0') {
        OLED_DisplayChar6x8(row, (column + r) * 6, *str++);
        r++;
    }
}

/**
 * @brief Display a string on the OLED display.
 * @param row: The starting row (vertical position, 0-6).
 * @Note  A 8x16 character occupies exactly two pages in height.
 * @param column: The starting column (horizontal position, 0-122).
 * @Note  A character is 8 pixels wide.
 * @param str: The string to display.
 * @return None
 */
void Oled_Display_String_8x16(u8 row, u8 column, u8 *str)
{
    u8 r = 0;
    while (*str != '\0') {
        OLED_DisplayChar8x16(row, (column + r) * 8, *str++);
        r++;
    }
}


/**
 * @brief Display a number on the OLED0561 screen with smart formatting.
 * @param row: row coordinate (0 to 7)
 * @param column: column coordinate(0 to 64)
 * @param num: number to display (float or double)
 * @note  This function automatically formats the number without trailing zeros.
 *        Examples: 123.0 -> "123", 1.23 -> "1.23", 0.123 -> "0.123"
 */
void Oled_display_number(u8 row, u8 column, const float num, FontSize size)
{
    char str[32];
    char temp[32];
    int len, i;
    
    // First format with maximum precision
    sprintf(temp, "%.6f", num);
    
    // Remove trailing zeros and decimal point if not needed
    len = strlen(temp);
    
    // Remove trailing zeros
    for (i = len - 1; i >= 0; i--) 
    {
        if (temp[i] == '0') 
        {
            temp[i] = '\0';
            len--;
        } 
        else if (temp[i] == '.') 
        {
            temp[i] = '\0';
            len--;
            break;
        } 
        else 
        {
            break;
        }
    }
    // Copy the cleaned string
    strcpy(str, temp);
    if(size == FONT_SIZE_6x8)
    {
        Oled_Display_String_6X8(row, column, (u8 *)str);
		
    }
    else if(size ==  FONT_SIZE_8x16)
    {
        Oled_Display_String_8x16(row, column, (u8 *)str);
    }
}



//----- 用于汉字显示的程序，暂不使用 ------//

//显示汉字16*16
//取模大小为16*16，取模方式为“从左到右从上到下”“纵向8点下高位”
//void OLED_DISPLAY_16_16(u8 x, //显示汉字的页坐标（从0xB0到0xB7）
//			u8 y, //显示汉字的列坐标（从0到63）
//			u16 w){ //要显示汉字的编号
//	u8 j,t,c=0;
//	for(t=0;t<2;t++){
//		I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,x); //页地址（从0xB0到0xB7）
//		I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,y/16+0x10); //起始列地址的高4位
//		I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,y%16);	//起始列地址的低4位
//		for(j=0;j<16;j++){ //整页内容填充
// 			I2C_Send_Byte(OLED_I2C_ADDRESS,DAT,GB_16[(w*32)+c]);
//			c++;}x++; //页地址加1
//	}
//	I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,0xAF); //开显示 
//}
//用户自定义的汉字库调用（w是uc.h中要显示汉字的编号）（此处不可修改）
//void OLED_DISPLAY_16_16_UC(u16 w){ 
//	u8 x,j,t,c=0;
//	x=0xb1;
//	for(t=0;t<2;t++){
//		I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,x); //页地址（从0xB0到0xB7）
//		I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,XY_UC/16+0x10); //起始列地址的高4位
//		I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,XY_UC%16);	//起始列地址的低4位
//		for(j=0;j<16;j++){ //整页内容填充
// 			I2C_Send_Byte(OLED_I2C_ADDRESS,DAT,GB_UC16[(w*32)+c]);
//			c++;}x++; //页地址加1
//	}
//	I2C_Send_Byte(OLED_I2C_ADDRESS,OLED_CONTROL_BYTE_CMD,0xAF); //开显示 
//}



/**
 * @brief Display an integer on the OLED0561 screen.
 * @param row: row coordinate (0 to 7)
 * @param column:column coordinate(0 to 64)
 * @param num: number to display
 */
// void Oled_display_8X16integer(u8 row,u8 column, u32 num)
// {
//     char str[10];
//     sprintf(str,"%d",num);
//     Oled_Display_String_8x16(row,column,(u8 *)str);
// }

/**
 * @brief Display a float number on the OLED0561 screen.
 * @param row: row coordinate (0 to 7)
 * @param column: column coordinate(0 to 64)
 * @param num: float number to display
 * @param decimal_places: number of decimal places to display (0-6)
 */
// void Oled_display_8X16float(u8 row, u8 column, float num, u8 decimal_places)
// {
//     char str[16];
//     char format[8];
    
//     // Create format string based on decimal places
//     sprintf(format, "%%.%df", decimal_places);
//     sprintf(str, format, num);
//     Oled_Display_String_8x16(row, column, (u8 *)str);
// }

/**
 * @brief Display a double number on the OLED0561 screen.
 * @param row: row coordinate (0 to 7)
 * @param column: column coordinate(0 to 64)
 * @param num: double number to display
 * @param decimal_places: number of decimal places to display (0-6)
 */
// void Oled_display_8X16double(u8 row, u8 column, double num, u8 decimal_places)
// {
//     char str[16];
//     char format[8];
    
//     // Create format string based on decimal places
//     sprintf(format, "%%.%dlf", decimal_places);
//     sprintf(str, format, num);
//     Oled_Display_String_8x16(row, column, (u8 *)str);
// }



// void OLED_Display_Single_ASCII_8x16(u8 row,u8 column, u16 charater)
// {
// 	u8 t,c=0;
// 	column=column+2; 										//因OLED屏的内置驱动芯片是从0x02列作为屏上最左一列，所以要加上偏移量
// 	for(t=0;t<2;t++)
// 	{
// 		I2C_Send_Byte(OLED_I2C_ADDRESS, COM, PAGE_HEAD_ADDR+row); //页地址（从0xB0到0xB7）
// 		I2C_Send_Byte(OLED_I2C_ADDRESS, COM, 0x10 | ((column >> 4) & 0x0F)); // 高4位
// 		I2C_Send_Byte(OLED_I2C_ADDRESS, COM, column & 0x0F);                 // 低4位
// 		for(uint8_t char_column=0;page<8;page++)
// 		{ //整页内容填充
//  			I2C_Send_Byte(OLED_I2C_ADDRESS,DAT,ASCII_8x16[(w*16)+c-512]);//为了和ASII表对应要减512
// 			c++;
// 		}
// 		row++;		 //页地址加1
// 	}
// }
