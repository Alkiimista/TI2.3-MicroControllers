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

//volatile int timesPressed = 0;
static char str[1000];

void wait(int ms);

//ISR(INT0_vect)
//{
	//display_text("HAH");
	//timesPressed++;
	//display_text(sprintf(str, "%i", timesPressed));	
//}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	int timesPressed = 0;
	init_lcd_4bit();

	DDRA = 0xF0;

	EICRA |= 0x0B;

	EIMSK |= 0x03;

	sei();
	
	DDRD = 0xFC;
	//display_text("100");
    while (1) 
    {
		//display_text("10000");
		
		if(PIND & 1)
		{
			timesPressed--;
			//display_text(sprintf(str, "%i", timesPressed));
			char str[15];
			sprintf(str, "%d", timesPressed);
			display_text(str);
			wait(250);
		}
		else if(PIND & 2)
		{
			timesPressed++;
			char str[15];
			sprintf(str, "%d", timesPressed);
			display_text(str);
			wait(250);
		}
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 250 );
    }
}

