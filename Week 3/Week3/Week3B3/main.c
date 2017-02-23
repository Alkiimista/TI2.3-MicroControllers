/*
 * Week3B3.c
 *
 * Created: 23-Feb-17 11:18:15
 * Author : Nick
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int TimerPreset = -1000;
int count = 0;

ISR( TIMER2_OVF_vect )
{
	TCNT2 = TimerPreset;	// Preset value
	count++;			// Increment counter
	PORTA = 0xFF;
}


void timer2Init( void )
{
	DDRD = 0x00;
	TCNT2 = TimerPreset;	// Preset value of counter 2
	TIMSK |= 0x02// BIT(6);		// T2 overflow interrupt enable
	//SREG |= 0x01 //BIT(7);		// turn_on intr all
	TCCR2 = 0x07;			// Initialize T2: ext.counting, rising edge, run
}


int main(void)
{
	DDRA = 0xFF;
	timer2Init();

    while (1) 
    {
		PORTA = 0x00;
		wait(1000);
    }
}

