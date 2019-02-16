
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
	
	/* Initialize GPIO pins */
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	
	/* First LED is always on */
	digitalWrite(1, HIGH);
	
	while(1){
		fscanf(fp, "%d", &fileval);
		
		if(fileval >= 8){
			//turn led 8 on
		}
		
		if(fileval >= 4) {
			//turn led 7 on
		}
		
		if(fileval >= 2) {
			//turn led 6 on
		}
		
		if(fileval >= 1) {
			//turn led 5 on
		}
		
		if(fileval >= 0.50) {
			//turn led 4 on
		}
		
		if(fileval >= 0.25) {
			//turn led 3 on
		}

		if(fileval >= 0.125) {
			//turn led 2 on
		}
		/* reset pointer to the start of the file */
		rewind(fp);
	}
}
