/*
 * B4.c
 *
 * Created: 02/02/2017 12:34:55
 *  Author: Duc
 */ 
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000

/* Prototype */
void wait(int);


int main(void)
{
	/* Replace with your application code */
	DDRA = 0b11111111;
	DDRC = 0b11111111;
	
	while (1)
	{
		for ( int i = 0x01; i<0x80; i<<=1 )
		{
			PORTA = i;
			PORTC = i;
			wait(1000);
		}
		for ( int i = 0x80; i>0x01; i>>=1 )
		{
			PORTA = i;
			PORTC = i;
			wait(1000);
		}
	}
	
	return 1;
}

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}