/*
 * Lab 5 automatic clock programmer
 * Authors:
 * Zach Haviland
 * Hunter Gross
 * Steph Poirier
 * 
 * Frequency is read on physical pin 11
 * This program reads a waveform from the avr clock output on physical pin 11 of the RPI
 * and reprograms the EEPROM of the AVR to get the clock to be closer to 100hz. It iterates
 * this process until the signal is within 99 - 101 hz
 * The code takes DATA_LENGTH samples at a sampling period of about 2500uS, or 400HZ frequency
 * Note that reading and storing the data takes about 11.20uS and this is factored into the sampling delay
 * and the sampline delay was also calibrated against the digilant discovery
 * NOTE: This code is a very specific application and is generally not going
 * to work with other stuff.  
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define DATA_LENGTH 1000 

void program_board(int offset);
float calc_freq(uint32_t *data,unsigned int length, int Fs);
char decToHexa(int n);
int main()
{	
	
	wiringPiSetup();
	//DATA_LENGTH sample array. We're only going to worry about a subset in the middle of this
	uint32_t *data_pointer = (uint32_t*)malloc(DATA_LENGTH*sizeof(uint32_t));
	//A counter
	uint32_t i = 0;
	//Gets the frequency back
	float freq = 0;
	//Used for building adjustmetns to EEPROM
	int32_t EEPROM_offset = 0;
	int32_t EEPROM_range[2] = {-15,15};
	//sets reading pin to input
	pinMode(0,INPUT);
	while(freq < 90 || freq > 110){
		//takes samples at ~400Hz 
		for(i = 0;i<DATA_LENGTH;i++){
			data_pointer[i] = digitalRead(0);	
			usleep(2432);
		}
		//calculates frequency
		freq = calc_freq(data_pointer, DATA_LENGTH, 400);
		printf("Frequency: %.3fhz\n",freq);
		//determines offset to try when reprogramming
		if(freq > 110){
			EEPROM_range[1] = EEPROM_offset -1;
		}
		if(freq < 90){
			EEPROM_range[0] = EEPROM_offset +1;		
		}	
		EEPROM_offset = (EEPROM_range[0] + EEPROM_range[1])/2;	
		printf("OSCAL OFFSET: %i\n",EEPROM_offset);
		program_board(EEPROM_offset);
	}

	return 0;
	

}
//length refers to the number of elementst in the 0 indexed array data. Fs is the sampling frequency in hz
float calc_freq(uint32_t *data,unsigned int length, int Fs)
{	
	//Another counter
	uint32_t i = 0;
	//counter number of periods calculated. Used as part of average period calculation
	uint32_t periods = 0;
	//Used for calculating average period.
	uint32_t current_edge = -1;
	uint32_t previous_edge = -1;
	//Running total of all periods time. Divied by periods to calculate average period time
	uint32_t totalT = 0;
	//traverses array finding indexes where the signal goes high to low
	while(i<length){
		//go until a high is hit	
		while(data[i] == 0 && i<length){
			i++;
		}
		//go until a low is hit
		while(data[i] == 1 && i<length){
			i++;
		}
		previous_edge = current_edge;
		current_edge = i;
		//runs whenever there's a full period between previous_edge and current_edge
		if((previous_edge != -1) && (i< length)){
			totalT += (current_edge - previous_edge);
			periods++;
		}

		
	}
	//calculates average period and returns frequency
	return ((float)periods)/totalT*Fs;
}
//programs the board EEPROM memory
void program_board(int offset)
{
	int sign = offset/offset;
	int magnitude = decToHexa(offset*sign);
	char programming[120];
	sprintf(programming, "sudo avrdude -C ../../avrdude_gpio.conf -c pi_1 -p atmega324pa -D -U eeprom:w:0x%i%c:m",sign,magnitude); 
	system(programming);
	return;

}

// function to convert decimal to hexadecimal. Only works for values up to F 
char decToHexa(int n) 
{	
	// char array to store hexadecimal number 
	char hexaDeciNum[100]; 
	  
	// counter for hexadecimal number array 
	int i = 0; 
	while(n!=0) 
	{	
		// temporary variable to store remainder 
		int temp  = 0; 
	   
		// storing remainder in temp variable. 
		temp = n % 16; 
	   
		// check if temp < 10 
		if(temp < 10) { 
			hexaDeciNum[i] = temp + 48; 
			i++; 
		} else{ 
			hexaDeciNum[i] = temp + 55; 
			i++; 
		} 
	   
		n = n/16; 
	}
	return hexaDeciNum[0];
} 
