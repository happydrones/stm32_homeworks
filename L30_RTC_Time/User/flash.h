#ifndef __FLASH_H
#define __FLASH_H 			   
#include "stm32f10x.h"	

void FLASH_Write(u32 Flash_add,u16 Flash_Dat);
u16 FLASH_Read(u32 Flash_add);
#endif





























