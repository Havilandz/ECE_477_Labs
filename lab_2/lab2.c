/*
 * LED Interface
 * Zach Haviland, Hunter Gross, Stephanie Poirier
 *
 * This program interfaces wih LEDs on GPIO pins 0-7
 *
 * LEDs will be lit corresponding to the binary value of the
 * number entered on the command line at program start
 * with bit 0 corresponding to LED0 up though bit 7 corresponding
 * to LED7
 *
 *
 * Hardware notes:
 * 	8 red LEDs were used in conjunction with
 * 	8 360 ohm resistors to ensure the current drive
 * 	does not exceed 51mA total. The target current
 * 	to drive the LEDS was 5mA
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

int main(int argc, char *argv[])
{

	uint32_t mask = 0x00;
	uint32_t i;
	int input = 0;
	// Error checking
	if (argc != 2) {
		printf("Usage: %s #\n", argv[0]);
		return -1;
	}

	input = atoi(argv[1]);


	if (input <= 0) {	// atoi() returns 0 on non-number arguments
		printf("ERROR: Enter a positive, real integer\n");

		return -1;
	}

	if ((input < 0) || (input > 255)) {

		printf("Enter an integer between 0x00 and 0xff\n");


		return -1;
	}

	wiringPiSetup();

	// Makes GPIO pins outputs
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);


	for (i = 0; i < 7; mask<<=1,i++) {
		if ((input & mask) == mask) {
			digitalWrite(i, HIGH);
		}
		else {

			digitalWrite(i, LOW);
		}
	}
	return 0;
}




