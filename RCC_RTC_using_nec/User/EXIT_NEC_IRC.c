#include "EXIT_NEC_IRC.h"
#include "delay.h"

u8 Key_NEC_IRC_Data = 0;   //NEC����ң�ؼ�ֵ
u8 Key_NEC_IRC_Add  = 0;   //NEC����ң�ص�ַ
/*********************************************************************
*�������ƣ�NVIC_Configuration(void)
*�������ܣ�ѡ���ж����ȵȼ����� 
*�������ã�NVIC_Configuration();
*�����б���
*�� �� ֵ����
*��    ����
*��    ע��
*********************************************************************/
//********************************************************************* 
void NVIC_Configuration(void)
{   
	  // 5.����NVIC���ȼ���
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	  
}
//*********************************************************************
/*********************************************************************
*�������ƣ�EXTI_NEC_IRC_Key_Config(void)
*�������ܣ�NEC�жϺ�������ʼ��
*�������ã�EXTI_NEC_IRC_Key_Config();
*�����б���
*�� �� ֵ����
*��    ����
*��    ע����Ҫ��ȡ����ң�����ݣ���������������øú������ж�����
*********************************************************************/
//*********************************************************************
void EXTI_NEC_IRC_Key_Config(void)
{ 
	// 5.����NVIC���ȼ���
	NVIC_Configuration();
//	// 5.����NVIC���ȼ���
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	//1.��EXTI�ⲿGPIO,AFIO,RCCʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //�������ж�GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//��AFIOʱ�� 
	
	//2.EXTI�ⲿ�ж���GPIOģʽ����
  GPIO_InitTypeDef GPIO_InitStructure; //����GPIO�ĳ�ʼ���ṹ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;            //ѡ��˿ں�   
	
	//GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            //ѡ��˿ں� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //ѡ��IO�ӿڹ�����ʽ //�������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //����IO�ӿ��ٶȣ�2/10/50MHz�� ���Բ������ٶ�
	GPIO_Init(GPIOB,&GPIO_InitStructure);	

	//3.ѡ��EXTI�ⲿ�ж��ź�Դ
  EXTI_InitTypeDef  EXTI_InitStructure;   //����ṹ�����	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);  //ѡ��GPIO�ⲿ�ж��ж������	

		
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;              //�����ж���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;               //�ж�ʹ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;     //�ж�ģʽΪ �ж�
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //�½��ش���
	
	EXTI_Init(& EXTI_InitStructure);	
   		
	//4.����NVIC�ж����ȼ�
  NVIC_InitTypeDef NVIC_InitStructure;
   
  NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;   //�ж���    
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;    //ʹ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //��ռ���ȼ� 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;         //��Ӧ���ȼ� 2
	
	NVIC_Init(& NVIC_InitStructure);
	
   
}
//*********************************************************************
/*********************************************************************
*�������ƣ�u32 Get_NEC_RxLow_level(void) 
*�������ܣ�NEC����Э�� �����͵�ƽʱ��
*�������ã�u32 Get_NEC_RxLow_level();
*�����б���
*�� �� ֵ���͵�ƽʱ�䵥λ΢��
*��    ����
*��    ע��
*********************************************************************/
//*********************************************************************
u32 Get_NEC_RxLow_level(void) 
{
u32 time  =0;  //�����ƽʱ��
                      	
SysTick->VAL=0x00;               //��ն�ʱ���ļ����� д������ֵ���������ʱ����ͬʱ������־λ��COUNTFLAG��Ҳ���Զ����� 
SysTick->LOAD= 0xffffff; //��װ������ֵ������Ƶ��72MHz��72��Ϊ1΢�� 24λ������ʱ����
SysTick->CTRL=0x00000005;        //ʱ��ԴHCLK���򿪶�ʱ��    	
while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0);
SysTick->CTRL=0;//�رն�ʱ�� 	
time = (0x00ffffff-(SysTick->VAL)&0x00ffffff)/72 ; //����Ƶ��72MHz��72��Ϊ1΢�� 24λ������ʱ��

/* //�����ú�����ʽ�����̫�󣬽���ң��ʱ�� ����ֱ�ӴӼĴ�������ʱ�䷽ʽ   
	 while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)
	 {
		  time_NEC++;  //�����ƽʱ��
	    SysTick_Delay_us(10);
	 }
*/
	 return time;	 
}
//*********************************************************************
/*********************************************************************
*�������ƣ�u32 Get_NEC_RxHigh_level(void) 
*�������ܣ�NEC����Э�� �����ߵ�ƽʱ��
*�������ã�Get_NEC_RxHigh_level();
*�����б���
*�� �� ֵ���ߵ�ƽʱ�䵥λ΢��
*��    ���� 
*��    ע��
*********************************************************************/
//*********************************************************************
u32 Get_NEC_RxHigh_level(void) 
{
u32 time =0;  //�����ƽʱ��	
SysTick->VAL=0x00;               //��ն�ʱ���ļ����� д������ֵ���������ʱ����ͬʱ������־λ��COUNTFLAG��Ҳ���Զ����� 
SysTick->LOAD= 0xffffff; //��װ������ֵ������Ƶ��72MHz��72��Ϊ1΢�� 24λ������ʱ����
SysTick->CTRL=0x00000005;        //ʱ��ԴHCLK���򿪶�ʱ��
	
while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 1);
SysTick->CTRL=0;//�رն�ʱ�� 	
time = (0x00ffffff-(SysTick->VAL)&0x00ffffff)/72 ; //����Ƶ��72MHz��72��Ϊ1΢�� 24λ������ʱ��

	return time;
}
//*********************************************************************
/*********************************************************************
*�������ƣ�EXTI9_5_IRQHandler(void) 
*�������ܣ�NEC����Э�� �жϺ�������
*�������ã��жϺ�����������Զ�����
*�����б���
*�� �� ֵ����
*��    ���� ȫ�ֱ�������main����ͨ��extern���ü��ɻ�ú���ң������
            ��ң�ص�ַ��Key_NEC_IRC_Add   ����ң�ؼ�ֵ���ݣ�Key_NEC_IRC_Data
*��    ע�� �ý��뺯��������ӿ������ 
            ���̰�ʶ���ܿ������������Ͻ���ʱ���ۼ��ж�ʵ��
*********************************************************************/
//*********************************************************************
void EXTI9_5_IRQHandler(void)
{
   u32 time_NEC=0,j,i;
	 u8 data=0X00;	
   u8 NEC_IRC_4Byte[4];	    //����NECЭ������
	 u8 Start_Repeat_Flag = 0;  //�ж���ʼ�źŻ����ظ��ź�  Start   1   
   static u8 NEC_Last_Data  = 0;    //��һ�μ�ֵ	
	
	if (EXTI_GetITStatus(EXTI_Line9) == SET)
	{
		 	EXTI_ClearITPendingBit(EXTI_Line9);  //����жϱ�־λ	
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)
		{
					/*1. �ж���������ظ��ź�*/
					time_NEC = Get_NEC_RxLow_level(); //NEC����Э�� ��ȡ�͵�ƽʱ��
					if(time_NEC<8000||time_NEC>10000) return; //����͵�ƽʱ�� С��8000us���ߴ���us���붪��
					time_NEC = Get_NEC_RxHigh_level();//NEC����Э�� ��ȡ�ߵ�ƽʱ��
			    if(time_NEC<1500||time_NEC>5500)return;  //����ߵ�ƽʱ��С��1500us�����5500us����
			    //Star�ź� �͵�ƽ9000us �ߵ�ƽ4500us     Repeat�źŵ͵�ƽ9000us �ߵ�ƽ2500us
			
					if(time_NEC<3500)  //Repeat�ظ��ź�
					{ 
          Key_NEC_IRC_Data = NEC_Last_Data;    //������һ�μ�ֵ											
			    return; //ʶ����Repeat�ظ��źţ��˳����������ݽ���
					}
					else						//����Start�ź� 
					{	
						 
					  Start_Repeat_Flag = 1;  //�ж���ʼ�źŻ����ظ��ź�  Start   1    
					}	
			    
          //EXTI_Cont= time_NEC; //����ʶ�𵽵ĵ�ƽʱ�� *1us ͨ��1602Һ����ʾ�����۲�ʵ��ʱ��		
					
					/*2. �����û���Ͱ�����*/
					if(Start_Repeat_Flag == 1) //�ж���ʼ�źŻ����ظ��ź�  Start   1   
					{
					for(i=0;i<4;i++)
					{
							for(j=0;j<8;j++)
							{
									time_NEC= Get_NEC_RxLow_level(); //NEC����Э�� ��ȡ�͵�ƽʱ��
									if(time_NEC<460||time_NEC>660)return;  //���� 0  ����1 ��ƽ����560us
									
									time_NEC=Get_NEC_RxHigh_level(); //NEC����Э�� ��ȡ�ߵ�ƽʱ��
									//560us�ߵ�ƽ  0    1680us�ߵ�ƽ 1
									if(time_NEC>460&&time_NEC<660)
									{
										data>>=1;  //���λд 0
									}
									else if(time_NEC>1590&&time_NEC<1790)
									{
										 data>>=1;          
										 data|=0x80; //1000 0000  ���λд1
									}
							}
							NEC_IRC_4Byte[i]= data;
					}
					//if((~NEC_IRC_4Byte[0] == NEC_IRC_4Byte[1]) && (~NEC_IRC_4Byte[2] == NEC_IRC_4Byte[3]))
					//if( (~0xff) == (0x00))
					
					//���������� Ч�鲢���¼�ֵ����
					if( (!(NEC_IRC_4Byte[0] & NEC_IRC_4Byte[1])) && (!(NEC_IRC_4Byte[2] & NEC_IRC_4Byte[3])))				
					{
					  Key_NEC_IRC_Add  = NEC_IRC_4Byte[0];   //NEC����ң�ص�ַ								
            Key_NEC_IRC_Data = NEC_IRC_4Byte[2];   //NEC����ң�ؼ�ֵ	
						
            NEC_Last_Data = Key_NEC_IRC_Data;      //������һ�μ�ֵ	��Repeat �ظ�����һ�μ�ֵ��ʵ�ֿ�+ ��- ����										
					}			 
					
					}
				
		}

	}

}


 
