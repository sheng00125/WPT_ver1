#include "sys.h"

void TIM3_IRQHandler(void);   //TIM3�ж�
int Position_PID (int Encoder,int Target);
void limit_pwm(void);
extern float Target_Uo;
