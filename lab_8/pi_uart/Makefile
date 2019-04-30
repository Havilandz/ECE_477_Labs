TARGET=uartPi
CFLAGS= -Wall -g -Wl,-u,vfprintf -lprintf_flt  
OBJS= UART_pi_lab7.o
LIBS= -lwiringPi -lm

all: ${TARGET} 

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}


clean:
	rm -f ${OBJS} ${TARGET}

