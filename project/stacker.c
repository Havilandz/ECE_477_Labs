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
 * Hardware Notes:
 *
 * AVR: ATMEGA324PA
 * Display: 4 MAX7219 8x8 Dot Matrix LED Display's Daisy-chained together
 * Programmer: Raspberry Pi 3
 *
 * Both the MAX7219 and the ATMEGA324PA run on 5V DC.
 * The project runs on one 9V battery.
 * An LM7805 linear voltage regulator was used to step down the voltage to 5V.
 *
 * Connections detailed in pinout.txt
 */

#include "spiBitBang.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define UPDATE write_board(board, board_data)

/* Variable Declaration */
int position = 0x7E; // The hex value of the current row
uint8_t currentRow = 0; // The position of the current row
uint8_t board = 0; // The board where the current row is
uint8_t prevPos = 0xff; // The previous row's position
int flag = 0; // Timer flag

uint8_t board_data[8] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};// The previous row's position
int time = 30;
/* Translates row data to cloumn data */
void translate(uint8_t row_data, uint8_t row_num);
/* Initializes the hardware interrupt for the button */
void interrupt_init(void);
//Delay function
void delay(unsigned char n);
//clears out the board data
void clear_data();
int main(int argc, char* argv[])
{
	/* Initialization */
	int direction = 1; // Starts the row moving from left to right
	interrupt_init();
	max7219_init();
	write_board(board, board_data);
	
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
		translate(position, currentRow);
		UPDATE;	
		delay(time);
		
	}

}
//pushes row data on to data array of column data
void translate(uint8_t row_data, uint8_t row_num)
{
	int i = 0;
	for(i = 7; i >= 0; i--) {
		if(row_data & (1<<i)) {
			board_data[i] |= (1<<row_num);
		}
		else {
			board_data[i] &= ~(1<<row_num);
		}
	}
}

void delay(unsigned char n)
{
	while(n--)
	_delay_ms(25);
}

void interrupt_init(void)
{
	SREG |= (1<<7); // Global Interrupt Enable
	EICRA |= (1<<ISC01); // Falling Edge Trigger
	EIMSK |= (1<<INT0); // Enable Interrupt
	PORTD |= (1<<PD2); // Enable Pull-up Resistor
	TCCR0B = (1<<CS02) | (1<<CS00);	// Sets Period to 128us
	OCR0A = 200;//~25ms
	TIMSK0 |= (1<<OCIE0A); // Enable Timer Interrupt
	
}
/* Interrupt Service Routine for the button */
ISR(INT0_vect)
{
//	if(flag) 
//		return;
	EIMSK &= ~(1<<INT0); //temporarily disable interrupt
	TCNT0 = 0;
	flag = 1; //sets flag to temporarily disable interrupts
	time--; //
	position &= prevPos; // Check the previous row for overlap
	prevPos = position; // Store data from the current row
	if(++currentRow > 7) { // Handles moving from board to board
		board++;
		currentRow = 0;
		clear_data();
	}
	EIFR = 0; // Clear interrupt flag
}

//timer interrupt
//sets button interrupt to work
		
ISR(TIMER0_COMPA_vect)
{
	EIMSK |= (1<<INT0); // Enable Interrupt
	flag = 0;
}

void clear_data(void)
{
	int ct = 0;
	for(ct = 0; ct<8; ct++){
		board_data[ct] = 0;
	}
}
