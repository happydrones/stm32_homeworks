//********************GPIO输出操作流程笔记*********************************************************************************
   GPIO输出操作流程笔记
1.启动总线时钟：所有GPIO都在APB2总线上（中文参考手册25页）
举例：
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//启动APB2总线 PA组IO总时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, DISABLE);//关闭APB2总线 PA组IO总线时钟

2.设置GPIO工作模式：
 ① 选择IO哪一位               
 ② 选择IO工作方式 
 ③ 选择IO口速度
 ④ GPIO_Init函数	
 
举例：
GPIO_InitTypeDef  GPIO_InitStruct;

GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;                     //选择第 0 位IO      
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //选择推挽输出
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //选择输出速度  50MHz
	
GPIO_Init(GPIOB, &GPIO_InitStruct);    //通过GPIO_Init固件库函数 一次性把参数写进去  PB0 推挽输出 50MHz 速度	
（参考中文固件库手册124页）
	
3.设置GPIO输出状态：

 ① GPIO写位操作          GPIO_WriteBit函数
 ② GPIO置位操作          GPIO_SetBits 置“1”函数    GPIO_ResetBits 置“0”函数
 ③ GPIO总线整组操作      GPIO_Write函数 
	
1.GPIO写位操作： Bit_SET 1   Bit_RESET  0
GPIO_WriteBit(GPIOB,GPIO_Pin_0,1);   //PB0 输出 1
GPIO_WriteBit(GPIOB,GPIO_Pin_0,0);   //PB0 输出 0

2.GPIO置位操作：
GPIO_SetBits(GPIOB,GPIO_Pin_0);         //PB0 输出 1
GPIO_ResetBits(GPIOB,GPIO_Pin_0);     //PB0 输出 0

3.GPIO总线整组操作：
GPIO_Write(GPIOB,0x0000);   //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 0
GPIO_Write(GPIOF,0xFFFF);    //直接操作16位整组GPIOF输出  0X0000  16个GPIO全部输出 1

注意：存在IO复用， 需要调用下面 函数  释放所有 gpio输出功能。 

void PC_PA_13_14_15_Gpio(void);//PB2 PB3 释放  函数申明
void PC_PA_13_14_15_Gpio(void) //
{

	  //rtc作为io，需要先取消rtc备用纽扣电池配置好后再装电池或不装
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE );
	  	  //RCC_APB2Periph_AFIO IO功能复用AFIO 时钟 改变默认功能 恢复IO口功能
    PWR_BackupAccessCmd( ENABLE );/* 允许修改RTC和后备寄存器*/
    RCC_LSEConfig( RCC_LSE_OFF ); /* 关闭外部低速时钟,PC14+PC15可以用作普通IO*/
    BKP_TamperPinCmd(DISABLE);  /* 关闭入侵检测功能,PC13可以用作普通IO*/

	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //恢复PA13  PA14  PA15 IO功能，默认位jtag swd下载功能
	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    PWR_BackupAccessCmd(DISABLE);/* 禁止修改RTC和后备寄存器*/
    //BKP_ITConfig(DISABLE);       /* 禁止TAMPER 中断*/

}
//********************GPIO输入操作流程笔记*********************************************************************************



//********************GPIO输入操作流程笔记*********************************************************************************





