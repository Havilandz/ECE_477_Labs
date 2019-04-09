/*
 * Button Interrupt Service Routine
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * DESCRIPTION
 * 
 */

#include "ISR.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define BOUNCE_DELAY 500

(INT0_vect)
{
	_delay_ms(BOUNCE_DELAY);
	yLocation += 2;

	currentRow &= prevRow;	
	prevRow = currentRow;

}


