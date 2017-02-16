/*
 * Week2B4.c
 *
 * Created: 09/02/2017 12:20:04
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 80000000

typedef struct 
{
	unsigned char data;
	unsigned int delay;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] =
{
	{0b00000001, 250}, {0b00000010, 250}, {0b00000100, 250}, {0b00001000, 250}, {0b00010000, 250}, {0b00100000, 250},
	{0b00000001, 250}, {0b00000010, 250}, {0b00000100, 250}, {0b00001000, 250}, {0b00010000, 250}, {0b00100000, 250},
	{0b00000001, 250}, {0b00000010, 250}, {0b00000100, 250}, {0b00001000, 250}, {0b00010000, 250}, {0b00100000, 1000},
	{0b00000011, 1500}, {0b00011000, 1500}, {0b00100001, 1500}, {0b00001100, 1500}, {0b00111111, 1500}, {0b00000000, 0}
};

int main(void)
{
	DDRC = 0b1111111;

	PORTC = 0b01111111;
    while (1) 
    {
		int index = 0;
		while(pattern[index].delay != 0)
		{
			PORTC = pattern[index].data;
			wait(pattern[index].delay);
			index++;
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

