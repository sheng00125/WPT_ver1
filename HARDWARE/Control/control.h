#include "sys.h"

void TIM3_IRQHandler(void);   //TIM3ÖÐ¶Ï
int Position_PID (int Encoder,int Target);
void limit_pwm(void);
void limit_shift_angle(void);


extern float Target_Uo;
extern float receivetemp0,receivetemp1,receivetemp2,receivetemp3;
extern u16 shift_angle;
extern int fv;