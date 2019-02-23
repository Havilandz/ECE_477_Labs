/*
 * LED interface
 * Zach Haviland, Hunter Gross, Stephanie Poirier
 *
 * This program interfaces wih LEDs on GPIO pins 0-7
 *
 * Hardware notes:
 * 	8 LEDs were used in conjunction with
 * 	8 360 ohm resistors to ensure the current drive
 * 	does not exceed 51mA total. The target current
 * 	to drive the LEDS was 5mA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <errno.h>
#include "ledctrl.h"

/* Initializes the 8 GPIO pins for the LEDs */
void ledInit()
{
	int i;
	wiringPiSetup();
	
	for(i = 0; i < 8; i++) {
		pinMode(i, OUTPUT);
	}
}

/* Toggles the passed LED on or off depending on its previous state.
Returns -1 on error, 0 on set low, and 1 on set high. */
int ledToggle(int led)
{
	if((n < 0) || (led > 7) {
		printf("Error: indexing a non-existant LED\n");
		return -1;
	}
	
	if(digitalRead(led)) {
		digitalWrite(led, LOW);
		return 0;
	}

	else {
		digitalWrite(led,HIGH);
		return 1;
	}
}

int hexCtrl(int n, char *c[])
{

	uint32_t mask = 0x01;
	uint32_t i;
	uint32_t input = 0;
	/*used for exception handling. Is set by
	strtod if input is invalid*/
	errno = 0;

	/* There must be an argument for the program to work
	Checked here to prevent other problems like seg faults*/
	if (n != 2) {
		fprintf(stderr,"Usage: %s NUMBER\n",c[0]);
		return -1;
	}

	/*Converts input to decimal or hex if the number
	is prepended by 0x. Functionality implicitly supports
	octal*/
	input = (uint32_t)strtod(c[1],NULL);


	// Error checking
	
	//Checks errno to ensure strod converted correctly
	if (errno == ERANGE){
		fprintf(stderr,"Enter an integer number\n");	
		return -1;
	}
	// The working values for led masks are only 0-255
	if ((input < 0) || (input > 255)) {
	 	fprintf(stderr,"Enter an integer between 0x00 and 0xff\n");
		return -1;
	}


	// Check each bit of the input and set the corresponding led
	for (i = 0; i < 8; mask<<=1,i++) {
		if ((input & mask) == mask) {
			digitalWrite(i, HIGH);
		}
		else {
			digitalWrite(i, LOW);
		}
	}
	
	return 0;
}




