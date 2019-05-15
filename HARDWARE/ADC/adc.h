#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
void Get_Adc_Window0(u8 ch);
void Get_Adc_Window1(u8 ch);
void Get_Adc_Window2(u8 ch);
void Get_Adc_Window3(u8 ch);

void Get_Adc_Window00(u8 ch);
void Get_Adc_Window11(u8 ch);
void Get_Adc_Window22(u8 ch);
void Get_Adc_Window33(u8 ch);

#define Time 200
#define Time1 201
 
 
extern int b0[200];
extern int b1[200];
extern int b2[200];
extern int b3[200];
extern int c0[201];
extern int c1[201];
extern int c2[201];
extern int c3[201];
extern u8 time0;
extern u8 time1;
extern u8 time2;
extern u8 time3;
#endif 
