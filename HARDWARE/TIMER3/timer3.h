#ifndef __TIMER3_H
#define __TIMER3_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);

extern	u16 adcx0,adcx1,adcx2,adcx3;
extern	float temp0,temp1,temp2,temp3,temp;
extern int a1,a2,a3,a0,a;
 
#endif
