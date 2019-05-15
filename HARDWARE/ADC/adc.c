 #include "adc.h"
 #include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
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
	   
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 

	
	

    ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_55Cycles5);

    ADC_AutoInjectedConvCmd(ADC1, ENABLE);
//    ADC_ExternalTrigInjectedConvEdgeConfig(ADC3, ADC_ExternalTrigInjecConvEdge_None); 
    ADC_InjectedSequencerLengthConfig(ADC1, 4);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_0, 1,ADC_SampleTime_55Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_1, 2,ADC_SampleTime_55Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_2, 3,ADC_SampleTime_55Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_3, 4,ADC_SampleTime_55Cycles5);
    ADC_Cmd(ADC1, ENABLE);
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
	
	
//			a0 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
//			a1 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
//			a2 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_3);
//			a3 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_4);

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 


//void Get_Adc_Window0(u8 ch)
//{
//	 c0[time0]=ADC_GetInjectedConversionValue(ADC1, ch);  // ��ȡADCע��ͨ��ֵ
//	 time0++;
//	 if(time0>=202)
//	 {
//		 
//		 u8 i=0;
//		 for(i=0;i<=200;i++)
//		 {
//			 c0[i]=c0[i+1];
//			 b0[i]=c0[i];
//		 }
//	 	 time0=201;
//	 }
//} 	 

//void Get_Adc_Window1(u8 ch)
//{
//	 c1[time1]=ADC_GetInjectedConversionValue(ADC1, ch);
//	 time1++;
//	 if(time1>=202)
//	 {
//		 
//		 u8 i=0;
//		 for(i=0;i<=200;i++)
//		 {
//			 c1[i]=c1[i+1];
//			 b1[i]=c1[i];
//		 }
//	 	 time1=201;
//	 }
//} 	 

//void Get_Adc_Window2(u8 ch)
//{
//	 c2[time2]=ADC_GetInjectedConversionValue(ADC1, ch);
//	 time2++;
//	 if(time2>=202)
//	 {
//		 
//		 u8 i=0;
//		 for(i=0;i<=200;i++)
//		 {
//			 c2[i]=c2[i+1];
//			 b2[i]=c2[i];
//		 }
//	 	 time2=201;
//	 }
//} 	 
//void Get_Adc_Window3(u8 ch)
//{
//	 c3[time3]=ADC_GetInjectedConversionValue(ADC1, ch);
//	 time3++;
//	 if(time3>=202)
//	 {
//		 
//		 u8 i=0;
//		 for(i=0;i<=200;i++)
//		 {
//			 c3[i]=c3[i+1];
//			 b3[i]=c3[i];
//		 }
//	 	 time3=201;
//	 }
//} 	 


void Get_Adc_Window00(u8 ch)
{  
//	 time0=0;
	u8 i=0;
	for(i=0;i<=200;i++)
	 {
	 b0[i]=ADC_GetInjectedConversionValue(ADC1, ch);

	 }		 
} 
void Get_Adc_Window11(u8 ch)
{  
	u8 i=0;
	for(i=0;i<=200;i++)
	 {
	 b1[i]=ADC_GetInjectedConversionValue(ADC1, ch);

	 }		 
} 

void Get_Adc_Window22(u8 ch)
{  
	u8 i=0;
	for(i=0;i<=200;i++)
	 {
	 b2[i]=ADC_GetInjectedConversionValue(ADC1, ch);

	 }		 
} 

void Get_Adc_Window33(u8 ch)
{  
	u8 i=0;
	for(i=0;i<=200;i++)
	 {
	 b3[i]=ADC_GetInjectedConversionValue(ADC1, ch);

	 }		 
} 


























