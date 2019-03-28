/*

Serial Communications Routines for AVR side
of ece477 lab 6 using lab specifications

Authors: Zach Haviland
	Steph _LASTNAME_


*/

#include<stdint>
#include "avr_coms.h"
//Sets up stdin and stdout for the AVR as well as serial parameters
void serial_init(void)
{
	
	




}
//reads from serial input on stdin
uint8_t  serial_read(FILE * fp)
{
	while((UCSR0A & (1<<RXC0)) == 0); 	//waits for a single char, multiple chars could be lost
	return UDR0;
}

//Sends to stdout on serial
void  serial_write(char key, FILE * fp)
{
	while((UCSR0A & (1<<UDRE0)) == 0); 	//waits until register is empty
	UDR0 = key;
	return 0;
}

