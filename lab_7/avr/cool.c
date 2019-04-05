/*
 * Lab 7 Cool stuff 
 * Authors: Hunter Gross
 * 
 * WARNING!!! THIS PROBABLY WON'T WORK AS IS 
 * THIS IS AN ATTEMPTED CONCEPT
 *
 * This program takes input from the user from 0 to 3.3V 
 * and attempts to tune the adc reading to that voltage by 
 * switching off a specific amout of LEDs in order to draw
 * the correct amount of current to load the AVR.
 */

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "led.h"
#include "avr_adc.h"
#include "avr_coms.h"
#include <util/delay.h>

#define VIN 1.1

int main(int argc char* argv[])
{
	FILE *input, *output 	// File pointers for stdin and stdout
	int i;			// Counter for do/while
	float max;		// Max voltage (set by the user)
	float vref;		// measured power supply voltage
	int measurement;	// measured adc value
	
	/* serial communication setup */
	serial_init();
	
	/* external function initialization */
	initLEDs();
	initPS();

	_delay_ms(3000);
	input = stdin;
	output = stdout;

	while(1) {
		while(fscanf(input, "%f", &max) != 1) 	// read from serial
			fscanf(input, "%*s");
		
		/* Keeps user input within proper voltage bounds */
		if (max < 0) max = 0;
		if (max > 3.3) max = 3.3;

		i = 0xff;
		do {
			setLEDs(i);
			_delay_us(100);
			measurement = adcRead();
			vref = (1024*VIN)/measurement;	
			i << 1;
			_delay_us(100);
		} while(vref > max);
		
		fprintf(output,"The power supply has been limited to %f Volts", vref);
	}
}
	
