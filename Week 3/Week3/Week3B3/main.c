/*
 * Week3B3.c
 *
 * Created: 23-Feb-17 11:18:15
 * Author : Nick
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int i = 0;

ISR( TIMER2_COMP_vect )
{
	//TCNT2 = TimerPreset;	// Preset value
	//count++;			// Increment counter
	//PORTA = 0xFF;

	if(i == 0)
	{
		PORTB = 0b00000000;
		i = 1;
		OCR2 =193;
	}
	else
	{
		PORTB = 0b11111111;
		i = 0;
		OCR2 = 117;
	}
}


void timer2Init( void )
{
	//DDRD = 0x00;
	//TCNT2 = TimerPreset;	// Preset value of counter 2

	OCR2 = 117;
	TIMSK = 0b10000000;			// T2 overflow interrupt enable
	TCCR2 = 0b00011101;			// Prescaler = 1024
}


int main(void)
{
	DDRB = 0b11111111;
	timer2Init();
	
	sei();
    while (1) 
    {
    }
}

