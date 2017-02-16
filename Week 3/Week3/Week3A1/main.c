///*
 //* Week3A1.c
 //*
 //* Created: 16/02/2017 10:15:21
 //* Author : Duc
 //*/ 
//
//#include <avr/io.h>
//#include <util/delay.h>
//
//#define F_CPU 80000000
//#define LCD_E 	3
//#define LCD_RS	2
//
///*Prototype*/
//void init_lcd(void);
//void lcd_command( unsigned char dat );
//void lcd_writeLine1( char text1[] );
//void lcd_writeChar( unsigned char dat );
//
//int main(void)
//{
	//DDRC = 0b11111111; //Output
    //init_lcd();
	//_delay_ms(1);
	//lcd_writeChar("a");
//
	//lcd_writeLine1("LKDSJFLSD");
    //while (1) 
    //{
		////lcd_writeLine1("pls");
		////PORTC ^= (1<<7);	// Toggle PORTD.7
		////_delay_ms( 250 );
    //}
//}
//
//// Initialisatie ldr
////
//void init_lcd(void)
//{
	//lcd_command( 0x02 ); //Set the mode to 4 bits, 5x8 dots.
	//
	//lcd_command( 0x28 ); //Set the display to show 2 lines.
	//
	//lcd_command( 0x0C ); //Display is turned on, cursor is off and blinking is off.
	//
	//lcd_command( 0x06 ); //Entry mode, cursor to the right and no shift.
//
	//lcd_command( 0x80 ); //Sets DDRAM adress, now you can send data.
//}
//
//void lcd_command ( unsigned char dat )
//{
	//PORTC = dat & 0xF0;		// hoge nibble
	//PORTC = PORTC | 0x08;	// data (RS=0),
							//// start (EN=1)
	//_delay_ms(1);			// wait 1 ms
	//PORTC = 0x04;			// stop (EN = 0)
	//PORTC = (dat & 0x0F) << 4; // lage nibble
	//PORTC = PORTC | 0x08;		// data (RS=0),
								//// start (EN=1)
	//_delay_ms(1);				// wait 1 ms
	//PORTC = 0x00;				// stop
								//// (EN=0 RS=0)
//}
//
//void lcd_writeChar( unsigned char dat )
//{
	//PORTC = dat & 0xF0; // hoge nibble
	//PORTC = PORTC | 0x0C; // data (RS=1),
	//// start (EN=1)
	//_delay_ms(1); // wait 1 ms
	//PORTC = 0x04; // stop (EN = 0)
	//PORTC = (dat & 0x0F) << 4; // lage nibble
	//PORTC = PORTC | 0x0C; // data (RS=1),
	//// start (EN=1)
	//_delay_ms(1); // wait 1 ms
	//PORTC = 0x00; // stop
	//// (EN=0 RS=0)
//}
//
//void lcd_writeLine1 ( char text1[] )
//{
	//// eerst de eerste 8 karakters = regel 1
	//// eerste pos regel 1
	//lcd_command(0x80);
	//for (int i=0; i<16; i++) {
		//lcd_writeChar( text1[i] );
	//}
//}
//
//void lcd_strobe_lcd_e()
//{
	//PORTC |= (1<<LCD_E);	// E high
	//_delay_ms(1);			// nodig
	//PORTC &= ~(1<<LCD_E);  	// E low
	//_delay_ms(1);			// nodig?
//}
//
//void lcd_writeData(unsigned char byte)
//{
	//// First nibble.
	//PORTC = byte;
	//PORTC |= (1<<LCD_RS);
	//lcd_strobe_lcd_e();
//
	//// Second nibble
	//PORTC = (byte<<4);
	//PORTC |= (1<<LCD_RS);
	//lcd_strobe_lcd_e();
//)

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	BigAVR LCD module
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c lcd.c
**					avr-gcc -g -mmcu=atmega128 -o lcd.elf lcd.o
**					avr-objcopy -O ihex lcd.elf lcd.hex
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_shiftRight();

/******************************************************************/
void lcd_strobe_lcd_e(void)
/*
short:			Strobe LCD module E pin --__
inputs:
outputs:
notes:			According datasheet HD44780
Version :    	DMK, Initial code
*******************************************************************/
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

/******************************************************************/
void init_4bits_mode(void)
/*
short:			Init LCD module in 4 bits mode.
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();

}

/******************************************************************/
void lcd_write_string(char *str)
/*
short:			Writes string to LCD at cursor position
inputs:
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// Het kan met een while:

	// while(*str) {
	// 	lcd_write_data(*str++);
	// }

	// of met een for:
	for(;*str; str++){
		lcd_write_data(*str);
	}
}


/******************************************************************/
void lcd_write_data(unsigned char byte)
/*
short:			Writes 8 bits DATA to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

/******************************************************************/
void lcd_write_command(unsigned char byte)
/*
short:			Writes 8 bits COMMAND to lcd
inputs:			byte - written to LCD
outputs:
notes:			According datasheet HD44780 table 12
Version :    	DMK, Initial code
*******************************************************************/
{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

/* This function shifts the current text 1 to the right.*/
void lcd_shiftRight()
{
	PORTC = 0x01;
	lcd_strobe_lcd_e();
	PORTC = 0x0C;
	lcd_strobe_lcd_e();
}



/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	init_4bits_mode();

	lcd_shiftRight();

	// Write sample string
	lcd_write_string("Hello");

	// Loop forever
	while (1)
	{
		//PORTD ^= (1<<7);	// Toggle PORTD.7
		//_delay_ms( 250 );
	}

	return 1;
}