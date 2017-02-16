/*
 * Week3B2.c
 *
 * Created: 16/02/2017 12:19:20
 * Author : Duc
 */ 

#include <avr/io.h>
#include "lcd.h"

volatile int timesPressed = 0;

int main(void)
{
	char str[2];
	init_lcd_4bit();
	int test = 3;
    while (1) 
    {
		display_text("8");
    }
}

