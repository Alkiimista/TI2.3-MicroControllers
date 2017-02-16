/*
 * Week2B3.c
 *
 * Created: 09/02/2017 12:38:29
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 80000000

const unsigned char numbers[16] =
{
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
};

volatile int index = 0;

ISR(INT0_vect)
{
	if(index > 15)
		index = 15;
	display(index++);
}

ISR(INT1_vect)
{
	if(index < 0)
		index = 0;
	display(index--);
}

int main(void)
{
	DDRC = 0b1111111;

	EICRA |= 0x0F;			// INT0 en INT1 zijn Rising Edge
	EIMSK |= 0x03;			// Enable INT1 & INT0

	sei();
	while (1)
	{
		wait(500);
		if(PIND & 0b0000001 && PIND & 0b00000010) // Als de knoppen PD0 en PD1 tegelijk ingedrukt worden, dan wordt 0 weergegeven.
		{
			index = 0;
			display(index);
		}
	}
}

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

void display(int digit)
{
	if(digit > 15)
	{
		PORTC = numbers[14];
	}
	else
		PORTC = numbers[digit];
}

