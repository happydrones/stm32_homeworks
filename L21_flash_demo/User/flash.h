#ifndef __FLASH_H
#define __FLASH_H 			   
#include "stm32f10x.h"	

void     FLASH_Write(u32 Flash_add,uint16_t Flash_Dat);
void Time_Write(u8 h,u8 m,u8 s);
void Time_Read(u8 *h,u8 *m,u8 *s);
uint16_t FLASH_Read(u32 Flash_add);
#endif





























