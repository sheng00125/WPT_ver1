 #include "adc.h"
 #include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 

	
	

    ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_55Cycles5);

    ADC_AutoInjectedConvCmd(ADC1, ENABLE);
//    ADC_ExternalTrigInjectedConvEdgeConfig(ADC3, ADC_ExternalTrigInjecConvEdge_None); 
    ADC_InjectedSequencerLengthConfig(ADC1, 4);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_0, 1,ADC_SampleTime_55Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_1, 2,ADC_SampleTime_55Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_2, 3,ADC_SampleTime_55Cycles5);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_3, 4,ADC_SampleTime_55Cycles5);
    ADC_Cmd(ADC1, ENABLE);
	  ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	
	
//			a0 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
//			a1 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
//			a2 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_3);
//			a3 = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_4);

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
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
//	 c0[time0]=ADC_GetInjectedConversionValue(ADC1, ch);  // 获取ADC注入通道值
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


























