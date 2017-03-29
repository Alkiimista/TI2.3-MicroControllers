/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ledmatrix.c
**
** Beschrijving:	Simple HT16K33 Ledmatix demo.
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ledmatrix.c
**					avr-gcc -g -mmcu=atmega128 -o ledmatrix.elf ledmatrix.o
**					avr-objcopy -O ihex ledmatrix.elf ledmatrix.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
* -------------------------------------------------------------------------*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


int alphabet[26][8] = {
	{0b00011000, 0b00100100, 0b00100100, 0b00100100, 0b00111100, 0b00100100, 0b00100100, 0b00100100}, // A
	//{0b00011110,0b00100010,0b00100010,0b00011110,0b00011110,0b00100010,0b00100010,0b00011110},
	{0b00111100, 0b00100010, 0b00100010, 0b00111100, 0b00111100, 0b00100010, 0b00100010, 0b00111100}, // B
	{0b00111100, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00111100}, // C
	{0b00111100, 0b00100010, 0b00100010, 0b00100010, 0b00100010, 0b00100010, 0b00100010, 0b00111100}, // D
	{0b00111100, 0b00100000, 0b00100000, 0b00111100, 0b00111100, 0b00100000, 0b00100000, 0b00111100}, // E
	{0b00111100, 0b00100000, 0b00100000, 0b00111100, 0b00100000, 0b00100000, 0b00100000, 0b00100000}, // F
	{0b00111100, 0b00100000, 0b00100000, 0b00100000, 0b00101100, 0b00100100, 0b00100100, 0b00111100}, // G
	{0b00100100, 0b00100100, 0b00100100, 0b00111100, 0b00111100, 0b00100100, 0b00100100, 0b00100100}, // H
	{0b00111100, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00111100}, // I
	{0b00111100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00100100, 0b00011000}, // J
	{0b00100010, 0b00100100, 0b00101000, 0b00110000, 0b00110000, 0b00101000, 0b00100100, 0b00100010}, // K
	{0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00100000, 0b00111100}, // L
	{0b00100100, 0b01011010, 0b01011010, 0b01011010, 0b01000010, 0b01000010, 0b01000010, 0b01000010}, // M
	{0b00000000, 0b00100100, 0b00100100, 0b00110100, 0b00101100, 0b00100100, 0b00100100, 0b00100100}, // N
	{0b00011000, 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00100100, 0b00011000}, // O
	{0b00111000, 0b00100100, 0b00100100, 0b00111000, 0b00100000, 0b00100000, 0b00100000, 0b00100000}, // P
	{0b00111000, 0b01000100, 0b01000100, 0b01000100, 0b01000100, 0b01001100, 0b00111100, 0b00000010}, // Q
	{0b01111000, 0b01000100, 0b01000100, 0b01111000, 0b01100000, 0b01010000, 0b01001000, 0b01000100}, // R
	{0b00000000, 0b00111100, 0b00100000, 0b00100000, 0b00111100, 0b00000100, 0b00000100, 0b00111100}, // S
	{0b11111110, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000}, // T
	{0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01111110}, // U
	{0b01000100, 0b01000100, 0b01000100, 0b01000100, 0b01101100, 0b00101000, 0b00101000, 0b00010000}, // V
	{0b01000100, 0b01000100, 0b01000100, 0b01010100, 0b01111100, 0b01101100, 0b01000100, 0b00000000},
	//{0b10000001, 0b10000001, 0b10000001, 0b11000011, 0b01011010, 0b01011010, 0b00100100, 0b00100100}, // W
	{0b10001000, 0b10001000, 0b01010000, 0b00100000, 0b00100000, 0b01010000, 0b10001000, 0b10001000}, // X
	{0b10000010, 0b01000100, 0b00101000, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00010000}, // Y
	{0b01111110, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b01111110	} // Z
};

/************************/
void twi_init(void)
/* 
short:			Init AVR TWI interface and set bitrate
inputs:			
outputs:	
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
***********************/
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

/************************/
void twi_start(void)
/* 
short:			Generate TWI start condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
***********************/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/************************/
void twi_stop(void)
/* 
short:			Generate TWI stop condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
***********************/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/************************/
void twi_tx(unsigned char data)
/* 
short:			transmit 8 bits data
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
***********************/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

/************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
***********************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void clear (void)
{
	int row = 7;

	for(int i = 0; i <= row; i++)
	{
		sendDataAtLine(0x00);
	}
}


void sendDataAtLine(int line, int data){
	twi_start();
	twi_tx(0xE0);
	twi_tx(line * 2);
	twi_tx(data);
	twi_stop();
}

void display8x8(int data[]) {
	int i = 0;
	for(i; i < 8; i++) {
		sendDataAtLine(i, reverseBit(data[i]));
		//sendDataAtLine(i, data[i]);
	}
}

void display8x8MultiArray(int data1[], int data2[], int startData1) {
	int i = startData1;
	int line = 0;
	for(i; i < 8; i++) {
		sendDataAtLine(line, data1[i]);
		line++;
	}
	int maxIndex = 8 - i;
	i = 0;
	for(i; i < maxIndex; i++) {
		sendDataAtLine(line, data1[i]);
		line++;
	}
}

int correctData(int data) {
	//int newNumber = data % 10000000;
	//newNumber |= data;

	int newNumber = 0;


	int i = 0;
	for(i; i < 8; i++) {
		newNumber |=  data % 10;
		newNumber = newNumber << 1;
		data = data >> 1;
	}
}

int reverseBit(int b)
{
	b = ((b * 0x0202020202ULL & 0x010884422010ULL) % 1023);
	//int newB =  ((b & 0x7F) >> 1) | ((b & 0x01) << 7);
	//int newB = b >> 1;
	return b;
}

void displayletter(char letter) {
	switch(letter) {
		case 'A' : display8x8(alphabet[0]); break;
		case 'B' : display8x8(alphabet[1]); break;
		case 'C' : display8x8(alphabet[2]); break;
		case 'D' : display8x8(alphabet[3]); break;
		case 'E' : display8x8(alphabet[4]); break;
		case 'F' : display8x8(alphabet[5]); break;
		case 'G' : display8x8(alphabet[6]); break;
		case 'H' : display8x8(alphabet[7]); break;
		case 'I' : display8x8(alphabet[8]); break;
		case 'J' : display8x8(alphabet[9]); break;
		case 'K' : display8x8(alphabet[10]); break;
		case 'L' : display8x8(alphabet[11]); break;
		case 'M' : display8x8(alphabet[12]); break;
		case 'N' : display8x8(alphabet[13]); break;
		case 'O' : display8x8(alphabet[14]); break;
		case 'P' : display8x8(alphabet[15]); break;
		case 'Q' : display8x8(alphabet[16]); break;
		case 'R' : display8x8(alphabet[17]); break;
		case 'S' : display8x8(alphabet[18]); break;
		case 'T' : display8x8(alphabet[19]); break;
		case 'U' : display8x8(alphabet[20]); break;
		case 'V' : display8x8(alphabet[21]); break;
		case 'W' : display8x8(alphabet[22]); break;
		case 'X' : display8x8(alphabet[23]); break;
		case 'Y' : display8x8(alphabet[24]); break;
		case 'Z' : display8x8(alphabet[25]); break;
	}
}


void initcommands(void)
{
	
	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}


/************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, trashing the HT16K33
Version :    	DMK, Initial code
***********************/
{
	
	twi_init();		// Init TWI interface
	initcommands();	// Standard commands before running 

	
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x00);	// Address
	twi_tx(0x00);	// data
	twi_stop();
	wait(500);
	//twi_start();
	//twi_tx(0xE0);	// Display I2C addres + R/W bit
	//twi_tx(rij);	// Address
	//twi_tx(lampje);	// De lampjes in een gegeven rij die branden waarbij FF heel de rij laat branden en 00 niks

	clear();
	int i = 0;
	while (1)
	{


		//swastika();


		//sendDataAtLine(2, 0x3E);
		//wait(500);
		//sendDataAtLine(2, 0xff);
		//sendDataAtLine(6, 0xFF);
		//displayletter('W');
		display8x8(alphabet[i]);
		i++;
		if(i == 26){
			i = 0;
		}
		//sendDataAtLine(2, 0x81);
		wait(500);
	}

	return 1;
}