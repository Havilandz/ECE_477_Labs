/*
 * Lab 5 Interrupt Service Routine header file
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * In order to help measure the frequency of the clock signal
 * generated in avrcode.c, Interrupts are used to track the time
 * between the rising and falling edge of the generated signal.
 * 
 * This time difference is equivalent to the period and is used to
 * calculate frequency.
 * 
 * The frequency is also calculated and is available through the 
 * global variable 'frequency'.
 *
 */

#ifndef LAB5ISR_H
#define LAB5ISR_H


/* Function preforms the wiringPi initialization
and sets up two interrupts on the rising and falling
edge of gpio pin 1 */
void intInit(void);

/* Interrupt service routine for the rising edge
of gpio pin 1. Will save the cpu time once pin 1 
goes high into variable 'start'. */
void startTimerISR(void);

/* Interrupt service routine for the falling edge
of gpio pin 1. Will save the cpu time once pin 1
goes low into variable 'end' and calculate the
difference (diff) */
void endTimerISR(void);

/* Helper function to calulate frequency from
a given diff (period). */
int getFrequency(int d);

#endif
