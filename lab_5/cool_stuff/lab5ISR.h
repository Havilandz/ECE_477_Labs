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
 * The global variable total is used to calculate the average freuqency
 * this is done because wiringPi is dumb and you can't turn off it's interrupts.
 *
 */

#ifndef LAB5ISR_H
#define LAB5ISR_H


/* Function preforms the wiringPi initialization
and sets up two interrupts on the rising and falling
edge of wiringPi gpio 0 */
void intInit(void);

/* Interrupt service routine for the rising edge
of wiringPi gpio 0. Will save the cpu time wiringPi gpio0 
goes high into variable 'start'. */
void startTimerISR(void);

/* Interrupt service routine for the falling edge
of wiringPi gpio0  . Will save the cpu time once wiringPi gpio0
goes low into variable 'end' and calculate the
difference (diff). this is on physical pin 11 */
void endTimerISR(void);

//Acessor function to get the average frequency of the input
double getFreq(void);

//Mutes gpio pin that reads from AVR. Basically stops interrupts
void gpioMute(void);

/* Helper function to calulate frequency from
a given diff (period). Depreciated in new code */
//int getFrequency(int d);

#endif
