/*
 * Week2B2.c
 *
 * Created: 09/02/2017 11:04:44
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 80000000

/*Prototype*/
void wait(int ms);

volatile int i = 0x01;
volatile int reverse = 0;

ISR(INT0_vect)
{
	if(reverse == 1 || i > 0x80)
	{
		i <<= 1;
		PORTA = i;
		reverse = 0;
	}
	else if(reverse == 0 || i < 0x01)
	{
		i >>= 1;
		PORTA = i;
		reverse = 1;
	}
}

ISR(INT1_vect)
{
	if(i < 0x80 || reverse == 0)
	{
		i <<= 1;
		PORTA = i;
		reverse = 1;
	}
	else if(i > 0x01 || reverse == 1)
	{
		i >>= 1;
		PORTA = i;
		reverse = 0;
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xF0;
	DDRA = 0b11111111;

	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0

	sei();

    while (1)
    {
    }
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

