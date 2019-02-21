/*
 * ECE477 Lab 3: LED CPU load monitor.
 * 
 * Authors: Steph Poirier, Hunter Gross, Zach Haviland
 * Spring 2019
 * 
 * This lab uses the LED control program from LAB 2 to
 * implement a system load meter using information from
 * /proc/loadavg. Note that he LED control progrm, ledctrl,
 * from last lab must be present in the same folder as this
 * program for this program to function.
 * 
 * The program will fork itself to create a child which will
 *  * run in the background. The parent will then creat the file
 * tombstone and will write the child's process ID to that file 
 * then exit, making an orphan.
 * 
 * If the program detects that the file tombstone already exists it
 * will read the PID from tombstone and kill the process with
 * that ID, i.e. the orphaned child. 
 * 
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>


int main(int argc, char *argv[]){

	//Holds value read from files
	double fileval = 0;
	//Used to look at /proc/loadavg
	FILE *fp = NULL;
	//used to look at tombstone if it exits
	FILE *angel = NULL;
	//holds child PID
	uint32_t cpid = 0;
	//temporary storage for strings. 
	char message[30] ;



	/*kills the process with PID in tombstone
	if tombstone exists */ 
	if((angel = fopen("tombstone","r"))){

		//gets the PID from file
		fscanf(angel,"%lf",&fileval);
		
		sprintf(message,"kill -9 %d",((int)fileval));
	
		//Error Checking and kill command
		if(system(message) == -1){
			printf("Error: Failed to kill orphan\n");
			fclose(angel);
			return 1;
		}
		/*get rid of tombstone so next time the program
		run it doesn't try to kill any orphans*/
		fclose(angel);
		system("rm tombstone");
		system("./ledctrl 0");
		printf("Orphan loadMeter killed successfully\n");

		return 0;
	}

	
	/* Creates the fork. The parent writes the childs
	process id to the file tombstone and returns */
	cpid = fork();
	
	//checks to make sure fork worked
	if(cpid == -1){
		printf("Failed to create child. Aborting\n");
		return -1;
	}
	/*cpid for parent and child are different values. 
	This if block only runs in the parent */
	if(cpid) {
		angel = fopen("tombstone","w+");
	
		if(!angel){ // If the fopen fails, exit 
			printf("Error: Failed to create tombstone\n");
			return -1;
		}
		fprintf(angel, "%d", cpid);
		fclose(angel);
		return 0;
	}
	
	printf("Orphaned child loadMeter running in background\n");
	


	/* First LED is always on, also checks that
	ledctrl is in the file with this program */
	if(system("./ledctrl 0x01")==-1){
		printf("Error: program ledctrl not present\n");
		return 1;
	}


	while(1) {

		fp = fopen("/proc/loadavg","r");

		/* Error checking */
		if(fp == NULL){
			printf("error opening file, exiting\n");
			return 1;
		}

		//First value encountered is minute load average
		fscanf(fp, "%lf", &fileval);

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
			printf("failed to close /proc/loadavg. Aborting program\n");
			return 1;
		}
		delay(10000);
	}
}
