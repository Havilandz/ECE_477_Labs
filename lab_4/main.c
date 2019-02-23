/*
 * ECE477 Lab 4: Push Button Interface 
 * 
 * Authors: Zach Haviland, Hunter Gross, Stephanie Poirier
 * 
 * Spring 2019
 *
 * This program utilizes two push buttons (A and B) which control the speed and direction
 * of a shifting LED. The program runs continuously until both buttons are pressed at the same time.
 * Only one LED is lit at a time, the light moves from the least significant position to 
 * the most significant position and wraps around when it reaches the end. 
 *
 * Push button A halves the delay between switching LEDs. The lower bound of the delay
 * is 32 milliseconds. Push button B doubles the delay. The upper bound of the delay is
 * 1024 milliseconds.
 * Pressing a button after it has reached its respective bound does not change speed, but reverses
 * the direction of the traveling light. 
 *
 * The code executes on button press, not release. Holding the button doesn't change code behavior
 * This code uses GPIO pins 0 - 7 for the LEDs and GPIO28 and GPIO29 for the push buttons A and B
 * respectively
 */
#include <stdint.h>
#include "gpioRead.h"
#include <wiringPi.h>
#include "ledctrl.h"

#define BOUNCE_DELAY 10

int main(int argc, char **argv)
{
	uint32_t timing = 1024; //Delay timing
	uint32_t i=0; // Loop counter
	//flags for recording button presses
	uint32_t pollA = 0;	
	uint32_t pollB = 0;
	int32_t direction = 1;
	ledInit();
	gpioInit(28);
	gpioInit(29);

	while(1){
		
	//polling and debouncing
	if(pollA){
		delay(BOUNCE_DELAY);
		pollA = gpioRead(28);
	}
	if(pollB){
		delay(BOUNCE_DELAY);
		pollB = gpioRead(29);
	}
	
	//does things based on button press
	if(pollA && pollB) break;


	//button A
	if(pollA){
		if(timing > 32)
			timing /= 2;
		else
			direction *= -1;
			
	}		


	//Button B
	if(pollB){
		if(timing < 1024)
			timing *= 2;
		else
			direction *= -1;
			
	}	

	//makes sure button is not held down
	//if button is not pressed down it will set a flag
	//that will let polling happen again
	do {
		ledToggle(i%8);
		delay(timing);
		ledToggle(i%8);
		i += direction;
	} while(gpioRead(28) || gpioRead(29)); 

	}
	hexCtrl(0x00);
	return 0;
}