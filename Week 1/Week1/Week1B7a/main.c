/*
 * Week1B7a.c
 *
 * Created: 02/02/2017 13:56:01
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000

enum states {START, STATE_1, STATE_2, STATE_3, END};
enum ports {D5, D6, D7};

/* Prototype */
void delay(int);

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

void delay(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

