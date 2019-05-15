#include "sys.h"

#define 		CLK_5110_0 				(GPIOD -> BRR = 1 << 7)
#define 		CLK_5110_1 				(GPIOD -> BSRR = 1 << 7)
#define 		DIN_5110_0 				(GPIOG -> BRR = 1 << 10)
#define 		DIN_5110_1 				(GPIOG -> BSRR = 1 << 10)
#define 		DC_5110_0 			(GPIOD -> BRR = 1 << 6)
#define 		DC_5110_1 			(GPIOD -> BSRR = 1 << 6)
#define 		CE_5110_0 			(GPIOG -> BRR = 1 << 9)
#define 		CE_5110_1 			(GPIOG -> BSRR = 1 << 9)
#define 		RST_5110_0 		(GPIOG -> BRR = 1 << 11)
#define 		RST_5110_1 		(GPIOG -> BSRR = 1 << 11)

void LCD_init(void);
void LCD_clear(void);
void LCD_move_chinese_string(unsigned char X, unsigned char Y, unsigned char T); 
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s);
void LCD_write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);
void chinese_string(unsigned char X, unsigned char Y, unsigned char T);                 
void LCD_write_char(unsigned char c);
void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y);
void LCD_write_byte(unsigned char dat, unsigned char dc);
void LCD_set_XY(unsigned char X, unsigned char Y);
void delay_1us(void);                 

