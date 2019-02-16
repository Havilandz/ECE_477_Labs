
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <errno.h>

int main(int argc, char *argv[]){

	FILE *fp = fopen("/proc/loadavg","r");
	double fileval;
	
	/* Error checking */
	if(fp == NULL){
		printf("error opening file, exiting.");
		return 1;
	}
	
	wiringPiSetup(); //Enable wiringPi


	/* First LED is always on */
	system("./ledctrl 0x01");


	while(1) {
		fscanf(fp, "%d", &fileval);

		if(fileval >= .125){
			//turn leds <=2 on
			system("./ledctrl 0x03");
		}

		if(fileval >= .25) {
			//turn leds <=3 on
			system("./ledctrl 0x07");
		}

		if(fileval >= .5) {
			//turn leds <=4 on
			system("./ledctrl 0x0f");
		}

		if(fileval >= 1) {
			//turn leds <=5 on
			system("./ledctrl 0x1f");
		}

		if(fileval >= 2) {
			//turn leds <=6 on
			system("./ledctrl 0x3f");
		}

		if(fileval >= 4) {
			//turn led <=7 on
			system("./ledctrl 0x7f");
		}

		if(fileval >= 8) {
			//turn all leds on
			system("./ledctrl 0xff");
		}
		/* reset pointer to the start of the file */
		rewind(fp);
	}
}
