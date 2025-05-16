 /**
  ******************************************************************************
  * @file    sys.c
  * @author  oscar
  * @version V0.0.1
  * @date    
  * @brief
  *  该软件延时是在系统主线时钟是在72mhz的基础上进行的，
  *  
  * 1.
  *
  *    
  *        
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

#include "delay.h"



void Delay_ms(u16 X_ms)  //延迟  X_ms*1  默认状态不配置rcc 默认时钟
{
  u16 x=0,y=0;
	for(x=X_ms;x>0;x--)
	   for(y=7995;y>0;y--);
}


void Delay_10us(u16 t)  //延迟  X_ms*1  默认状态不配置rcc 默认时钟
{
  u16 x,y;
	for(x=t;x>0;x--)
	   for(y=10;y>0;y--);
}

void Delay_us(u16 X_us)  //延迟  X_us*1  默认状态不配置rcc 默认时钟
{
  u16 x,y;
	for(x=X_us;x>0;x--)
	   for(y=8;y>0;y--);
}
