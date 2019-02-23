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
 * This code uses GPIO pins 0 - 7 for the LEDs and GPIO28 and GPIO29 for the push buttons 
 */

int main(int argc, char **argv)
{
	while(1){
		
	//polling and debouncing
	




	//does things based on button press



	//button A




	//Button B



	




	//makes sure button is not held down
	//if button is not pressed down it will set a flag
	//that will let polling happen again
	

	}
}
