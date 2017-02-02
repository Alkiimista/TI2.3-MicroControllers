/*
 * Week1B7a.c
 *
 * Created: 02/02/2017 13:56:01
 * Author : Duc
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000

typedef enum {START, STATE_1, STATE_2, STATE_3, END} states;
typedef enum {D5, D6, D7} ports;
	
typedef struct
{
	void (*finit)(void);
	void (*fbody)(void);
	void (*fexit)(void);
	states nextState;
	};

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

