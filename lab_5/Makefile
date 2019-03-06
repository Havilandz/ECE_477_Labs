AVR_CONF=-C ~/ece477/ECE_477_Labs/avrdude_gpio.conf
CC=avr-gcc
CFLAGS=-mmcu=atmega324


fuses:
	sudo avrdude $(AVR_CONF) -c pi_1 -p atmega324pa -U lfuse:w:0x52:m -U hfuse:w:0x99:m -U efuse:w:0xff:m


