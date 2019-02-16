/*
ECE477 Lab 3: LED CPU load monitor.

Authors: Steph Poirier, Hunter Gross, Zach Haviland
Spring 2019

This lab uses the LED control program from LAB 2 to
implement a system load meter using information from
/proc/loadavg. Note that he LED control progrm, ledctrl,
from last lab must be present in the same folder as this
program for this program to function.


 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



int main(int argc, char *argv[]){

	//Holds value read from loadavg
	double fileval = 0;
	//Used to look at /proc/loadavg
	FILE *fp = NULL;


	/* First LED is always on, also checks that
	ledctrl is in the file with this program */
	if(system("./ledctrl 0x01")==-1){
		printf("error: program ledctrl not present");
		return 1;
	}


	while(1) {

		fp = fopen("/proc/loadavg","r");

		/* Error checking */
		if(fp == NULL){
			printf("error opening file, exiting.");
			return 1;
		}

		//First value encountered is minute load average
		fscanf(fp, "%lf", &fileval);

		printf("%.3f\n",fileval); ///For debugging

		if(fileval >= 8){
			//turn all leds on
			system("./ledctrl 0xff");
		}

		else if(fileval >= 4) {
			//turn leds <=7 on
			system("./ledctrl 0x7f");
		}

		else if(fileval >= 2) {
			//turn leds <=6 on
			system("./ledctrl 0x3f");
		}

		else if(fileval >= 1) {
			//turn leds <=5 on
			system("./ledctrl 0x1f");
		}

		else if(fileval >= 0.5) {
			//turn leds <=4 on
			system("./ledctrl 0x0f");
		}

		else if(fileval >= 0.25) {
			//turn leds <=3 on
			system("./ledctrl 0x07");
		}

		else if(fileval >= 0.125) {
			//turn leds <= 2 on
			system("./ledctrl 0x03");
		}
		else{
			//turn led 1 on
			system("./ledctrl 0x01");
		}
		/* reset pointer to the start of the file */
		//rewind(fp);

		//closes file and checks to make sure it succeded
		if(fclose(fp)){
			printf("failed to close /proc/loadavg. Aborting program");
			return 1;
		}

	}
}
