/*
 * Week4B.c
 *
 * Created: 09-Mar-17 10:54:22
 * Author : Nick
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void adcInit( void )
{
	//c, d?, e
	// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADMUX = 0b01100001;

	//a, b, f, g
	// ADC-enable, no interrupt, start, free running, division by 64
	ADCSRA = 0b10000110;


}

ISR( INT0_vect ) {

	//PORTB = 0x01;
	ADCSRA |= 0b01000000;
	while(ADCSRA & 0b01000000 ) ;

	PORTB = ADCL;
	
	PORTA = ADCH;
}

int main(void)
{


	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	DDRD = 0xF0;

	adcInit();

	
	EICRA |= 0x0B;
	// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD ^= 0x80;
		wait(500);
    }
}
