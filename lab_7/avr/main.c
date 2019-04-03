#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "led.h"
#include "avr_adc.h"

int main(int argc, char* argv[])
{
	initPS();
	initLEDs();

	FILE *input, *output;
	uint8_t n = 0;
	input = stdin;
	output = stdout;

	fscanf(input, "%i", &n);

	setLEDs(n);
	measurePS();	
}
