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



void clear(void);

void max7219_init(void);
void write_board(int board, int row, int data);	
void write_row(int row, int data);
void send_byte(int byte);
void noop(void);
void spi_write(int addr,int  data);
void spi_latch(int addr,int  data);
void main(int argc, char* argv[]) 
{
	max7219_init();
	int ct = 0;
	int byte = 0x01;
	while(1){

/*	for(ct = 7;ct >= 0; ct--)
	{
		CLK_LOW;
//		_delay_ms(500);
		if(byte & (1<<ct)){
			DATA_HIGH;
//			_delay_ms(500);
		}else{
			DATA_LOW;		
//			_delay_ms(500);
		}
		CLK_HIGH;
//	_delay_ms(500);
	}*/
	_delay_ms(500);
	CS_LOW;	
	spi_write(0x05, 0xff&byte++);
	CS_HIGH;
/*
	_delay_ms(500);
	CS_LOW;	
	spi_write(0x05, 0x00);
	CS_HIGH;
*/



		
	
	}		
}

void max7219_init(void)
{
	DDRA = 0xff;
	int ct = 0;


	//No decoding
	spi_latch(0x09, 0);
	// Intensity: 3 (0-15)
    	spi_latch(0x0A, 1);
    	// Scan limit: All "digits" (rows) on
    	spi_latch(0x0B, 7);
    	// Shutdown register: Display on
    	spi_latch(0x0C, 1);
    	// Display test: off
	spi_latch(0x0F, 0);
    		

	clear();
	clear();
}


void write_board(int board, int row, int data){	
	
	int ct = 0;
	
	switch(board){
	case 0:
		for(ct = 8; ct>0; ct--){
			CS_LOW;
			noop();
			noop();
			noop();
			if(data & 1<<(ct-1))	
				spi_write(ct, 1<<(row-1));
			else
				spi_write(ct, 0<<(row-1));
			CS_HIGH;
		}
		break;
	case 1:
		for(ct = 8; ct>0; ct--){
			CS_LOW;
			noop();
			noop();
			if(data & 1<<(ct-1))
				spi_write(ct, 1<<(row-1));
			else
				spi_write(ct, 0<<(row-1));
			noop();
			CS_HIGH;
		}	
		break;
	case 2:
		for(ct = 8; ct>0; ct--){
			CS_LOW;
			noop();
			if(data & 1<<(ct-1))
				spi_write(ct, 1<<(row-1));
			else
				spi_write(ct, 0<<(row-1));
			noop();
			noop();
			CS_HIGH;
		}
		break;
	case 3:
		for(ct = 8; ct>0; ct--){
			CS_LOW;
			if(data & 1<<(ct-1))
				spi_write(ct, 1<<(row-1));
			else
				spi_write(ct, 0<<(row-1));
			noop();
			noop();
			noop();
			CS_HIGH;
		}
		break;
	default:
		noop();
		noop();
		noop();
		noop();			
	}



}


void noop(void){
	send_byte(0);
	send_byte(0);
}
	
void spi_write(int addr,int  data){

	send_byte(addr);
	send_byte(data);

}

void spi_latch(int addr,int  data){
	CS_LOW;
	send_byte(addr);
	send_byte(data);
	CS_HIGH;
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

void clear(void){
    int i;
    for (i = 0; i < 8; i++) {
	CS_LOW;
	spi_latch(i+1, 0);
	CS_HIGH;
    }
}
