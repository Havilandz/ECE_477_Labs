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

#include "Lab5ISR.h"
#include <avr/io.h>
#include <wiringPi.h>
#include <time.h>

clock_t start, end, diff = 0;

extern double frequency;

void intInit()
{
	wiringPiSetup();
	wiringPiISR(1, INT_RISING_EDGE, startTimerISR());
	wiringPiISR(1, INT_FALLING_EDGE, endTimerISR());

}

void startTimerISR()
{
	// Keep track of the start time
	start = clock();
}

void endTimerISR()
{
	// find the stop time and calculate the period
	end = clock();
	diff = end - start;
	frequency = 1/diff
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
