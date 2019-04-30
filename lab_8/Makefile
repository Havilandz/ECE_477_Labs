#AVR Makefile
OBJS=
AVR_CONF=../avrdude_gpio.conf
ACC=avr-gcc
CHIP=atmega88
ACFLAGS=-mmcu=${CHIP} -O1 

program: a.hex
	sudo avrdude ${AVR_CONF} -c pi_1 -p ${CHIP} -U flash:w:a.hex:i

a.hex: a.out
	avr-objcopy -j .text -j .data -O ihex a.out a.hex

a.out: ${OBJS}
	${ACC} ${ACFLAGS} ${OBJS}

fuses:
	sudo avrdude ${ARV_CONF} -c pi_1 -p ${CHIP} -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

clean:
	rm -f *.hex *.out
