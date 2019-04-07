int main(int argc, char* argv[])
{
	wiringPiSetup();
	int fd;
	pinMode(26, OUTPUT);
	setup_stdin();
	fd = init();
	if(fd == -1)
		return -1;

	digitalWrite(26,1);
	
	if(fork()) {
		from_to(fd,1);
	}
	else {
		from_to(0, fd);
	}
	
	return 1;
}

void setup_stdin(void)
{
	struct termios tc;
	tcgetattr(0,&tc);
	tc.c_lflag &= ~ICANON;
	tc.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &tc);
}

void from_to(int f1, int f2)
{
	char c;
	while(1) {
		if(read(f1, &c, 1)) {
			write(f2, &c, 1);
		}
	}
}

int init(void)
{
	int fd1;
	struct termios tc;
	
	fd1 = open("/dev/ttyS0", O_RDWR|O_NOCTTY);
	if(!fd1) {
		printf("ttyS0 failed to open\n");
		return -1;
	}
	tcgetattr(fd1, &tc);
	tc.c_iflag = IGNPAR;
	tc.c_oflag = 0;
	tc.c_cflag = CS8 | CREAD | CLOCAL | CSTOPB;

	cfsetispeed(&tc, B1200);
	cfsetospeed(&tc, B1200);

	tcsetattr(fd1, TCSANOW, &tc);
	return fd1;
}

void coolStuff(void)
{
	float max;
	int adc;
	printf("Enter a max power supply voltage");
	scanf("%d", max);
	
	adc = (1.1*1024) / max;
	
	
