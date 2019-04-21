/*
 * SPI Bit Bang Source File
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "spiBitBang.h"

void max7219_init(void)
{
	DDRA = 0xff;
	int ct = 0;
	CS_LOW;
	for(ct = 0; ct<4; ct++){ 
		spi_write(0x09, 0);
		// Intensity: 3 (0-15)
	    	spi_write(0x0A, 1);
	    	// Scan limit: All "digits" (rows) on
	    	spi_write(0x0B, 7);
	    	// Shutdown register: Display on
	    	spi_write(0x0C, 1);
	    	// Display test: off
    		spi_write(0x0F, 0);
    		
	}
	CS_HIGH;
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
	spi_write(i+1, 0);
	CS_HIGH;
    }
}