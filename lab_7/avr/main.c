/*
 * Lab 7 AVR Main Routine
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * This program reads from serial to obtain user input from stdin in
 * the form of an integer corresponding to a hexadecimal value to 
 * control a set of 8 LEDs. After sending the data to setLEDs, the program
 * takes a meaurement of the power supply voltage and sends it through serial
 * communication to be printed to the terminal.
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "led.h"
#include "avr_adc.h"
#include "avr_coms.h"

void main(int argc, char* argv[])
{
	FILE *input, *output; 	// File pointers for stdin and stdout
	int n = 0; 		// Integer for reading from stdin
	double measurement; 	// Power supply measurement to be taken

	/* Serial communication setup */
	serial_init();
	_delay_ms(3000);
		
	/* External function initialization */
	initLEDs();
	initPS();
	
	input = stdin;
	output = stdout;
	
	while(1) {
		fscanf(input, "%i", &n); // Read from serial

		/* Formats n into uint8_t to prevent unintended behavior */
		n &= 0xff00;
		n = (uint8_t)n;
		
		setLEDs(n);
		
		/* Takes the supply voltage measurement and sends it to the terminal */
		measurement = measurePS();
		fprintf(output, "The power rail is at %d Volts\r\n", measurement);
	}
}
