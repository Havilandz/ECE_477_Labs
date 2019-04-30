/* 
 * Lab 6 source code
 * Authors: Bruce Segee Hunter Gross, Zach Haviland, Stephanie Poirier
 *
 * This program sends and receives data to and from the serial port
 * ttyS0 on a RPi 3. 
 *
 * 
 *
 */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <wiringPi.h>
#include <time.h>
void from_to(int ,int);
void setup_stdin(void);

int init(void);



 int main(int argc, char* argv[])
// todo command line arguments
 { 
	//The wiringpi stuff is to pull the reset line high to reset the avr then hold it low
	wiringPiSetup();
	int avr_uart;
	int tmp;
	//char buf[1000];	
	pinMode(26, OUTPUT);
	digitalWrite(26, 0);
	setup_stdin();
	avr_uart=init();
	if(avr_uart == -1) 
	return -1;
//todo make sure avr_uart is ok
	digitalWrite(26, 1);


	if(fork()){ 

		from_to(avr_uart,1);//0 is stdin
	}
	else {
		from_to(0,avr_uart);//0 is stdin
	}
	//todo sure would be nice to have an exit condition
	 return 1;

 }



 void setup_stdin(void)
 { 
	struct termios tc;
	tcgetattr(0, &tc);
	tc.c_lflag &=~ICANON ;
	tc.c_lflag |=ECHO;
	tcsetattr(0, TCSANOW, &tc);
}


void from_to(int f1, int f2)
{  
	char c;
	while(1){ 

		if(read(f1,&c,1)){
			write(f2,&c,1); 
		}
	}
}




int init(void)
{
	int fd;
	struct termios tc;	             // terminal control structure

	//todo serial port should not be hard coded
	fd = open("/dev/ttyS0", O_RDWR|O_NOCTTY);  // really ought to check for error
	if(!fd) {
		printf("ttyS0 failed to open\n");
		return -1;
	}
	tcgetattr(fd, &tc);
	tc.c_iflag = IGNPAR; //ignores parity errors and sets two stop bits
	tc.c_oflag = 0;
	tc.c_cflag = CS8 | CREAD | CLOCAL | CSTOPB; //8 bit chars enable receiver no modem status lines
	tc.c_lflag =0 ;

	//todo baud rate should not be hard coded
	cfsetispeed(&tc, B1200);
	cfsetospeed(&tc, B1200);
	//todo should have bits per character set
	tcsetattr(fd, TCSANOW, &tc);
	return fd;
}

