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

/* Writes zeros to every LED to clear the display */
void clear(void);

/* Configures the display driver and the spi pins */
void max7219_init(void);

/* writes data to a specific 8x8 matrix using spi_write() */
void write_board(int board, int row, int data);	

/* sends one byte of data via bit bang spi */
void send_byte(int byte);

/* sends two 0 bytes via bit bang spi which is considered a no-op
by the max7219 */
void noop(void);

/* writes two bytes using send_byte(). The first byte is the address 
on the board, the second byte is the hex data for the corresponding column. */
void spi_write(int addr,int  data);

#endif
