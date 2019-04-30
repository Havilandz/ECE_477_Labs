#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "avr_adc.h"
#include <util/delay.h>
#define BANDGAP_V 1.1F

void initPS(void)
{
	ADMUX |= (1<<REFS0); //ADC reference set to avcc
	ADMUX |= ((1<<MUX4)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1)); //Sets ADC input to 1.1V bandgap reference. 
//	ADMUX |= (1<<ADLAR); //sets left alligned outputs
	//Sets 1/64 prescaler, ADC clock frequency is 125kHz
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1));
	//enable ADC
	_delay_ms(2);
	ADCSRA |= (1<<ADEN);


}


int adcRead(void)
{
	volatile unsigned int temp;
	ADCSRA |= (1<<ADSC); //Start ADC conversion

	while(ADCSRA&(1<<ADSC)); //wait for conversion to be done
	temp = (ADCL|ADCH<<8);
	//return BANDGAP_V*1024./(ADCH<<2); //Calculate reference voltage Avcc
	return temp; //Calculate reference voltage Avcc


}
