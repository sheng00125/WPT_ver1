#include "timer3.h"
#include "control.h"


int pwm=500;
float Position_KP=1,Position_KI=0,Position_KD=0;     // KP=1�� KI=0.001�� KD=0.01
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 

		temp0=(float)(a0*0.0033-4.8);
		temp1=(float)(a1*0.0161-0.2668);
		temp2=(float)a2*(3.3/4096);
		temp3=(float)a3*(3.3/4096);
//		pwm=pwm-Position_PID(temp1,Target_Uo);              //===λ��PID������
		limit_pwm();                                       //===PWM�޷�
//		
			
			
			
			
		}
}



/**************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
int Position_PID (int Encoder,int Target)
{ 	
	 
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 

	 return Pwm;                                           //�������
}


void limit_pwm(void)
{ 
		int Amplitude_High=450;    //===PWM������899 ������899
	  int Amplitude_Low=100;     //===PWM����200�����ֹͣת��
    if(pwm>=Amplitude_High) pwm=Amplitude_High;	
		if(pwm<=Amplitude_Low)  pwm=Amplitude_Low;	
	
}
