/*
 * Stacker Game
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * DESCRIPTION GOES HERE
 *
 */

#include "spi/spi.h"
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define BOUNCE_DELAY 500

int yLocation = 0;
uint8_t currentRow;
uint8_t prevRow = 0xff;

int main(int argc, char* argv[])
{
	/* Initialization */
	USART_SPI_init();

	/* Main Loop */

	while(1) {
		
	}

}


ISR(INT0_vect)
{
	_delay_ms(BOUNCE_DELAY);
	yLocation += 2;

	currentRow &= prevRow;	
	prevRow = currentRow;

}


		
		