/*
 * Week1B5.c
 *
 * Created: 02/02/2017 12:49:39
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000

typedef struct 
{
	unsigned char data;
	unsigned int delay;	
	
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] =
{
	{0x00, 100}, {0x01, 200}, {0x02, 300}, {0x04, 400}, {0x10, 100}, {0x20, 200}, {0x40, 300}, {0x80, 400},
	{0x00, 400},
	{0xAA, 350}, {0x55, 250},
	{0xAA, 150}, {0x55,  50},
	{0xAA, 150}, {0x55, 250},
	{0x00, 300},
	{0x81, 400}, {0x42, 500}, {0x24, 400}, {0x18, 300}, {0x0F, 200}, {0xF0, 100}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};

	

/* Prototype */
void wait(int);


int main(void)
{
    /* Replace with your application code */
	DDRA = 0b11111111;
	
    while (1) 
    {
		int index = 0;
		
		while(pattern[index].delay != 0x00)
		{
			PORTA = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
		//int index = 0;
		//
		//while(pattern[index].delay != 0)
		//{
			//PORTA = pattern[index].data;
			//wait(pattern[index].delay);
			//index++;
		//}
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



