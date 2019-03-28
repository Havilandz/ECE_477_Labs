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
int main(int argc, char* argv[])
{
	/* Buffer where key presses get stored */
	unsigned char keys[KEY_BUFF_SIZE];
	
	/* file descriptor for serial and ready flag for select() */
	int fd, ready, i=0;

	/* Buffer where data from serial is stored */
	unsigned char readOut[READ_BUFF_SIZE];

	/* fd_set structs for select() */
	fd_set read_set, write_set;
			
	/* Open the serial port */
	fd = open("/dev/ttyS0",O_RDWR);

	/* Error checking open() */
	if (!fd) {
		printf("NULL POINTER! ttyS0 failed to open\n");
		return -1;
	}

	/* fills the fd_set structs */
	FD_SET(fd, &write_set); // write to serial
	FD_SET(fd, &read_set); // read from serial 
	FD_SET(0, &read_set); // read from stdin

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
				do {
					read(fd, &readOut, 1);
				}while (*readOut != '\0'); // Assumes data is null terminated
			}
			if (FD_ISSET(1, &read_set)) { // stdin is ready for a key
				keys[++i] = (unsigned char)getchar();
			}
			if (FD_ISSET(fd, &write_set)) { // Serial write is ready
				write(fd, &keys, 1);
			}
		}
	}	
	return 0;
}
