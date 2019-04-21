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
#define BOUNCE_DELAY 1
#define UPDATE write_board(board,currentRow, position)
int position = 0x7E;
uint8_t currentRow;
uint8_t board = 0;
uint8_t prevPos = 0xff;
int delay = 500;
int main(int argc, char* argv[])
{
	int direction = 1; //tells direction of game movement
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

void interrupt_init(void)
{
	SREG |= (1<<I); // Global Interrupt Enable
	EICRA |= (1<<ISC01); // Falling Edge Trigger
	EIMSK |= (1<<IINT0); // Enable Interrupt
	PORTD |= (1<<PD2); // Enable Pull-up Resistor
	

ISR(INT0_vect)
{
	_delay_ms(BOUNCE_DELAY);
	position &= prevPos;
	prevPos = position;
	if(++currentRow > 8) {
		board++;
		currentRow = 0;
	}

	EIFR = 0; // Clear interrupt flag
}


		
		
