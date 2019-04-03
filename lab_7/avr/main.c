#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "led.h"
#include "avr_adc.h"
#include "avr_coms.h"

void main(int argc, char* argv[])
{

	serial_init();
	_delay_ms(3000);
		

	FILE *input, *output;
	int n = 0;
	double measurement;
	initLEDs();
	initPS();
	input = stdin;
	output = stdout;
	while(1) {
		fscanf(input, "%i", &n);
		n &= 0xff00;
		n = (uint8_t)n;
		setLEDs(n);
		measurement = measurePS();
		fprintf(output, "The power rail is at %d Volts\r\n", measurement);
	}
}
