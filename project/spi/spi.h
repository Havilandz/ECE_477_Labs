/*
 * SPI Initialization File
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * The macros are defined for use on an ATMEGA324PA AVR 
 *
 */


#ifndef SPI_H
#define SPI_H

#ifndef F_CPU
#define F_CPU 8000000UL // 8MHz Clock
#endif


/* Macros for SPI  */
#define SPI_SS_DDR DDRB
#define SPI_SS_PORT PORTB
#define SPI_SS_PIN PB4

#define SPI_MOSI_DDR DDRB
#define SPI_MOSI_PORT PORTB
#define SPI_MOSI_PIN PB5

#define SPI_MISO_DDR DDRB
#define SPI_MISO_PORT PORTB
#define SPI_MISO_PIN PB6

#define SPI_SCK_DDR DDRB
#define SPI_SCK_PORT PORTB
#define SPI_SCK_PIN PB7

#define SPI_SELECT_SLAVE SPI_SS_PORT &= ~(1<<SPI_SS_PIN)
#define SPI_DESELECT_SLAVE SPI_SS_PORT |= (1<<SPI_SS_PIN)

/* Macros for 3 pin SPI via USART */
#define UBRRN 31 // Divides the clock by 64 

/*  Function Prototypes */
void USART_SPI_init(void);
void SPI_init(void);


#endif
