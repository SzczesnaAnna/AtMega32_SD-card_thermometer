#ifndef onewire_h
#define onewire_h

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define OW_PIN PB3
#define OW_DIR DDRB
#define OW_OUT PORTB
#define OW_IN PINB

#define OW_low OW_DIR |= 1 << OW_PIN
#define OW_high OW_DIR &= ~( 1 << OW_PIN )
#define OW_check ( OW_IN & ( 1 << OW_PIN ) )
int OWTouchReset(void);
void OWWriteBit(int bit);
int OWReadBit(void);
void OWWriteByte(int data);
int OWReadByte(void);
#endif
