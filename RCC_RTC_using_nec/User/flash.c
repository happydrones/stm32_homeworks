#include "flash.h"
//#define Flash_add  0x0807F804    //最后一页（255页）：0x0807 F800 – 0x0807 FFFF  flash地址用偶数，因为存储是一两字节位单位

//FLASH写入数据
void FLASH_Write(u32 Flash_add,u16 Flash_Dat) //参数1：32位FLASH地址。参数2：16位数据
{ 
	   //RCC_HSICmd(ENABLE); //打开HSI时钟
	   FLASH_Unlock();  //解锁FLASH编程擦除控制器
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
     FLASH_ErasePage(Flash_add);     //擦除指定地址页，擦除必须以页单位，会擦除整页    
	   FLASH_ProgramHalfWord(Flash_add,Flash_Dat); //从指定页的addr地址开始写   
  	 FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
     FLASH_Lock();    //锁定FLASH编程擦除控制器  
}

//FLASH读出数据
u16 FLASH_Read(u32 Flash_add)      //Flash_add：32位FLASH地址。 返回值：16位数据
{ 
	/*
	u16 Flash_Dat;
  Flash_Dat = *(u16*)(Flash_add);  //从指定页的Flash_add地址读出数据
  
	return Flash_Dat;	 
   */ 
	return *(u16*)(Flash_add);     //从指定页的Flash_add地址开始读
}

//FLASH写入数据
void FLASH_Write_HalfWord(u32 Flash_add,u16 Flash_Dat,u16 Flash_Dat_Num,u32 Flash_ADD_BASE) //参数1：32位FLASH地址  参数2：16位数据  参数3：总共Flash数据个数
{ 
	   u16 Flash_Dat_Save[Flash_Dat_Num];   //缓存Flash 所有数据 方便后面重新写入flash
	   u8  i = 0;
	   for(i=0;i<Flash_Dat_Num;i++)
     {
		    Flash_Dat_Save[i] = FLASH_Read(Flash_ADD_BASE+i*2);      //Flash_add：32位FLASH地址。 返回值：16位数据		 
		 }    
		 
		 Flash_Dat_Save[(Flash_add-Flash_ADD_BASE)/2] = Flash_Dat;
	 	
	   //RCC_HSICmd(ENABLE); //打开HSI时钟
	   FLASH_Unlock();  //解锁FLASH编程擦除控制器
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
     FLASH_ErasePage(Flash_add);     //擦除指定地址页，擦除必须以页单位，会擦除整页   

		 for(i=0;i<Flash_Dat_Num;i++)
		 {
		   FLASH_ProgramHalfWord(Flash_ADD_BASE+i*2,Flash_Dat_Save[i]); //从指定页的addr地址开始写 
		 }
  	 FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
     FLASH_Lock();    //锁定FLASH编程擦除控制器  
}


















