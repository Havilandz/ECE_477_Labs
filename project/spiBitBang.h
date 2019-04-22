/* 
 * SPI Bit Bang Header File
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 */
#ifndef SPIBITBANG_H
#define SPIBITBANG_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

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
#endif

