#ifndef lcd_h
#define lcd_h

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LCD_DDR DDRA
#define LCD_PORT PORTA
#define RS 2
#define E 3

void lcdinit(void); //inicjalizacja wyswietlacza
void lcd_write_instr(uint8_t data); //funkcja wysyłająca pojedynczą instrukcję do wyświetlacza
void lcd_clear(void); //funkcja realizująca instrukcję "czyść wyświetlacz"
void lcd_write_data(uint8_t data); //funkcja wysyłająca pojedynczą daną do wyświetlacza
void lcd_set_xy(uint8_t x, uint8_t y); //funkcja ustawiająca kursor na pozycji xy
void lcd_write_text_xy(uint8_t x, uint8_t y, char *text); //funkcja wyświetlająca tekst znajdujący sie w w pamięci danych(!!!) począwszy od pozycji xy.
void lcd_kursor(uint8_t k);
int lcd_putc(char c, FILE *stream);
extern FILE lcd_stream;
#endif

