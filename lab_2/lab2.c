/*
 * LED Interface
 * Zach Haviland, Hunter Gross, Stephanie Poirier
 *
 * This program interfaces wih LEDs on GPIO pins 0-7
 *
 * LEDs will be lit corresponding to the binary value of the
 * number entered on the command line at program start
 * with bit 0 corresponding to LED0 up though bit 7 corresponding
 * to LED7.
 *
 * The user can optionally provide a brightness level to specify
 * the brightness of the LEDs.
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
#include <softPwm.h>

int main(int argc, char *argv[])
{

	uint32_t mask = 0x01;
	uint32_t i;
	uint32_t input = 0;
	uint32_t brightness;
	/*used for exception handling. Is set by
	strtod if input is invalid*/
	errno = 0;

	/* There must be an argument for the program to work
	Checked here to prevent other problems like seg faults*/
	if ((argc > 3) || (argc < 2)) {
		fprintf(stderr,"Usage: %s NUMBER [BRIGHTNESS]\n",argv[0]);
		return -1;
	}

	// If there is a brightness argument, it must be between 0 and 100
	if ((argc == 3) && (atoi(argv[2]) == 0)) {
		fprintf(stderr,"Brightness must be a decimal integer between 0 and 100\n");
		return -1;
	}

	/*Converts input to decimal or hex if the number
	is prepended by 0x. Functionality implicitly supports
	octal*/
	input = (uint32_t)strtod(argv[1],NULL);

	// Checks errno to ensure strod converted correctly
	if (errno == ERANGE){
		fprintf(stderr,"Enter an integer number\n");
		return -1;
	}
	// The working values for led masks are only 0-255
	if ((input < 0) || (input > 255)) {
	 	fprintf(stderr,"Enter an integer between 0x00 and 0xff\n");
		return -1;
	}

	wiringPiSetup();

	// GPIO Pin init for each led
	for (i = 0; i < 8; i++) {
		pinMode(i, OUTPUT);
	}

	/* Creates software controlled PWM pins for
	GPIO pins 0-7 */
	for (i=0; i < 8; i++) {
		softPwmCreate(i, 0, 100);
	}

	// Sets the brightness value, default is 100
	if (argv[2] != NULL) {
		brightness = atoi(argv[2]);
	}
	else {
		brightness = 100;
	}

	// Check each bit of the input and set the corresponding led
	for (i = 0; i < 8; mask<<=1,i++) {
		if ((input & mask) == mask) {
			softPwmWrite(i, brightness);
		}
		else {
			softPwmWrite(i, 0);
		}
	}

	return 0;
}




