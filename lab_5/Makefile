TARGET=avrcode.c
AVR_CONF=-C ../avrdude_gpio.conf
CC=avr-gcc
CHIP=atmega324pa
CFLAGS=-mmcu=${CHIP}

program: a.hex
	sudo avrdude ${AVR_CONF} -c pi_1 -p ${CHIP} -U flash:w:a.hex:i


hex: a.out
	avr-objcopy -j .text -j .data -O ihex a.out a.hex

compile: ${TARGET}
	${CC} ${CFLAGS} ${TARGET}

fuses:
	sudo avrdude ${AVR_CONF} -c pi_1 -p ${CHIP} -U lfuse:w:0x52:m -U hfuse:w:0x99:m -U efuse:w:0xff:m
clean:
	rm -f *.hex *.out
