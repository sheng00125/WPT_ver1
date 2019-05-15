#include "timer.h"
#include "led.h"
#include "usart.h"


//TIM1 CH1 PWM输出设置 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	
 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO, ENABLE); //使能TIMx外设

  TIM_DeInit(TIM1);
  TIM_InternalClockConfig(TIM1);
 
  //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM1_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化GPIO
 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM1_CH1N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载周期值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2模式	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 低电平有效 
	 //
 TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;	//???????
 TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;	
 TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; 	//???????
 TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
 TIM_OC1Init(TIM1,&TIM_OCInitStructure);   	//根据指定的参数初始化外设TIMx
 TIM_OC2Init(TIM1,&TIM_OCInitStructure);


//设置死区时间
 TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
 TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
 TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
 TIM_BDTRInitStructure.TIM_DeadTime = 7; 	// 7*Tdts  =1/72M = 7*13.89ns
 TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable; //??????
 TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;	//??????
 TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
 TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);  



	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1 预装载使能
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能,高级定时器必须开启这个 
	
	TIM1->CCR2=300;         // 改变移项角
	
	TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             
	NVIC_Init(&NVIC_InitStructure);                            
	
	
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIMx
	   										  
} 
// TIM1中断服务函数
void TIM1_CC_IRQHandler(void)
{
	
	TIM8->CNT=0;
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_CC2); 
}
//TIM8 CH2 PWM输出设置 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM8_PWM_Init(u16 arr,u16 psc)
{		 					 
	
 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM8 | RCC_APB2Periph_AFIO, ENABLE); //使能TIMx外设
//  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM8, ENABLE);
  TIM_DeInit(TIM8);
  TIM_InternalClockConfig(TIM8);
 
  //设置该引脚为复用输出功能,输出TIM8 CH2的PWM脉冲波形
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM8_CH2N
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化GPIO
 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM8_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用功能输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化GPIO
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载周期值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CH1 PWM2模式	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //OC1 低电平有效 
	 //
 TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;	//???????
 TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;	
 TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; 	//???????
 TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
 TIM_OC1Init(TIM8,&TIM_OCInitStructure);   	//根据指定的参数初始化外设TIMx
 TIM_OC2Init(TIM8,&TIM_OCInitStructure);


//设置死区时间
 TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
 TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
 TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; 
 TIM_BDTRInitStructure.TIM_DeadTime = 7; 	//????
 TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable; //??????
 TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;	//??????
 TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
 TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);  



	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1 预装载使能
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能,高级定时器必须开启这个 
	
	TIM_Cmd(TIM8, ENABLE);  //使能TIMx
	   										  
} 
