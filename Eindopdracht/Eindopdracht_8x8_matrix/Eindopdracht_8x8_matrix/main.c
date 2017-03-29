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
/*
const unsigned short FONT8x8[97][8] = {
	{0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00}, // columns, rows, num_bytes_per_char
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // space 0x20
	{0x30,0x78,0x78,0x30,0x30,0x00,0x30,0x00}, // !
	{0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00}, // "
	{0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00}, // #
	{0x18,0x3E,0x60,0x3C,0x06,0x7C,0x18,0x00}, // $
	{0x00,0x63,0x66,0x0C,0x18,0x33,0x63,0x00}, // %
	{0x1C,0x36,0x1C,0x3B,0x6E,0x66,0x3B,0x00}, // &
	{0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00}, // '
	{0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00}, // (
	{0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00}, // )
	{0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, // *
	{0x00,0x30,0x30,0xFC,0x30,0x30,0x00,0x00}, // +
	{0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30}, // ,
	{0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}, // -
	{0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, // .
	{0x03,0x06,0x0C,0x18,0x30,0x60,0x40,0x00}, // / (forward slash)
	{0x3E,0x63,0x63,0x6B,0x63,0x63,0x3E,0x00}, // 0 0x30
	{0x18,0x38,0x58,0x18,0x18,0x18,0x7E,0x00}, // 1
	{0x3C,0x66,0x06,0x1C,0x30,0x66,0x7E,0x00}, // 2
	{0x3C,0x66,0x06,0x1C,0x06,0x66,0x3C,0x00}, // 3
	{0x0E,0x1E,0x36,0x66,0x7F,0x06,0x0F,0x00}, // 4
	{0x7E,0x60,0x7C,0x06,0x06,0x66,0x3C,0x00}, // 5
	{0x1C,0x30,0x60,0x7C,0x66,0x66,0x3C,0x00}, // 6
	{0x7E,0x66,0x06,0x0C,0x18,0x18,0x18,0x00}, // 7
	{0x3C,0x66,0x66,0x3C,0x66,0x66,0x3C,0x00}, // 8
	{0x3C,0x66,0x66,0x3E,0x06,0x0C,0x38,0x00}, // 9
	{0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, // :
	{0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30}, // ;
	{0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00}, // <
	{0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00}, // =
	{0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x00}, // >
	{0x3C,0x66,0x06,0x0C,0x18,0x00,0x18,0x00}, // ?
	{0x3E,0x63,0x6F,0x69,0x6F,0x60,0x3E,0x00}, // @ 0x40
	{0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x00}, // A
	{0x7E,0x33,0x33,0x3E,0x33,0x33,0x7E,0x00}, // B
	{0x1E,0x33,0x60,0x60,0x60,0x33,0x1E,0x00}, // C
	{0x7C,0x36,0x33,0x33,0x33,0x36,0x7C,0x00}, // D
	{0x7F,0x31,0x34,0x3C,0x34,0x31,0x7F,0x00}, // E
	{0x7F,0x31,0x34,0x3C,0x34,0x30,0x78,0x00}, // F
	{0x1E,0x33,0x60,0x60,0x67,0x33,0x1F,0x00}, // G
	{0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00}, // H
	{0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, // I
	{0x0F,0x06,0x06,0x06,0x66,0x66,0x3C,0x00}, // J
	{0x73,0x33,0x36,0x3C,0x36,0x33,0x73,0x00}, // K
	{0x78,0x30,0x30,0x30,0x31,0x33,0x7F,0x00}, // L
	{0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x00}, // M
	{0x63,0x73,0x7B,0x6F,0x67,0x63,0x63,0x00}, // N
	{0x3E,0x63,0x63,0x63,0x63,0x63,0x3E,0x00}, // O
	{0x7E,0x33,0x33,0x3E,0x30,0x30,0x78,0x00}, // P 0x50
	{0x3C,0x66,0x66,0x66,0x6E,0x3C,0x0E,0x00}, // Q
	{0x7E,0x33,0x33,0x3E,0x36,0x33,0x73,0x00}, // R
	{0x3C,0x66,0x30,0x18,0x0C,0x66,0x3C,0x00}, // S
	{0x7E,0x5A,0x18,0x18,0x18,0x18,0x3C,0x00}, // T
	{0x66,0x66,0x66,0x66,0x66,0x66,0x7E,0x00}, // U
	{0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00}, // V
	{0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00}, // W
	{0x63,0x63,0x36,0x1C,0x1C,0x36,0x63,0x00}, // X
	{0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00}, // Y
	{0x7F,0x63,0x46,0x0C,0x19,0x33,0x7F,0x00}, // Z
	{0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00}, // [
	{0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x00}, // \ (back slash)
	{0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00}, // ]
	{0x08,0x1C,0x36,0x63,0x00,0x00,0x00,0x00}, // ^
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF}, // _
	{0x18,0x18,0x0C,0x00,0x00,0x00,0x00,0x00}, // ` 0x60
	{0x00,0x00,0x3C,0x06,0x3E,0x66,0x3B,0x00}, // a
	{0x70,0x30,0x3E,0x33,0x33,0x33,0x6E,0x00}, // b
	{0x00,0x00,0x3C,0x66,0x60,0x66,0x3C,0x00}, // c
	{0x0E,0x06,0x3E,0x66,0x66,0x66,0x3B,0x00}, // d
	{0x00,0x00,0x3C,0x66,0x7E,0x60,0x3C,0x00}, // e
	{0x1C,0x36,0x30,0x78,0x30,0x30,0x78,0x00}, // f
	{0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x7C}, // g
	{0x70,0x30,0x36,0x3B,0x33,0x33,0x73,0x00}, // h
	{0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00}, // i
	{0x06,0x00,0x06,0x06,0x06,0x66,0x66,0x3C}, // j
	{0x70,0x30,0x33,0x36,0x3C,0x36,0x73,0x00}, // k
	{0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, // l
	{0x00,0x00,0x66,0x7F,0x7F,0x6B,0x63,0x00}, // m
	{0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x00}, // n
	{0x00,0x00,0x3C,0x66,0x66,0x66,0x3C,0x00}, // o
	{0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x78}, // p 0x70
	{0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x0F}, // q
	{0x00,0x00,0x6E,0x3B,0x33,0x30,0x78,0x00}, // r
	{0x00,0x00,0x3E,0x60,0x3C,0x06,0x7C,0x00}, // s
	{0x08,0x18,0x3E,0x18,0x18,0x1A,0x0C,0x00}, // t
	{0x00,0x00,0x66,0x66,0x66,0x66,0x3B,0x00}, // u
	{0x00,0x00,0x66,0x66,0x66,0x3C,0x18,0x00}, // v
	{0x00,0x00,0x63,0x6B,0x7F,0x7F,0x36,0x00}, // w
	{0x00,0x00,0x63,0x36,0x1C,0x36,0x63,0x00}, // x
	{0x00,0x00,0x66,0x66,0x66,0x3E,0x06,0x7C}, // y
	{0x00,0x00,0x7E,0x4C,0x18,0x32,0x7E,0x00}, // z
	{0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00}, // {
	{0x0C,0x0C,0x0C,0x00,0x0C,0x0C,0x0C,0x00}, // |
	{0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00}, // }
	{0x3B,0x6E,0x00,0x00,0x00,0x00,0x00,0x00}, // ~
	{0x1C,0x36,0x36,0x1C,0x00,0x00,0x00,0x00}};// DEL
*/

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
		//sendDataAtLine(i, shiftBitRight(reverseBit(data[i])));
		//sendDataAtLine(i, data[i]);
	}
}

int shiftBitRight(int bit)
{
	// This is all reversed because we use the function reverseBit()
	//bit = bit<<1;

	// Disable the first row of bits
	// Shift everything 1 bit to the right

	return bit;
}

//void display8x8MultiArray(int data1[], int data2[], int startData1) {
	//int i = startData1;
	//int line = 0;
	//for(i; i < 8; i++) {
		//sendDataAtLine(line, data1[i]);
		//line++;
	//}
	//int maxIndex = 8 - i;
	//i = 0;
	//for(i; i < maxIndex; i++) {
		//sendDataAtLine(line, data1[i]);
		//line++;
	//}
//}

void display8x8MultiArray(int data1[], int data2[], int startData2) {
	// split the numbers in data into array values
	int data18x8[8][8];
	int data28x8[8][8];
	int i = 0;
	int j = 0;
	for(j; j < 8; j++) {
		for(i; i < 8; i++) {
			data18x8[j][i] = (data1[j] >> i) & 1; //retrieve a single 0b number
			data28x8[j][i] = (data2[j] >> i) & 1; //and put it in corresponding array place
		}
	}

	j = 0;
	int sendData = 0x00; // the data which is going to be sent to the 8x8 dot matrix on one line
	for(j; j < 8; j++) {
		sendData = 0x00;// reset values
		i = 0;
		for(i; i < startData2; i++) { // put the first char in correct place
			sendData |= data18x8[j][startData2 + i] << (7 - i);
		}
		int k = 0;
		for(k; k < (7 - startData2); k++) { // put the second char into the correct place
			sendData |= data28x8[j][k] << (7 - i);
			i++;
		}
		sendDataAtLine(j, sendData); // send this data to 8x8 dot matrix
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

char reverseTheBits(char bit)
{
	char count = sizeof(bit) * 8 - 1;
	char reverse_bit = bit;
	bit >>= 1;
	while(bit)
	{
		reverse_bit <<= 1;
		reverse_bit |= bit & 1;
		bit >>= 1;
		count--;
	}
	reverse_bit <<= count;
	return reverse_bit;
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
/*
	char textToDisplay[12] = "Hallo";
	int position, c, character, l;
	int textLength = strlen(textToDisplay) - 1;
	short int displayBuffer[8][textLength*8];
	short int display[8];
	for(int i = 0; i < textLength; i++)
	{
		character = textToDisplay[i];
		for(position = 0; position < 8; position++)
		{
			displayBuffer[position][i] = alphabet[character][position];
		}
	}
*/

	char letter;
	int index;
	int i = 0;
	while (1)
	{
		//sendDataAtLine(2, 0x3E);
		//wait(500);
		//sendDataAtLine(2, 0xff);
		//sendDataAtLine(6, 0xFF);
		//displayletter('W');
		
		//display8x8(alphabet[i]);	// Starts to display the alphabet, starting from the first letter.
		//i++;						// Increases the counter, now it shows the second letter.
		//if(i == 26){				// If it reaches the end of the alphabet it returns to the first letter.
			//i = 0;
		//}
		//sendDataAtLine(2, 0x81);


/*
		short int bitShifted[8];
		for(letter = 0; letter < (textLength -1); letter++)
		{
			for(int y = 0; y < 8; y++)
			{
				for(index = 0; index < 8; index++)
				{
					bitShifted[index] = (displayBuffer[index][letter]) << y | (displayBuffer[index][letter+1]) >> (8-y);
					bitShifted[index] = reverseBit(bitShifted[index]);
				}

				for(int oo; oo < 8; oo++)
				{
					display8x8(bitShifted[oo]);
				}
				
			}
		}
*/		

//		display8x8MultiArray(alphabet[1], alphabet[2], 4);
		wait(500);


	}

	return 1;
}