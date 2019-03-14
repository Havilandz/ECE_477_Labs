TARGET= clock_adjust
CFLAGS= -Wall -g
OBJS= main.o lab5ISR.o 
LIBS= -lwiringPi

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}
clean:
	rm -f ${OBJS} ${TARGET}
