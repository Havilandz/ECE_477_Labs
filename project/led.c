#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void initLEDs(void)
{
	DDRA = 0xff; // Sets PORTC as output

	/* Test all LEDs */
	/*PORTC = 0xff;
	_delay_ms(500);
	PORTC = 0x00l;*/
}

void setLEDs(int led)
{
	PORTA = led;
}
	
