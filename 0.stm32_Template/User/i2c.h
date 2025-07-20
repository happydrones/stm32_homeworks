#ifndef __I2C_H
#define __I2C_H
#include "sys_config.h"



#define HostAddress	0xc0	//总线主机的器件地址
#define BusSpeed	200000	//总线速度（不高于400000）


void I2C1_Configuration(void);
void I2C_Sand_Buffer(u8 SlaveAddr, u8 WriteAddr, u8* pBuffer, u16 NumByteToWrite);
void I2C_Send_Byte(u8 SlaveAddr,u8 writeAddr,u8 pBuffer);
void I2C_Read_Buffer(u8 SlaveAddr,u8 readAddr,u8* pBuffer,u16 NumByteToRead);
u8 I2C_Read_Byte(u8 SlaveAddr,u8 readAddr);
		 				    
#endif
