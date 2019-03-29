/*

Simple High Low Guessing Game Over UART
Authors: Zach Haviland, Steph Poirier, Hunter Gross



*/

#include "avr_coms.h"
#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdlib.h>


/*Initialize the serial communication at 1200 baud, 8 data bits, no parity, and 2 stop bits.*/
/*Use high_low to find the number generated by the random number generator.*/

void high_low(void);
int main(void)
{
	serial_init();
	_delay_ms(3000);
	while(1)
	{
		high_low();

	}
	return 0;
}

/*
find a value created by the random number generator between 0 and 5000 by telling the user
if their guess is too high or too low and allowing them keep guessing until they get it correct
*/

void high_low(void)
{
	FILE *fpinput, *fpoutput;
	int solution, guess;
	
	solution = rand()%5000;
	fpinput = stdin;
	fpoutput = stdout;
	fprintf(fpoutput,"Welcome to the high-low guessing game \r\n");	
	fprintf(fpoutput, "Enter a positive whole number between 0 and 5,000 \r\n");
	
	guess = solution + 1; //prevents corner case where guess == answer at beginning of program
	
	while(guess != solution)
	{
		while(fscanf(fpinput, "%d", &guess) != 1) 
			fscanf(fpinput, "%*s");
		if(guess < solution)
			fprintf(fpoutput, "Your guess was too low. Please try again\r\n");
		else if(guess > solution)
			fprintf(fpoutput, "Your guess was too high. Please try again\r\n");
		else fprintf(fpoutput, "RIGHT ON, YOU GOT IT! WAY TO SLAY THE DAY!\r\n");
	}
}
