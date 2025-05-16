#ifndef __FLASH_H
#define __FLASH_H 			   
#include "stm32f10x.h"	

void FLASH_Write(u32 Flash_add,u16 Flash_Dat);
u16 FLASH_Read(u32 Flash_add);
void FLASH_Write_HalfWord(u32 Flash_add,u16 Flash_Dat,u16 Flash_Dat_Num,u32 Flash_ADD_BASE); //参数1：32位FLASH地址  参数2：16位数据  参数3：总共Flash数据个数

#endif





























