/*
Lab 5 automatic clock programmer
Authors:
Zach Haviland
Hunter Gross
Steph Poirier

This program reads a waveform from the avr clock output on physical pin 11 of the RPI
and reprograms the EEPROM of the AVR to get the clock to be closer to 100hz. It iterates
this process until the signal is within 99 - 101 hz
NOTE: This code is a very specific application and is generally not going
to work with other stuff.  
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main()
{	
	//Holds final frequency measurement
	double freq = 0;
	//Counter
	uint32_t i = 0;
	//Stores timestamps for calculating period
	clock_t start = 0;
	clock_t end = 0;
	//Sum of 10 signal periods measured in clock cycles
	clock_t sum_T = 0;
	/* Sets up interrupts */
	system("gpio mode 0 in");
	system("gpio edge 0 falling");

	/* Averages 10 periods of signal*/
	for(i = 0;i<10;i++){
		waitForInterrupt(0,-1);
		start = clock();
		waitForInterrrupt(0,-1);
		end = clock();
		sum_T += (start-end);
	}
	//calculates average freqency and converts to hz using
	//CLOCKS_PER_SEC macro
	freq = CLOCKS_PER_SEC * 10.0 / sum_T;
	
	printf("%.4f\n",freq);
	return 0;




}


