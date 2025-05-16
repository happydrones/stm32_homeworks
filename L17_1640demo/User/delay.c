
#include "delay.h"


/*
* @brief  延时us函数
* @param  nCount  循环次数
* @retval 无
*/
void delay_us(u16 nCount)
{
	uint16_t loop;
    do{
        for (uint8_t i = 0; i < 5; i++)
        {
        }
		loop++;
		
    }while(loop<nCount);
}
/*
* @brief  延时10us函数
* @param  nCount  循环次数
* @retval 无
*/
void delay_10us(u16 nCount)
{
	uint16_t loop;
    do{
        for (uint8_t i = 0; i < 95; i++)
        {
        }
		loop++;
		
    }while(loop<nCount);
}
/*
* @brief  延时ms函数
* @param  nCount  循环次数
* @retval 无
*/
void delay_ms(u16 nCount)
{
    for (u16 j = 0; j < nCount; j++)
    {    
         for(u16 i=0; i<7995; i++)
        {         
        }
    } 
}

/*
* @brief  延时ms函数
* @param  nCount  循环次数
* @retval 无
*/
void delay_s(u16 nCount)
{
    for (u32 j = 0; j < nCount; j++)
    {    
        for(u32 i=0; i<6605000; i++)
        {         
        }
    } 
}
