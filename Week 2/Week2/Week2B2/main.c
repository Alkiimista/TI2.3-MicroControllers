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

volatile int i = 0x01; //Begin LED, PA0.
volatile int reverse = 0;

ISR(INT0_vect)
{
	if(i == 0x01)	//Als het LED bij PA0 is, gaat hij naar beneden toe.
	reverse = 0;
	else if(i == 0x80)	//Als het LED bij PA7 is, gaat hij omhoog.
	reverse = 1;
	
	if(reverse == 0)
	{
		i <<= 1;	//Shift bit 1 naar links, oftewel een LED naar beneden.
		PORTA = i;
	}
	else if(reverse == 1)
	{
		i >>= 1;	//Shift bit 1 naar rechts, oftewel een LED naar boven.
		PORTA = i;
	}
}

ISR(INT1_vect)
{
	if(i == 0x01)	//Als het LED bij PA0 is, gaat hij naar beneden toe.
	reverse = 0;
	else if(i == 0x80)	//Als het LED bij PA7 is, gaat hij omhoog.
	reverse = 1;
	
	if(reverse == 0)
	{
		i <<= 1;	//Shift bit 1 naar links, oftewel een LED naar beneden.
		PORTA = i;
	}
	else if(reverse == 1)
	{
		i >>= 1;	//Shift bit 1 naar rechts, oftewel een LED naar boven.
		PORTA = i;
	}	
}

int main(void)
{
	DDRD = 0xF0;
	DDRA = 0b11111111;

	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	PORTA = i;	//Initialiseren van de LED.

	sei();

    while (1)
    {
    }
}

