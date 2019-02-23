OFLAGS = -Wall -g -c
CFLAGS = -Wall -g -lwiringPi


lab4: main.o ledctrl.o gpioRead.o
	gcc main.o ledctrl.o gpioRead.o  $(CFLAGS) -o lab4
ledctrl.o: ledctrl.h ledctrl.c
	gcc $(OFLAGS) ledctrl.c
gpioRead.o: gpioRead.h gpioRead.c
	gcc $(OFLAGS) gpioRead.c
main.o: main.c
	gcc $(OFLAGS)  main.c 
clean:
	rm *.o lab4
