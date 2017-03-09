/*
 * Week4B.c
 *
 * Created: 09-Mar-17 10:54:22
 * Author : Nick
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <string.h>

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void adcInit( void )
{
	// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADMUX = 0b11100001;

	// ADC-enable, no interrupt, start, free running, division by 64
	ADCSRA = 0b11100110;

}



int main(void)
{
	DDRF = 0x00;
	DDRA = 0xFF;

	adcInit();
	init_lcd_4bit();
	wait(300);
	char tempToDisplay[15];
	clearScreen();
    /* Replace with your application code */
    while (1) 
    {
		clearScreen();
		int i = ADCH;
		sprintf(tempToDisplay, "C %i", i);
		wait(5);
		
		display_text(tempToDisplay);
		wait(5);
		memset(tempToDisplay, 0, 15);
		PORTA = ADCH;
		wait(2000);
		
    }
}
