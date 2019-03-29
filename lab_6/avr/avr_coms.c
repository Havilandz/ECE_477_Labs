/*

Serial Communications Routines for AVR side
of ece477 lab 6 using lab specifications

Authors: Zach Haviland
	 Steph Poirier
	Hunter Gross
Communication Details: 
Baud:1200hz
8 bit no paritu 2 stop 

*/

#include<stdint.h>
#include "avr_coms.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define UBRRN 831 
static FILE serial_stream = (FILE)FDEV_SETUP_STREAM(serial_write, serial_read, _FDEV_SETUP_RW);

//Sets up stdin and stdout for the AVR as well as serial parameters, returns a file descriptor to the serial stream
void serial_init(void)
{
	UBRR0H= (unsigned char)(UBRRN > 8);
	UBRR0L=(unsigned char)UBRRN; // 1200 BAUD FOR 8MHZ SYSTEM CLOCK
	//UBRR0H= 0;
	//UBRR0L= 96; // 1200 BAUD FOR 1MHZ SYSTEM CLOCK

	UCSR0A= 1<<U2X0;
	UCSR0C= (1<<USBS0)|(3<<UCSZ00) ;  // 8 BIT NO PARITY 2 STOP
	UCSR0B=(1<<RXEN0)|(1<<TXEN0)  ; //ENABLE TX AND RX ALSO 8 BIT
	stdin=&serial_stream;
	stdout=&serial_stream;


}
//reads from serial input on stdin
int  serial_read(FILE * fp)
{
	while((UCSR0A & (1<<RXC0)) == 0); 	//waits for a single char, multiple chars could be lost
	return UDR0;
}

//Sends to stdout on serial
int  serial_write(char key, FILE * fp)
{
	while((UCSR0A & (1<<UDRE0)) == 0); 	//waits until register is empty
	UDR0 = key;
	return 0;
}

