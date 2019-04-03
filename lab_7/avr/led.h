/*
 * AVR LED Interface
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * The functions included configure a set of 8 LEDs wired to pins 0-7
 * on PORTC of the ATMEGA324PA AVR.
 */

#ifndef LED_H
#define LED_H

/* Initializes PORTC and tests
the LEDs by toggling them */
void initLEDs(void);

/* Sets the LEDs correspoding to 
an 8 bit integer passed as an argument */
void setLEDs(uint8_t led);

#endif
