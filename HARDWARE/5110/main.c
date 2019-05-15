#include "stm32f10x.h"
#include "delay.h"		    
#include "usart.h"
#include "counter.h"
#include "SysTick.h"
#include "sys.h"
#include "stdio.h"
#include "nokia_5110.h"

/***********************************************************************************************
定时器外部时钟模式
************************************************************************************************/
u32 count_s;
u16 count_ms;
extern u16 count_i; 
extern u16 count_over; 
int main(void)
{										 
	float Fre_temp;	
	char s[16];
	int i=0;
	LCD_init(); //初始化液晶    
	LCD_clear(); 
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
 // uart_init(9600);	 //串口初始化为9600
	delay_init();	    	 //延时函数初始化	
  TIM1_PWM_Init(2,0);
	TIM3_External_Clock_CountingMode();
	TIM4_timer_Init();

    while(1)
    {
		if(count_i>100)
		{
			count_ms = TIM3->CNT;
			count_s = count_over*65536 + count_ms;
			//printf("%d \r\n ",count_s);	//打印数据
			
			
	    if( count_s<1000 )				  			//HZ  单位
      {
		    Fre_temp=(float)count_s;
				sprintf(s,"%.2f",Fre_temp);
				LCD_write_english_string(0,0,"frequence:");
        LCD_set_XY(0, 1);		
		    for(i=0;i<16;i++)
		    {
			    LCD_write_char(s[i]);
		    }
	    }
	   if( (count_s>=1000)&&(count_s<1000000) )	   //KHZ 单位
	   {
				Fre_temp=(float)count_s/1000;
				sprintf(s,"%.2f",Fre_temp);
				LCD_write_english_string(0,0,"frequence:");
        LCD_set_XY(0, 1);		
		    for(i=0;i<16;i++)
		    {
			    LCD_write_char(s[i]);
		    }	
				LCD_write_english_string(50,1,"kHZ");
	   }
	   if( count_s>=1000000 )						   //MHZ单位
	   {
				Fre_temp=(float)count_s/1000000;
				sprintf(s,"%.2f",Fre_temp);				
				LCD_write_english_string(0,0,"frequence:");
        LCD_set_XY(0, 1);		
		    for(i=0;i<16;i++)
		    {
			    LCD_write_char(s[i]);
		    }	
				LCD_write_english_string(50,1,"MHZ");
	    }
		  delay_ms(10);
		  count_i=0;
			count_over=0;
			TIM3->CNT=0;			
		}			
   }
}
