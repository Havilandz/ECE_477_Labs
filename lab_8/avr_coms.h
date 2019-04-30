/*

Serial Communications Routines for AVR side
of ece477 lab 6 using lab specifications
The UART pins are TXD0 on PD1, physical pin 15
and RXD0 on PD0 physical pin 14
Authors: Zach Haviland
	Steph Poirier
	Hunter Gross`


*/

#include<stdint.h>
#include<stdio.h>
//Sets up stdin and stdout for the AVR as well as serial parameters
void serial_init(void);
//It occurs to me that the below two prototypes probably shouldn't be here
int  serial_read(FILE *);
int  serial_write(char, FILE *);

