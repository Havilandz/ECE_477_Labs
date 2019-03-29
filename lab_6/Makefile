TARGET=lab6
CFLAGS= -Wall -g
OBJS=lab6.o
LIBS= -lwiringPi

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}
clean:
	rm -f ${OBJS} ${TARGET}

