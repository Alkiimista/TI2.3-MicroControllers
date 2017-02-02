/*
 * Week1B6.c
 *
 * Created: 02/02/2017 13:25:17
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000

void delay(int);

int main(void)
{
    /* Replace with your application code */
	int delayInt = 1000;
	DDRC = 0b01111111;
	DDRD = 0b11111111;
	
    while (1) 
    {	
		if(PIND & 0x01)
		{
			if(delayInt == 250){ delayInt = 1000;}
				else{delayInt = 250;}
			delay(300);
		}
		
		PORTC = 0x01;
		delay(delayInt);
		PORTC = 0x00;
		delay(delayInt);
    }
}

void delay(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

