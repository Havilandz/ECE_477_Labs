TARGET=uartPi
CFLAGS= -Wall -g
OBJS= UART_pi.o
LIBS= -lwiringPi

all: ${TARGET} 

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}


clean:
	rm -f ${OBJS} ${TARGET}

