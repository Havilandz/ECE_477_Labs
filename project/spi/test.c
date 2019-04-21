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


int display[8];


void max7219_init(void);
void spi_clear(void);
void spi_write(int addr, int data);
void send_byte(int byte);

void main(int argc, char* argv[]) 
{
	int i;
	max7219_init();
	
		spi_write(0x01, 0xff);
		spi_write(0x00, 0x0f);
		spi_write(0x00, 0xa0);
		spi_write(0x00, 0x0a);
	
	while(1) {
		
		_delay_ms(500);
	}		
}

void max7219_init(void)
{
	DDRA = 0xff;
	spi_write(0x09, 0);
	// Intensity: 3 (0-15)
    	spi_write(0x0A, 1);
    	// Scan limit: All "digits" (rows) on
    	spi_write(0x0B, 7);
    	// Shutdown register: Display on
    	spi_write(0x0C, 1);
    	// Display test: off
    	spi_write(0x0F, 0);
//    	spi_clear();


	
}


void write_row(int board, int row, int data){	
	ct1 = 0;
	ct2 = 0;
	ct3 = 0;
	CS_HIGH;
	switch(board)
	case: 0
	case 1
	case 2






}

void noop(void){
	send_byte(0);
	send_byte(0);
}
void send_byte(int byte){
	int ct = 0;
	for(ct = 7;ct >= 0; ct--)
	{
		CLK_LOW;
		if(byte & (1<<ct))
			DATA_HIGH;
		else
			DATA_LOW;		
		CLK_HIGH;
	}



}
