#VR programmer makefile
OBJS= avrcode.c
AVR_CONF=-C ../avrdude_gpio.conf
ACC=avr-gcc
CHIP=atmega324pa
ACFLAGS=-mmcu=${CHIP} -O1 
LIBS= 

program: a.hex
	avrdude -c avrispmkII -P usb -p ${CHIP} -U flash:w:a.hex:i




a.hex: a.out
	avr-objcopy -j .text -j .data -O ihex a.out a.hex

a.out: ${OBJS}
	${ACC} ${ACFLAGS} ${OBJS}

fuses:
	avrdude -c avrispmkII -P usb -p ${CHIP} -U lfuse:w:0xD2:m -U hfuse:w:0xD1:m -U efuse:w:0xff:m
clean:
	rm -f *.hex *.out


