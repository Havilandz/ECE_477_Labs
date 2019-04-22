/*
 * Stacker Game
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * The stacker game starts off with a row of LEDs at the bottom of the board.
 * The row moves back and forth horizontally until the player presses the button, stopping the
 * row in place. The object of the game is to make a tower of lights to the top of the board.
 * Not stopping in time to line up the lights will shrink the width of the rows until the player
 * reaches the top or misses the tower. 
 *
 */

#include "spiBitBang.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define BOUNCE_DELAY 1
#define UPDATE write_board(board,currentRow, position)

/* Variable Declaration */
int position = 0x7E; // The hex value of the current row
uint8_t currentRow = 1; // The position of the current row
uint8_t board = 0; // The board where the current row is
uint8_t prevPos = 0xff; // The previous row's position
int delay = 500; // Controls the speed of the row movement

/* Initializes the hardware interrupt for the button */
void interrupt_init(void);

int main(int argc, char* argv[])
{
	/* Initialization */
	int direction = 1; // Starts the row moving from left to right
	interrupt_init();
	max7219_init();
	write_board(board,currentRow, position);
	
	/* Main Loop */

	while(1){
		if((position & 1) || (position & 0x80)) // True if row touches edge of board
			direction *=-1; // Switch Direction
		
		/* Movement Control */
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
	SREG &= (1<<7); // Global Interrupt Enable
	EICRA |= (1<<ISC01); // Falling Edge Trigger
	EIMSK |= (1<<INT0); // Enable Interrupt
	PORTD |= (1<<PD2); // Enable Pull-up Resistor
	
}
/* Interrupt Service Routine for the button */
ISR(INT0_vect)
{
	//check timer to make sure that an interrupt hasn't happened in X ms
	//or disable interrupts for this then have a timer interrupt that 
	//reenables it	
	//clear timer to 0
	//enable timer interrupt
	//or just have the timer running all the time
	position &= prevPos; // Check the previous row for overlap
	prevPos = position; // Store data from the current row
	if(++currentRow > 8) { // Handles moving from board to board
		board++;
		currentRow = 0;
	}

	EIFR = 0; // Clear interrupt flag
}

//timer interrupt
//sets button interrupt to work
		
		
