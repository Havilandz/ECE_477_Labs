/*
Lab 5 automatic clock programmer
Authors:
Zach Haviland
Hunter Gross
Steph Poirier

Frequency is read on physical pin 11
This program reads a waveform from the avr clock output on physical pin 11 of the RPI
and reprograms the EEPROM of the AVR to get the clock to be closer to 100hz. It iterates
this process until the signal is within 99 - 101 hz
NOTE: This code is a very specific application and is generally not going
to work with other stuff.  
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
//ISR puts clock timeStamps in here.
//every two timeStamps constitudes one period
//of the input waveform
clock_t timeStamps[20] = {0};
//index for accessing the timeStamps array
uint32_t i= 0;

void FREQ_ISR(void);


int main()
{	
	//Has wiringpi use the BCM gpio numbers, which matches with gpio commands in terminal
	wiringPiSetup();	

	//Holds final frequency measurement
	double freq = 0;
	//A counter
	uint32_t c = 0;
	/* Sets up interrupts */

	wiringPiISR(0,INT_EDGE_FALLING,FREQ_ISR);

	//waits for all timestamps to be filled
	while(timeStamps[20] == 0){;}

	//Calculates frequency averaged over 10 periods
	for(c = 0;c < 10;c++){
		freq += (double)(timeStamps[(2*c)+1]-timeStamps[2*c]);	
	}
	freq = 1./freq*10*CLOCKS_PER_SEC;//CLOCKS_PER_SEC macro converts us to hz properly 

	printf("%.8f\n",freq);

	return 0;




}

void FREQ_ISR(void)
{	
	//if statement prevents the case where another interrupt
	//goes off while this one is still going at i = 19
	//which would segfault this off the face of the fucking planet
//	if(i<=19)
		timeStamps[i] = clock();
	//disabled interrupts after 20 timeStamps
//	if(i >= 19)
//		system ("/usr/local/bin/gpio edge 0 none") ;
	i++;
	printf("%i\n",i);
}

