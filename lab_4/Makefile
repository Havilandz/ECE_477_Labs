loadMeter: main.o ledctrl
	gcc main.o -Wall -g -o loadMeter -lwiringPi
main.o: main.c
	gcc -Wall -g -c main.c 
clean:
	rm *.o loadMeter
