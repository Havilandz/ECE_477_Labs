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
#include "../led.h"

int main(int argc, char* argv[]) 
{
	FILE *output;
	uint16_t msg = 0x01ff;
	uint16_t msg2 = 0x0100;
	uint16_t no_decode = 0x0900;
	initLEDs();	
	USART_SPI_init();
	_delay_ms(500);
	output = stdout;
	fwrite(&no_decode, 2, 1, output);
	while(1){
		setLEDs(0x00);
		fwrite(&msg, 2, 1, output);		
		setLEDs(0x01);
		_delay_ms(500);
		setLEDs(0x00);
		fwrite(&msg2, 2, 1, output);		
		setLEDs(0x01);
		_delay_ms(500);

	}
}

