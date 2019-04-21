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

#define CS_HIGH PORTA |= (1<<PA0)
#define CS_LOW PORTA &= ~(1<<PA0)
#define CLK_HIGH PORTA |= (1<<PA1)
#define CLK_LOW PORTA &= ~(1<<PA1)
#define DATA_HIGH PORTA |= (1<<PA2)
#define DATA_LOW PORTA &= ~(1<<PA2)



void max7219_init(void);

void spi_write(int addr, int data);

int main(int argc, char* argv[]) 
{
	FILE *output;
	uint16_t msg = 0x0155;
	uint16_t msg2 = 0x0100;
	uint16_t no_decode = 0x0900;
	USART_SPI_init();
	_delay_ms(500);
	output = stdout;
	max7219_init();
	
	while(1){

	
	



	}
}

void max7219_init(void){


	
}
void spi_write(int addr, int data){	
	CS_LOW();
	


}

void send_byte(int byte){
	int ct = 0;
	for(ct = 0;ct <8; ct++)
	{
		CLK_LOW();
		

	}



}
