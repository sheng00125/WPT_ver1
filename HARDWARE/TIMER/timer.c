#include "timer.h"
#include "led.h"
#include "usart.h"


//TIM1 CH1 PWM������� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	
 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO, ENABLE); //ʹ��TIMx����

  TIM_DeInit(TIM1);
  TIM_InternalClockConfig(TIM1);
 
  //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIO
 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM1_CH1N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
	
	TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2ģʽ	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �͵�ƽ��Ч 
	 //
 TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;	//???????
 TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;	
 TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; 	//???????
 TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
 TIM_OC1Init(TIM1,&TIM_OCInitStructure);   	//����ָ���Ĳ�����ʼ������TIMx
 TIM_OC2Init(TIM1,&TIM_OCInitStructure);


//��������ʱ��
 TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
 TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
 TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
 TIM_BDTRInitStructure.TIM_DeadTime = 7; 	// 7*Tdts  =1/72M = 7*13.89ns
 TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable; //??????
 TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;	//??????
 TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
 TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);  



	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1 Ԥװ��ʹ��
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��,�߼���ʱ�����뿪����� 
	
	TIM1->CCR2=300;         // �ı������
	
	TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             
	NVIC_Init(&NVIC_InitStructure);                            
	
	
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx
	   										  
} 
// TIM1�жϷ�����
void TIM1_CC_IRQHandler(void)
{
	
	TIM8->CNT=0;
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_CC2); 
}
//TIM8 CH2 PWM������� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM8_PWM_Init(u16 arr,u16 psc)
{		 					 
	
 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM8 | RCC_APB2Periph_AFIO, ENABLE); //ʹ��TIMx����
//  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM8, ENABLE);
  TIM_DeInit(TIM8);
  TIM_InternalClockConfig(TIM8);
 
  //���ø�����Ϊ�����������,���TIM8 CH2��PWM���岨��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM8_CH2N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��GPIO
 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM8_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���ù������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��GPIO
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2ģʽ	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 �͵�ƽ��Ч 
	 //
 TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;	//???????
 TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;	
 TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; 	//???????
 TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
 TIM_OC1Init(TIM8,&TIM_OCInitStructure);   	//����ָ���Ĳ�����ʼ������TIMx
 TIM_OC2Init(TIM8,&TIM_OCInitStructure);


//��������ʱ��
 TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
 TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
 TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
 TIM_BDTRInitStructure.TIM_DeadTime = 7; 	//????
 TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable; //??????
 TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;	//??????
 TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
 TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);  



	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1 Ԥװ��ʹ��
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_ARRPreloadConfig(TIM8, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE �����ʹ��,�߼���ʱ�����뿪����� 
	
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIMx
	   										  
} 
