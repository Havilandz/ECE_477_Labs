/*
 * Lab 5 Interrupt Service Routine implementation file
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * This file sets up the interrupts for measuring the period 
 * of the clock signal
 *
 * The user should check if frequency is 0 after reading
 * the value to ensure a measurement has been made.
 *
 */

#include "lab5ISR.h"
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdio.h>
clock_t start, end, diff = 0;
//keeps track of how many times these routines have gone off
//Meaningfully means how many half periods the routine has measured. 
uint32_t samples = 0;
//total time spent high in clock cycles.
double total = 0;
/* End endTimerISR needs to be enabled after the
   startTimerISR to prevent strange timing issues from happening
   end_init tracks when endTimerISR has been enabled*/
uint32_t end_init = 0;


void intInit()
{
	wiringPiSetup();
	samples = 0;
	total = 0;
	wiringPiISR(0, INT_EDGE_RISING, startTimerISR);

	return;	
}

void startTimerISR()
{
	// Keep track of the start time
	start = clock();
	samples++;
	if(end_init == 0){
		wiringPiISR(0, INT_EDGE_FALLING, endTimerISR);	
		end_init = 1;
	}
	return;
}

void endTimerISR()
{
	// find the stop time and calculate the period
	end = clock();
	diff = end - start;
	total += diff;	
	printf("%i\n",samples);
	return;
}

double getFreq(void)
{
	return CLOCKS_PER_SEC * samples / (2 * total);
}

//gpioMute should stop the intterupts from registering
void gpioMute(void)
{
	system ("/usr/local/bin/gpio edge 17 none") ;
	return;
}
//double getFrequency(clock_t d)
//{
//	double freq;
//	while(1){ // Wait until next frequency measurement
//		if (d){ // Only calculate frequency if there is a period
//			freq = 1 / d;
//			diff = 0; // Clear diff to prep for next interrupt
//			return freq;
//		}
//	}
