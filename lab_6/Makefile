TARGET=lab6
CFLAGS= -Wall -g
OBJS=lab6.o
LIBS= -lwiringPi

all: ${TARGET} cool

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}
cool: cool.o
	${CC} -o cool cool.o ${LIBS}
clean:
	rm -f ${OBJS} ${TARGET}

