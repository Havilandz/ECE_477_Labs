/*
 * AVR LED Interface
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * The functions included configure a set of 8 LEDs wired to pins 0-7
 * on PORTA of the ATMEGA324PA AVR.
 * Not that this is also used to run the LOAD pin on the led dotmatrix display 
 * for the final project, which is connected to A0
 */

#ifndef LED_H
#define LED_H

/* Initializes PORTC and tests
the LEDs by toggling them */
void initLEDs(void);

/* Sets the LEDs correspoding to 
an 8 bit integer passed as an argument */
void setLEDs(int led);

#endif
