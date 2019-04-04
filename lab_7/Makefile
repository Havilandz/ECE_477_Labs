TARGET=uartPi
CFLAGS= -Wall -g
OBJS= UART_pi_lab7.o
LIBS= -lwiringPi

all: ${TARGET} 

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}


clean:
	rm -f ${OBJS} ${TARGET}

