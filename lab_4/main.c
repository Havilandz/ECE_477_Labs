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

void buttonInterrupt(void);

volatile int GLOBAL_EXIT_FLAG = 0;
//flags for recording button presses
uint32_t pollA = 0;
uint32_t pollB = 0;
uint32_t pollC = 0;


int timing = 1024;
int direction = 1;
int main(int argc, char **argv)
{
	int amount = 1;//amount of LEDS to be toggled based on button C presses
	

	uint32_t i = 0; // Loop counter




	ledInit();
	gpioInit(27);
	gpioInit(28);


	// Setup hardware interrupts
	wiringPiISR(27, INT_EDGE_RISING, buttonInterrupt);
	wiringPiISR(28, INT_EDGE_RISING, buttonInterrupt);
//	wiringPiISR(29, INT_EDGE_RISING, buttonInterrupt);

	while(1){
		
	


		ledToggle(i%8, amount, direction);
		delay(timing);
		ledToggle(i%8, amount, direction);
		i += direction;


		if(GLOBAL_EXIT_FLAG) break;		



	}
	hexCtrl(0x00);
	return 0;
}

void buttonInterrupt(void) {
	pollA = 0;
	pollB = 0;
	pollC = 0;

	// Debouncing
	 if(gpioRead(27)){
		delay(BOUNCE_DELAY);
                pollA = gpioRead(27);
	 }
        
	if(gpioRead(28)){
		delay(BOUNCE_DELAY);
                pollB = gpioRead(28);
         }
		 
//	if(gpioRead(29)){
//		delay(BOUNCE_DELAY);
 //               pollA = gpioRead(29);
//	 }	 

	 //does things based on button press

	// Exit condition
        if(pollA && pollB) 
		GLOBAL_EXIT_FLAG = 1;

         //button A
	if(pollA && !GLOBAL_EXIT_FLAG){
		if(timing > 32)
			timing /= 2;
                else
			direction *= -1;

                }

         //Button B
	if(pollB && !GLOBAL_EXIT_FLAG){
		if(timing < 1024)
			timing *= 2;
                else
			direction *= -1;

                }
}


