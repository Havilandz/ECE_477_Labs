/*
Lab 5 automatic clock programmer
Authors:
Zach Haviland
Hunter Gross
Steph Poirier

Frequency is read on physical pin 11
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
#include <wiringPi.h>



int main()
{	
	wiringPiSetup();
	pinMode(0,INPUT);
	int *data_pointer = (int*)malloc(1000*sizeof(int));
	clock_t start, end;
	start = clock();
	data_pointer[999] = digitalRead(0);
	end = clock();
	printf("%.8f , %i\n", ((double)(end-start))/CLOCKS_PER_SEC, data_pointer[999]);
	return 0;
	

}


