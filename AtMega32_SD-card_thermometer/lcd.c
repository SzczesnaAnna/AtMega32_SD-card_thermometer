#include "lcd.h"
#include <util/delay.h>

FILE lcd_stream=FDEV_SETUP_STREAM(lcd_putc, NULL, _FDEV_SETUP_WRITE);

void lcd_write_data(uint8_t data)
{
	LCD_PORT|=1<<RS; //bit RS na 1
	
	LCD_PORT|=1<<E;
	LCD_PORT=(data&0xf0)|(LCD_PORT&0x0f);
	_delay_ms(5);
	LCD_PORT&=~(1<<E);
	_delay_ms(5);
	
	LCD_PORT|=1<<E;
	LCD_PORT=(data<<4)|(LCD_PORT&0x0f);
	_delay_ms(5);
	LCD_PORT&=~(1<<E);
	_delay_ms(5);
}
void lcd_write_instr(uint8_t data)
{
	
	LCD_PORT&=~(1<<RS); //bit RS na 0
	
	LCD_PORT|=1<<E;
	LCD_PORT=(data&0xf0)|(LCD_PORT&0x0f);
	_delay_ms(5);
	LCD_PORT&=~(1<<E);
	_delay_ms(5);
	
	LCD_PORT|=1<<E;
	LCD_PORT=(data<<4)|(LCD_PORT&0x0f);
	_delay_ms(5);
	LCD_PORT&=~(1<<E);
	_delay_ms(5);
}
void lcdinit(void)
{
	LCD_DDR=0xff;
	_delay_ms(45);
	lcd_write_instr(0x33);
	lcd_write_instr(0x32);
	
	lcd_write_instr(0x28);
	lcd_write_instr(0x08);
	lcd_write_instr(0x01);
	lcd_write_instr(0x06);
	lcd_write_instr(0x0f);
}

void lcd_clear()
{
	lcd_write_instr(0x01);
}
void lcd_kursor(uint8_t x)
{	
	if(x==0)lcd_write_instr(0b00001100);
	if(x==1)lcd_write_instr(0b00001110);
	if(x==2)lcd_write_instr(0b00001111);
}
void lcd_set_xy(uint8_t x, uint8_t y)
{
	if(y>1)y=y%2;
	if(x>15)x=x%15;
	lcd_write_instr(0x80+y*0x40+x);
}
void lcd_write_text_xy(uint8_t x, uint8_t y, char *text)
{
	lcd_set_xy(x,y);
	while(*text)
	{
		lcd_write_data(*text);
		text++;
	}
}
int lcd_putc(char c, FILE *stream)
{
	lcd_write_data(c);
	return 0;
}
