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
 * This code uses GPIO pins 0 - 7 for the LEDs and GPIO27 and GPIO28 for the push buttons A and B
 * respectively
 *
 * Push button C increases the amount of LEDs that "move". for each press of button C, the number
 * of LEDs lit at any given time increases by 1 until all of the LEDs are lit. Pressing button C again
 * after it has reached it's bound resets the number of lit LEDs to 1.
 *
 */
#include <stdint.h>
#include "gpioRead.h"
#include <wiringPi.h>
#include "ledctrl.h"

#define BOUNCE_DELAY 10

void buttonInterrupt(void);

// flag to trigger an exit on button A+B press
volatile int GLOBAL_EXIT_FLAG = 0;

// flags for recording button presses
uint32_t pollA = 0;
uint32_t pollB = 0;
uint32_t pollC = 0;

// amount of LEDs to be toggled each step
int amount = 0; 

// default delay time in ms
int timing = 1024;

// signed direction bit
int direction = 1;

int main(int argc, char **argv)
{	
	uint32_t i = 0; // Loop counter

	// Initialization
	ledInit();
	gpioInit(27);
	gpioInit(28);
	gpioInit(29);

	// Setup hardware interrupts
	wiringPiISR(27, INT_EDGE_FALLING, buttonInterrupt);
	wiringPiISR(28, INT_EDGE_FALLING, buttonInterrupt);
	wiringPiISR(29, INT_EDGE_FALLING, buttonInterrupt);

	while(1){

		// Main routine for toggling LEDs
		ledFollow(i%8, amount, direction);
		delay(timing);
		ledFollow(i%8, amount, direction);
		i += direction;
		
		/* Interrupt routine for button c is outside
		ISR due to timing issues */
		if(pollC)
		{
			if(++amount > 7)
				amount =0;
			pollC = 0;
		}

		// Exit Condition
		if(GLOBAL_EXIT_FLAG) break;		

	}
	
	hexCtrl(0x00); // Clears all LEDs before shutdown
	return 0;
}

// Interrupt Service Routine
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
		 
	if(gpioRead(29)){
		delay(BOUNCE_DELAY);
               pollC = gpioRead(29);
	 }	 

	// Exit condition
        if(pollA && pollB) 
		GLOBAL_EXIT_FLAG = 1;

         //button A
	if(pollA && !GLOBAL_EXIT_FLAG){
		if(timing > 32) timing /= 2;
                
		else direction *= -1;
	}

         //Button B
	if(pollB && !GLOBAL_EXIT_FLAG){
		if(timing < 1024) timing *= 2;
                
		else direction *= -1;
	}
}


