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
//********************GPIO输出操作流程笔记*********************************************************************************