#AVR Programmer Makefile
OBJS=stacker.c ./spi/spi.c
AVR_CONF=-C ../avrdude_gpio.conf
ACC=avr-gcc
CHIP=atmega324pa
ACFLAGS=-mmcu=${CHIP} -O1
LIBS=

program: a.hex
	

a.hex: a.out
	avr-objcopy -j .text -j .data -O ihex a.out a.hex
		
a.out: ${OBJS} ./spi/spi.h
	${ACC} ${ACFLAGS} ${OBJS}

fuses:

clean:
	rm -f *.hex *.out
