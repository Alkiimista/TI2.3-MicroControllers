/*
 * Week3B2.c
 *
 * Created: 16/02/2017 12:19:20
 * Author : Duc
 */ 

#include <avr/io.h>
#include "lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

//volatile int timesPressed = 0;
static char str[10];

void wait(int ms);

//ISR(INT0_vect)
//{
	//display_text("HAH");
	//timesPressed++;
	//display_text(sprintf(str, "%i", timesPressed));	
//}
volatile int timesPressed = 0;
// char str[10];

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


ISR(INT0_vect)
{
	clearScreen();
	wait(1);
	timesPressed++;
	sprintf(str, "%d", timesPressed);
	display_text(str);
	memset(str, 0, 10);
}


int main(void)
{
	//int timesPressed = 0;
	init_lcd_4bit();

	
	DDRD = 0xF0;
	DDRA = 0b11111111;

	EICRA |= 0x0B;

	EIMSK |= 0x03;

	sei();
	
	display_text("0");
    while (1) 
    {
		
    }
}

