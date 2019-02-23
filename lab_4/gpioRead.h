/*
 * gpioRead.h
 * 
 * Authors: Zach Haviland, Hunter Gross Steph Poirier
 * 2/23/2019
 * 
 * This header file contains the function definitions for
 * gpioRead.c
 * 
 * gpioRead is an abstraction of the process used to initialize 
 * raspberry pi gpio pins for digital input with the wiringPi
 * library. It was developed with the intent of using the functions
 * for interfacing with simple push buttons.
 * The inteface assumes that the input pins are pulled up internally
 * with the push button connecting to ground when it is pushed.
 */
#ifndef BUTTON_CTRL_H
#define BUTTON_CTRL_H

/*Takes a pin number and configures that pin as a digital
input with the internal pull up enabled*/
void gpioInit(int pin);
/*Takes a pin number that was configured as a digital
input with gpioIinit()
Returns 1 if the line is pulled low and 0 if the line is high */
int gpioRead(int pin);

#endif
