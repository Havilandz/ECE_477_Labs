/* 
 * Lab 6 source code
 * Authors: Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * This program sends and receives data to and from the serial port
 * ttyS0 on a RPi 3. 
 *
 * 
 *
 */

#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<fcntl.h>
#define READ_BUFF_SIZE 50
#define KEY_BUFF_SIZE 10
#define STDIN 0

int accessSerial(int n, int fd);

int main(int argc, char* argv[])
{
	/* Buffer where key presses get stored */
	unsigned char keys[KEY_BUFF_SIZE];
	
	/* file descriptor for serial and ready flag for select()
	index for key buffer and process id */
	int fd, ready, i=0, pid;

	/* Buffer where data from serial is stored */
	unsigned char readOut[READ_BUFF_SIZE];

	/* fd_set structs for select() */
	fd_set read_set, write_set;
			
	/* fills the fd_set structs */
	FD_SET(fd, &write_set); // write to serial
	FD_SET(fd, &read_set); // read from serial 
	FD_SET(STDIN, &read_set); // read from stdin
	
	while (1) {
		/* select waits for a file descriptor to be ready to use */
		ready = select(2, &read_set, &write_set, NULL, NULL); 	

		/* select throws -1 for errors */
		if (ready == -1) {
			printf("Error with select()\n");
			return -1;
		}
		/* select throws 0 when it times out */
		else if (ready == 0) {
			printf("select() timed out\n");
			return 1;
		}
		/* if select is successful */
		else {
			if (FD_ISSET(fd, &read_set)) { // Serial read is ready
				accessSerial(0,fd);
				do {
				read(fd, &readOut, 1);
				}while (*readOut != '\0'); // Assumes data is null terminated
				accessSerial(1,fd);
			}
			if (FD_ISSET(fd, &write_set)) { // Serial write is ready
				accessSerial(0,fd);
				write(fd, &keys, 1);
				accessSerial(1,fd);
			}
			if(FD_ISSET(STDIN, &readOut)) { // stdin read is ready	
				keys[++i] = getchar();
			}
		}
	}
	return 0;
}

int accessSerial(int n, int fd)
{
	if (n == 0) {

		fd = open("/dev/ttyS0",O_RDWR);
	
		if (!fd) {
			printf("NULL POINTER! ttylS0 failed to open\n");
			return -1;
		}
		return fd;
	}
	if (n == 1) {
		close(fd);
		return 0;
 	}
}
