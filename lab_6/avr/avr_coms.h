/*

Serial Communications Routines for AVR side
of ece477 lab 6 using lab specifications

Authors: Zach Haviland
	Steph _LASTNAME_


*/

#include<stdint>

//Sets up stdin and stdout for the AVR as well as serial parameters
void serial_init(void);
uint8_t  serial_read(void);
void  serial_write(void);

