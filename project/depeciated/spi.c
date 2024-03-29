/*
 * SPI Initialization Source File
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 */

#include "spi.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
//Defines missing USART spi macros
#ifndef UCPHA0
#define UCPHA0 1
#endif
#ifndef UDORD0
#define UDORD0 2
#endif

static FILE serial_stream = (FILE)FDEV_SETUP_STREAM(serial_write, serial_read, _FDEV_SETUP_RW);

/* Initializes 3 Pin SPI on the USART pins of an AVR */
void USART_SPI_init()
{



	UBRR0 = 0;
	XCK_DDR |= (1<<XCK_BIT);

	UCSR0C &= ~(1<<UCPHA0); // Set Clock Phase
	UCSR0C &= ~(1<<UDORD0); // Set Big Endian (MSB)
	//Set SPI mode 1
	UCSR0C |= (1<<UMSEL01) | (1<<UMSEL00);


	UCSR0B |= (1<<TXEN0); // Enable Transmitter

	/* BAUD Rate */
	UBRR0H |= (unsigned char)(UBRRN >> 8); 
	UBRR0L |= (unsigned char)UBRRN;
	

	stdin = &serial_stream;
	stdout = &serial_stream;	
	
}
	
/* Initializes SPI on an AVR 
void SPI_init()
{
	SPCR = 0; // Clear SPI control register
	SPCR |= (1<<SPE); // Enable SPI
	SPCR |= (1<<MSTR); // Set master mode
	SPCR |= (1<<SPR1); // Prescaler  = 64

	SPI_MOSI_DDR |= (1<<SPI_MOSI_PIN); // MOSI output
	SPI_SS_DDR |= (1<<SPI_SS_PIN); // SS output
	SPI_SCK_DDR |= (1<<SPI_SCK_PIN); // SCK output 
	SPI_MISO_DDR &= ~(1<<SPI_MISO_PIN) // MISO input

	SPI_SS_PORT |= (1<<SPI_SS_PIN); // Deselect Slave
	SPI_MISO_PORT |= (1<<SPI_MISO_PIN); //MISO pullup

	
}
*/
//reads from serial input on stdin
int  serial_read(FILE *fp)
{
	while((UCSR0A & (1<<RXC0)) == 0); 	//waits for a single char, multiple chars could be lost
	return UDR0;
}

//Sends to stdout on serial
int  serial_write(char key, FILE *fp)
{
	while((UCSR0A & (1<<UDRE0)) == 0); 	//waits until register is empty
	UDR0 = key;
	return 0;
}

