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
#define UPDATE write_board(board,currentRow, position)
int position = 0x7E;
uint8_t currentRow;
uint8_t board = 0;
uint8_t prevRow = 0xff;
int delay = 500;
int main(int argc, char* argv[])
{
	int direction = 2; //tells direction of game movement
	/* Initialization */
	max7219_init();
	currentRow = 1;
	write_board(board,currentRow, position);
	
	/* Main Loop */

	while(1){
		if((position & 1) || (position & 0x80))
			direction *=-1;
		if(direction > 0){	
			position *= 2;
	
		}else{
			position /= 2;
		}
		UPDATE;	
		_delay_ms(500);
		
	}

}


ISR(INT0_vect)
{
	_delay_ms(BOUNCE_DELAY);
	position += 2;

	currentRow &= prevRow;	
	prevRow = currentRow;

}


		
		
