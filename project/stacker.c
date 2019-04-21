/*
 * Stacker Game
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * DESCRIPTION GOES HERE
 *
 */

#include "spiBitBang.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define BOUNCE_DELAY 500

int position = 0;
uint8_t currentRow;
uint8_t prevRow = 0xff;

int main(int argc, char* argv[])
{
	/* Initialization */
	max7219_init();
	currentRow = 1;
	write_board(0,currentRow, 0x7E);
	
	/* Main Loop */

	while(1);

}


ISR(INT0_vect)
{
	_delay_ms(BOUNCE_DELAY);
	position += 2;

	currentRow &= prevRow;	
	prevRow = currentRow;

}


		
		
