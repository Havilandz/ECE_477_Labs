/*
 * SPI Test Communication
 * Author: Hunter Gross
 *
 */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "spi.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

int main(int argc, char* argv[]) 
{
	FILE *output;
	uint16_t msg = 0x01aa;
	
	USART_SPI_init();
	_delay_ms(500);
	output = stdout;

	fprintf(output, "%d\r\n", msg);		

}

