#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "onewire.h"
#include "diskio.h"
#include "ff.h"
#include "ffconf.h"
#include "string.h"


//lab10
float temp;
FATFS fs;
FIL plik;
char bufor[20];
UINT bw;
int main(void)
{ 	
	FRESULT res;
	res=f_mount(&fs, "", 1);
	if(res!=FR_OK)
	{
		lcd_write_text_xy(0,0,"Blad montowania karty SD:");
		while(1);
	}
	res=f_open(&plik, "daneAS.txt", FA_CREATE_ALWAYS|FA_WRITE);
	if(res!=FR_OK)
	{
		lcd_write_text_xy(0,0,"Blad otwarcia pliku:");
		while(1);
	}
	
	lcdinit();
	lcd_kursor(0);
	
	uint8_t x,y;
	uint16_t z;

	for(int i=0; i<6; i++)
	{ 
		lcd_write_text_xy(0,0,"Temperatura:");
		if(OWTouchReset()==0)
		{
			OWWriteByte(0xCC); //Skip ROM
			OWWriteByte(0x44); //Rozpocznij pomiar temperatury
		}
		_delay_ms(750);
		if(OWTouchReset()==0)
		{
			OWWriteByte(0xCC); 
			OWWriteByte(0xBE); 
			x=OWReadByte();
			y=OWReadByte();
			z=((y&0b00000111)<<8)+x;
			temp=z*0.0625;
			lcd_set_xy(0,1);
			fprintf(&lcd_stream, "%.4f st. C", temp);
			
			sprintf(bufor, "%.4f\n", temp);
			res=f_write(&plik, bufor, strlen(bufor), &bw);
			
			if(res!=FR_OK)
			{
				lcd_write_text_xy(0,0,"Blad zapisu:");
				while(1);
			}
		}
		
	}
	
	f_close(&plik);
	f_mount(0, "", 0);
	lcd_write_text_xy(0,0,"Koniec pomiarow:");
	while(1);{}
	return 1;
}

