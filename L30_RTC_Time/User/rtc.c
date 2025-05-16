/**
  ******************************************************************************
  * @file    rtc.c
  * @author  oscar
  * @version v0.0.1
  * 
  * @date    2025-05-1
  * @brief   This file provides a set of functions needed to manage the Real-Time Clock (RTC)
  * @note    This file is based on the template provided by Xia Laoshi for STM32F10x.
  *******************************************************************************
  * @changelog
  * 2025-05-01: 
  *
  * Copyright (c) 2025-2025 oscar(happydrones123@gmail.com). All rights reserved.
  ******************************************************************************
  */




#include "rtc.h"

//月份数据表     
uint16_t ryear;
uint8_t rmon,rday,rhour,rmin,rsec,rweek;
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表  
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//平年的月份日期表


/**
  * @brief  初始化RTC并设置为低速外部晶振（LSE）模式。
  * @param  None
  * @retval None
  */
static void RTC_InitWithLS(void)
{
	// Initial configuration for RTC setup
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//启用PWR和BKP的时钟（from APB1） PWR 寄存器包含BKP寄存器写保护保护
    //后备域解锁
	PWR_BackupAccessCmd(ENABLE);
	//备份寄存器模块复位
    BKP_DeInit();
	//RTC时钟源配置成LSE（外部低速晶振32.768KHZ）
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); 
	//外部32.768KHZ晶振开启 
    RCC_LSEConfig(RCC_LSE_ON); 
	//等待稳定    
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);   
    RCC_RTCCLKCmd(ENABLE);//使能RTCCLK RTC开启    
    RTC_WaitForSynchro();//开启后需要等待APB1时钟与RTC时钟同步，才能读写寄存器    
    RTC_WaitForLastTask();//读写寄存器前，要确定上一个操作已经结束
    RTC_SetPrescaler(32767);//设置RTC分频器，使RTC时钟为1Hz,RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)   
    RTC_WaitForLastTask();//等待寄存器写入完成	
    //当不使用RTC秒中断，可以屏蔽下面2条
    //RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能秒中断   
    //RTC_WaitForLastTask();//等待写入完成
}

/**
 * @brief  配置RTC并设置为低速外部晶振（LSE）模式。
 * @details 该函数首先检查后备寄存器1中的数据是否为0xAAAA，
 *          若数据丢失，则重新配置RTC并设置后备寄存器1为0xAAAA。
 *          若数据未丢失，则检查复位类型，并清除复位标志。
 *          最后，使能RTC时钟并等待其与APB1时钟同步。
 * @param  None
 * @retval None
 * 
 */
void RTC_Config(void)
{
/*
	//实时时钟初始化
    //在BKP的后备寄存器1中，存了一个特殊字符0xAAAA
    //第一次上电或后备电源掉电后，该寄存器数据丢失，表明RTC数据丢失，需要重新配置
*/
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xAAAA)
	{
		//判断寄存数据是否丢失       
        RTC_InitWithLS();//重新配置RTC        
        BKP_WriteBackupRegister(BKP_DR1, 0xAAAA);//配置完成后，向后备寄存器中写特殊字符0xAAAA
    }
	else
	{
		//若后备寄存器没有掉电，则无需重新配置RTC
        //这里我们可以利用RCC_GetFlagStatus()函数查看本次复位类型
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
		{
            //这是上电复位
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
		{
            //这是外部RST管脚复位
        }       
        RCC_ClearFlag();//清除RCC中复位标志

        //虽然RTC模块不需要重新配置，且掉电后依靠后备电池依然运行
        //但是每次上电后，还是要使能RTCCLK
        RCC_RTCCLKCmd(ENABLE);//使能RTCCLK  RTC开启  不属于后备寄存器  				
        RTC_WaitForSynchro();//等待RTC时钟与APB1时钟同步

        //当不使用RTC秒中断，可以屏蔽下面2条
		//RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能秒中断        
		//RTC_WaitForLastTask();//等待操作完成
    }
	/* //是否启动 RCC输出工功能
	#ifdef RTCClockOutput_Enable   
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	    PWR_BackupAccessCmd(ENABLE); //后备域解锁  
	    BKP_TamperPinCmd(DISABLE);   
	    BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
	#endif
	*/
}




/**
 * @brief  RTC中断处理函数。
 * @details 该函数处理RTC的中断事件，主要针对秒中断进行处理。
 *          在函数中，首先检查秒中断标志是否被置位，如果被置位则执行相应的中断处理逻辑。
 *          最后，清除秒中断待处理位并等待最后一个任务完成。
 * @param  无
 * @retval 无
 */
void RTC_IRQHandler(void)
{ 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{

	}
	RTC_ClearITPendingBit(RTC_IT_SEC); 
	RTC_WaitForLastTask();
}

/**
  * @brief  RTC闹钟中断处理函数。
  * @details 该函数处理RTC的闹钟中断事件。首先检查闹钟中断标志是否被置位，
  *          如果被置位则执行相应的中断处理逻辑。最后，清除闹钟中断待处理位
  *          并等待最后一个任务完成。
  * @param  无
  * @retval 无
  */
void RTCAlarm_IRQHandler(void)
{	
	if(RTC_GetITStatus(RTC_IT_ALR) != RESET)	
	{
	
	}
	RTC_ClearITPendingBit(RTC_IT_ALR);
	RTC_WaitForLastTask();
}


/**
  * @brief  判断指定年份是否为闰年。
  * @param  year: 要判断的年份。
  * @retval 如果是闰年返回1，否则返回0。
  * 
  * @note		闰年的判断规则：
  * 			1. 年份能被4整除但不能被100整除
  * 			2. 年份能被400整除
  */
u8 Is_Leap_Year(u16 year)
{                    
	if(year%4==0)
		{ //必须能被4整除
		if(year%100==0)
			{		
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除          
			else return 0;  
		  }else return 1;  
	  }else return 0;
}                           
//设置时钟
//把输入的时钟转换为秒钟
//以1970年1月1日为基准
//1970~2099年为合法年份


/**
  * @brief  设置RTC的时间。
  * @param  syear: 要设置的年份（1970~2099年有效）。
  * @param  smon: 要设置的月份（1~12）。
  * @param  sday: 要设置的日期（1~31）。
  * @param  hour: 要设置的小时（0~23）。
  * @param  min: 要设置的分钟（0~59）。
  * @param  sec: 要设置的秒（0~59）。
  * @retval 0: 设置成功；1: 年份超出有效范围。
  */
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)//写入当前时间（1970~2099年有效），
{ 
	u16 t;
	u32 seccount=0;
	if(syear<2000||syear>2099)return 1;//syear范围1970-2099，此处设置范围为2000-2099       
	for(t=1970;t<syear;t++)
	{ 	
		//把所有年份的秒钟相加
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;                    //平年的秒钟数
	}
	
	smon-=1;
	for(t=0;t<smon;t++)
	{         //把前面月份的秒钟数相加
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)
		{
			seccount+=86400;//闰年2月份增加一天的秒钟数     
		}   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加
	seccount+=(u32)hour*3600;//小时秒钟数
	seccount+=(u32)min*60;      //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//启用PWR和BKP的时钟（from APB1） PWR 寄存器包含BKP寄存器写保护保护
	PWR_BackupAccessCmd(ENABLE);//后备域解锁
	//RTC_First_Config(); //重新初始化时钟	 
	RTC_SetCounter(seccount);//把换算好的计数器值写入
	RTC_WaitForLastTask(); //等待写入完成
	return 0; //返回值:0,成功;其他:错误代码.    
}

//读出时间

/**
  * @brief  .
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *   This parameter can be one of the following values:
  *     @arg PWR_Regulator_ON: STOP mode with regulator ON
  *     @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
  *     @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
  * @retval None
  */
u8 RTC_Get(void)//读出当前时间值 //返回值:0,成功;其他:错误代码.
{
	static u16 daycnt=0;
	u32 timecount=0;
	u32 temp=0;
	u16 temp1=0;
	timecount=RTC_GetCounter();		
	temp=timecount/86400;   //得到天数(秒钟数对应的)
	if(daycnt!=temp)
	{//超过一天了
		daycnt=temp;
		temp1=1970;  //从1970年开始
		while(temp>=365)
		{
			if(Is_Leap_Year(temp1))
			{	//是闰年
			    if(temp>=366)
					temp-=366;//闰年的秒钟数
			    else 
				{
					temp1++;
					break;
				} 
		    }
		    else temp-=365;       //平年
		    temp1++; 
		}  
		ryear=temp1;//得到年份
		temp1=0;
		while(temp>=28)
		{	//超过了一个月
			if(Is_Leap_Year(ryear)&&temp1==1)
			{	//当年是不是闰年/2月份
				if(temp>=29)
					temp-=29;//闰年的秒钟数
				else 
					break;
			}
			else
			{
	            if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
	            else break;
			}
			temp1++; 
		}
		rmon=temp1+1;//得到月份
		rday=temp+1;  //得到日期
	}
	temp=timecount%86400;     //得到秒钟数      
	rhour=temp/3600;     //小时
	rmin=(temp%3600)/60; //分钟     
	rsec=(temp%3600)%60; //秒钟
	rweek=RTC_Get_Week(ryear,rmon,rday);//获取星期  
	return 0;
} 

//按年月日计算星期(只允许1901-2099年)//已由RTC_Get调用  

/**
  * @brief  Enters STOP mode.
  * @param  PWR_Regulator: specifies the regulator state in STOP mode.
  *   This parameter can be one of the following values:
  *     @arg PWR_Regulator_ON: STOP mode with regulator ON
  *     @arg PWR_Regulator_LowPower: STOP mode with regulator in low power mode
  * @param  PWR_STOPEntry: specifies if STOP mode in entered with WFI or WFE instruction.
  *   This parameter can be one of the following values:
  *     @arg PWR_STOPEntry_WFI: enter STOP mode with WFI instruction
  *     @arg PWR_STOPEntry_WFE: enter STOP mode with WFE instruction
  * @retval None
  */
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{   
	u16 temp2;
	u8 yearH,yearL;
	yearH=year/100;     
	yearL=year%100;
	// 如果为21世纪,年份数加100 
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的 
	temp2=yearL+yearL/4;
	temp2=temp2%7;
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7); //返回星期值
}
