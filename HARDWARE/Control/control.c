#include "timer3.h"
#include "control.h"


int pwm=500;
float Position_KP=1,Position_KI=0,Position_KD=0;     // KP=1， KI=0.001， KD=0.01
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 

		temp0=(float)(a0*0.0033-4.8);
		temp1=(float)(a1*0.0161-0.2668);
		temp2=(float)a2*(3.3/4096);
		temp3=(float)a3*(3.3/4096);
//		pwm=pwm-Position_PID(temp1,Target_Uo);              //===位置PID控制器
		limit_pwm();                                       //===PWM限幅
//		
			
			
			
			
		}
}



/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID (int Encoder,int Target)
{ 	
	 
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 

	 return Pwm;                                           //增量输出
}


void limit_pwm(void)
{ 
		int Amplitude_High=450;    //===PWM满幅是899 限制在899
	  int Amplitude_Low=100;     //===PWM低于200，电机停止转速
    if(pwm>=Amplitude_High) pwm=Amplitude_High;	
		if(pwm<=Amplitude_Low)  pwm=Amplitude_Low;	
	
}
