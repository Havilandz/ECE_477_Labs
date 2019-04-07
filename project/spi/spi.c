*
 * SPI Initialization Source File
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 */

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include "spi.h"


/* Initializes SPI on an AVR */
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


