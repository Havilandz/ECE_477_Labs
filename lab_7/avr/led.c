#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void ledInit(void)
{
	DDRC = 0xff;
	PORTC = 0xff;
	_delay_ms(500);
	PORTC = 0x00l;
}

void toggleLEDs(uint8_t led)
{
	PORTC = led;
}
	
