/*
 * Week1.c
 *
 * Created: 02/02/2017 11:52:32
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000

/* Prototype */
void wait(int);


int main(void)
{
    /* Replace with your application code */
	DDRA = 0b01111111;
	PORTC = 0x01;
	
    while (1) 
    {
		if(PINC & 0x01 )	//Laat LED PA0 knipperen als knop PC0 ingedrukt is.
		{
			PORTA = 0x01;
			wait(100);
			PORTA = 0x00;
			wait(1000);
		}
		else
		{
			PORTA = 0x00;
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

