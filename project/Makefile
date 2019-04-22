#AVR programmer makefile
OBJS= stacker.c spiBitBang.c
AVR_CONF=-C ../avrdude_gpio.conf
ACC=avr-gcc
CHIP=atmega324pa
ACFLAGS=-mmcu=${CHIP} -O1 -Wl,-u,vfprintf -lprintf_flt 
LIBS= -lprintf_flt -lm -lfp

program: a.hex
	sudo avrdude ${AVR_CONF} -c pi_1 -p ${CHIP} -U flash:w:a.hex:i




a.hex: a.out
	avr-objcopy -j .text -j .data -O ihex a.out a.hex

a.out: ${OBJS}
	${ACC} ${ACFLAGS} ${OBJS}

fuses:
	sudo avrdude ${AVR_CONF} -c pi_1 -p ${CHIP} -U lfuse:w:0xD2:m -U hfuse:w:0xD1:m -U efuse:w:0xff:m
clean:
	rm -f *.hex *.out


