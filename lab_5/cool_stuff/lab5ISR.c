/*
 * Lab 5 Interrupt Service Routine implementation file
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * This file sets up the interrupts for measuring the period 
 * of the clock signal
 *
 * The global variable 'frequency' stores the calculated 
 * frequency of the current period
 *
 * The user should check if frequency is 0 before reading
 * the value to ensure a measurement has been made.
 *
 */

#include "lab5ISR.h"
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <wiringPi.h>
clock_t start, end, diff = 0;
//stores frequency
double frequency;
//keeps track of how many times these routines have gone off
uint32_t samples = 0;
//total frequency across all samples
double total = 0;

void intInit()
{
	wiringPiSetup();
	samples = 0;
	total = 0;
	wiringPiISR(0, INT_RISING_EDGE, startTimerISR());
	wiringPiISR(0, INT_FALLING_EDGE, endTimerISR());
	return;	
}

void startTimerISR()
{
	// Keep track of the start time
	start = clock();
	samples++;
	return;
}

void endTimerISR()
{
	// find the stop time and calculate the period
	end = clock();
	diff = end - start;
	frequency = 1/diff;
	total += frequency;	
	return;
}

double getFreq(void)
{
	return total/samples;
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
