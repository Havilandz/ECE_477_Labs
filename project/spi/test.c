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
	while(1);
}

void max719_init(void){
	spi_write(0x09, 0); //no decode
	spi_write(0x0A, 1); //intensity 3
	spi_write(0x0B, 7); // scan limit: akk "digits" rows (on)
	spi_write(0x0C, 1);
	spi_write(0x0F, 0);
	
}
void spi_write(int addr, int data);
	
	uint16_t msg = addr<<8 + data;
	setLEDs(0x00);
	fwrite(&msg, 2, 1, output);
	setLEDs(0x01);


}


