#include "EXIT_NVIC.h"
#include "1602lcd.h"
#include "delay.h"

u16 EXTI_Cont=0; //�жϽ��������־λ
extern u8 EXTI_Test_Num;  //���� ����ִ�е� λ�� ��־  �������򣺵���0���жϷ�����0  ����1 ���жϷ�����2 ����2��

/*********************************************************************
*�������ƣ�NVIC_Configuration(void)
*�������ܣ� 
*�������ã�
*�����б���
*�� �� ֵ����
*��    ����
*��    ע��
*********************************************************************/
void NVIC_Configuration(void)
{   
	  // 5.����NVIC���ȼ���
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	  
}

void EXTI_Key_Config(void)
{ 
	// 5.����NVIC���ȼ���
	NVIC_Configuration();
//	// 5.����NVIC���ȼ���
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	//1.��EXTI�ⲿGPIO,AFIO,RCCʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //�������ж�GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//��AFIOʱ�� 
	
	//2.EXTI�ⲿ�ж���GPIOģʽ����
  GPIO_InitTypeDef GPIO_InitStructure; //����GPIO�ĳ�ʼ���ṹ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;            //ѡ��˿ں�   
	
	//GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;            //ѡ��˿ں� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //ѡ��IO�ӿڹ�����ʽ //�������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //����IO�ӿ��ٶȣ�2/10/50MHz�� ���Բ������ٶ�
	GPIO_Init(GPIOC,&GPIO_InitStructure);	

	//3.ѡ��EXTI�ⲿ�ж��ź�Դ
  EXTI_InitTypeDef  EXTI_InitStructure;   //����ṹ�����	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);  //ѡ��GPIO�ⲿ�ж��ж������	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);  //ѡ��GPIO�ⲿ�ж��ж������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);  //ѡ��GPIO�ⲿ�ж��ж������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);  //ѡ��GPIO�ⲿ�ж��ж������
		
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;              //�����ж���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;               //�ж�ʹ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;     //�ж�ģʽΪ �ж�
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //�½��ش���
	
	EXTI_Init(& EXTI_InitStructure);	
//***********************************************************************
   //KE2 ʹ������ѡ��EXTI�ⲿ�ж��ź�Դ
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;              //�����ж���	
	EXTI_Init(& EXTI_InitStructure);
//***********************************************************************		
   //KE3 ʹ������ѡ��EXTI�ⲿ�ж��ź�Դ
  EXTI_InitStructure.EXTI_Line=EXTI_Line2;              //�����ж���	
	EXTI_Init(& EXTI_InitStructure);
//***********************************************************************		
   //KE4 ʹ������ѡ��EXTI�ⲿ�ж��ź�Դ
  EXTI_InitStructure.EXTI_Line=EXTI_Line3;              //�����ж���	
	EXTI_Init(& EXTI_InitStructure);	
//***********************************************************************			
	//4.����NVIC�ж����ȼ�
  NVIC_InitTypeDef NVIC_InitStructure;
   
  NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;   //�ж���    
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;    //ʹ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //��ռ���ȼ� 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;         //��Ӧ���ȼ� 2
	
	NVIC_Init(& NVIC_InitStructure);
	
//***********************************************************************		
   //KE2 	ʹ����������NVIC�ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;   //�ж���
	NVIC_Init(& NVIC_InitStructure);
//***********************************************************************		
   //KE3 	ʹ����������NVIC�ж����ȼ�	 
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;   //�ж���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;  //��ռ���ȼ� 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;         //��Ӧ���ȼ� 2	

	NVIC_Init(& NVIC_InitStructure);
//***********************************************************************		
   //KE4 	ʹ����������NVIC�ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;   //�ж���
	NVIC_Init(& NVIC_InitStructure);
//***********************************************************************			
}

//EXTI0_IRQHandler
//�ⲿ�жϷ�����
void EXTI0_IRQHandler(void)
{
	//EXTI_Cont ++;//�жϽ��������־λ
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			EXTI_Cont ++;//�жϽ��������־λ 
			Display_Lcd_1602_Number(2,11,1,5);//1602����λ��д��ʮ������
			Delay_ms(1000); //�ӳ�  X_ms*1  Ĭ��״̬������rcc Ĭ��ʱ��
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
		EXTI_Test_Num   = 1;  //���� ����ִ�е� λ�� ��־  �������򣺵���0���жϷ�����0  ����1 ���жϷ�����2 ����2��
	}

}/*
//�ⲿ�жϷ�����
void EXTI1_IRQHandler(void)
{
	//EXTI_Cont ++;//�жϽ��������־λ
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
		{
			EXTI_Cont ++;//�жϽ��������־λ
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}*/
//�ⲿ�жϷ�����
void EXTI2_IRQHandler(void)
{
	//EXTI_Cont ++;//�жϽ��������־λ
	if (EXTI_GetITStatus(EXTI_Line2) == SET)
	{
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == 0)
		{
			EXTI_Cont --;//�жϽ��������־λ		
			Display_Lcd_1602_Number(2,11,2,5);//1602����λ��д��ʮ������
			Delay_ms(1000); //�ӳ�  X_ms*1  Ĭ��״̬������rcc Ĭ��ʱ��		
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
  EXTI_Test_Num   = 2;  //���� ����ִ�е� λ�� ��־  �������򣺵���0���жϷ�����0  ����1 ���жϷ�����2 ����2��
}
/*
//�ⲿ�жϷ�����
void EXTI3_IRQHandler(void)
{
	//EXTI_Cont ++;//�жϽ��������־λ
	if (EXTI_GetITStatus(EXTI_Line3) == SET)
	{
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			EXTI_Cont --;//�жϽ��������־λ
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
 */
/*******************************************
//�������ⲿ�жϷ����� ģ��
void EXTI4_IRQHandler(void)
{
	//EXTI_Cont ++;//�жϽ��������־λ
	if (EXTI_GetITStatus(EXTI_Line3) == SET)
	{
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			EXTI_Cont --;//�жϽ��������־λ
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

void  EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		//��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
**********************************************************************/
