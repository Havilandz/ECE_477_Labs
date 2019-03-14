/*
Lab 5 automatic clock programmer
Authors:
Zach Haviland
Hunter Gross
Steph Poirier

This program reads a waveform from the avr clock output on physical pin 11 of the RPI
and reprograms the EEPROM of the AVR to get the clock to be 100hz
memory of the avr and rsets it until the clock is 100hz
NOTE: This code is a very specific application and is generally not going
to work with other stuff.  
 */

#include "lab5ISR.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{	
	//stores average frequency from avr chip
	double freq = 0;
	intInit();	
	sleep(1);
	gpioMute();
	freq = getFreq();
		
}

