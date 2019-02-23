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
#include <stdint.h>
#include <wiringPi.h>
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
	if((led < 0) || (led > 7)) {
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

int hexCtrl(int input)
{

	uint32_t mask = 0x01;
	uint32_t i;
	
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




