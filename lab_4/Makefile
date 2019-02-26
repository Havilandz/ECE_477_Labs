TARGET= lab4
CFLAGS= -Wall -g
OBJS= main.o ledctrl.o gpioRead.o
LIBS= -lwiringPi


${TARGET}: ${OBJS}
	${CC} ${OBJS} ${LIBS}
clean:
	rm -f ${OBJS} ${TARGET}
