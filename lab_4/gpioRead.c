/*
 * gpioRead.c
 * 
 * Authors: Zach Haviland, Hunter Gross Steph Poirier
 * 
 * Function implementations for gpioRead
 * 
 * 
 */
#include <wiringPi.h>
#include "gpioRead.h"

void gpioInit(int pin)
{
	wiringPiSetup();
	pinMode(pin,INPUT);
	pullUpDnControl(pin,PUD_UP);
}

int gpioRead(int pin)
{
	return !digitalRead(pin);
} 
