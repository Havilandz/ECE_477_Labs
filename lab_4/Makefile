TARGET= lab4
CFLAGS= -Wall -g
OBJS= main.o ledctrl.o gpioRead.o
LIBS= -lwiringPi

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}
clean:
	rm -f ${OBJS} ${TARGET}
