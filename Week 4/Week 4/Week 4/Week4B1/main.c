/*
 * Week4B.c
 *
 * Created: 09-Mar-17 10:54:22
 * Author : Nick
 */ 

#include <avr/io.h>
#include <util/delay.h>

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
	ADCSRA = 0b11100110;

}


int main(void)
{

	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	adcInit();
	
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
    }
}
