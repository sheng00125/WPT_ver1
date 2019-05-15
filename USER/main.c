#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "median_filter.h"
#include "nokia_5110.h" 
#include "timer3.h"
/* 
使用说明 	
TIM1的CH1和CH1N 产生带有死区的PWM波
TIM8的CH2和CH2N 产生带有死区的PWM波
同时 TIM1和TIM8波形有一定可控相位差
1.频率调节 TIM1_PWM_Init(1160,0);	TIM8_PWM_Init(1160,0);中的数
2.占空比调节 改变 TIM_SetCompare1(TIM1,580);	TIM_SetCompare2(TIM8,580); 580/1160 
3.移项角改变   改变TIM1_PWM_Init函数中的TIM1->CCR2值
4.改变死区时间 改变TIM1_PWM_Init函数和TIM8_PWM_Init函数中的TIM_BDTRInitStructure.TIM_DeadTime 
  死区时间计算参考： https://www.cnblogs.com/NickQ/p/8550901.html

*/	

// ADC1 Chanel0,1,2,3  -> PA0,1,2,3
	u16 adcx0,adcx1,adcx2,adcx3;
	float temp0,temp1,temp2,temp3,temp;
int a1,a2,a3,a0,a;
u16 I1=0;
int b0[200]={0};int b1[200]={0};int b2[200]={0};int b3[200]={0};
int c0[201],c1[201],c2[201],c3[201];
u8 time0=0;u8 time1=0;u8 time2=0;u8 time3=0;
    char str0[10]="0";   // 数组长度不能取太小否则显示部分乱码
		char str1[10]="0";
		char str2[10]="0";
		char str3[10]="0";
float Target_Uo=60.0;
u8 D=50;    // 通道1占空比
extern int pwm;
 int main(void)
 {		
	int f=71728;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化
	TIM3_Int_Init(199,7199);//10Khz的计数频率，计数到200为20ms  
	TIM4_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz
  TIM1_PWM_Init((int)(72000000/f),0);	 //不分频。PWM频率=72000000/1028=69Khz
	TIM8_PWM_Init((int)(72000000/f),0);	 //不分频。PWM频率=72000000/1028=69Khz
	Adc_Init();		  		//ADC初始化

	LCD_init(); //?????    
	LCD_clear(); 
	 pwm=180;
	 
	 	TIM_SetCompare1(TIM1,(int)(1028/2));		   // 设置TIM1通道1占空比 = 580/1160
		TIM_SetCompare2(TIM8,(int)(1028/2));		   // 设置TIM8通道2占空比 = 580/1160
	 
   	while(1)
	{								 


// ADC实时采集数据并排序
		Get_Adc_Window00(ADC_InjectedChannel_1);
		Get_Adc_Window11(ADC_InjectedChannel_2);
		Get_Adc_Window22(ADC_InjectedChannel_3);
		Get_Adc_Window33(ADC_InjectedChannel_4);
		a0= GetMedianNum(b0, 201);
		a1= GetMedianNum(b1, 201);
		a2= GetMedianNum(b2, 201);
		a3= GetMedianNum(b3, 201);
// Boost PWM		
		TIM_SetCompare1(TIM4,pwm);		   
		TIM_SetCompare2(TIM4,pwm+10);	
// 显示器处理		
    sprintf(str0,"%.2f",temp0);
		sprintf(str1,"%.2f",temp1);
		sprintf(str2,"%.2f",temp2);
		sprintf(str3,"%.2f",temp3);
		
		LCD_write_english_string(0,0,"Iin:");
		LCD_write_english_string(30,0,str0);
		LCD_write_english_string(75,0,"A");
		
		LCD_write_english_string(0,9,"Vin:");
		LCD_write_english_string(30,9,str1);
		LCD_write_english_string(75,9,"V");
		
		LCD_write_english_string(0,18,"Iout:");
		LCD_write_english_string(30,18,str2);
		LCD_write_english_string(75,18,"A");
		
		LCD_write_english_string(0,27,"Vout:");
		LCD_write_english_string(30,27,str3);
		LCD_write_english_string(75,27,"V");
		
		LCD_write_english_string(0,37,"e:");
    LCD_write_english_string(30,37,"0.85");
		LCD_write_english_string(75,37,"%");

	}	 
 }

