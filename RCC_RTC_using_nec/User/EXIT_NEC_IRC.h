#ifndef __EXIT_NEC_IRC_H__
#define __EXIT_NEC_IRC_H__	 
#include "sys.h"


void NVIC_Configuration(void); //Ƕ���жϿ�����������
void EXTI_NEC_IRC_Key_Config(void);//NEC�жϺ�������ʼ��

 
u32 Get_NEC_RxLow_level(void); //NEC����Э�� ��ȡ�͵�ƽʱ��
u32 Get_NEC_RxHigh_level(void);//NEC����Э�� ��ȡ�ߵ�ƽʱ��
#endif
