lab4: main.o ledctrl.c ledctrl.h gpioRead.c gpioRead.h
	gcc main.o -Wall -g -o lab4 -lwiringPi
main.o: main.c
	gcc -Wall -g -c main.c 
clean:
	rm *.o lab4
