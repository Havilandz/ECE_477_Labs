/*
 * Program name: Hello ECE477
 * Authors: Zach Haviland, Hunter Gross, Stephanie Pourier
 *
 * This program prints the string "Hello World" a number of times
 * equal to the size of a supplied native data type in bytes. 
 *
 * Supported data types are: int, double, float, long int (long) , short int (short) and char. 
 * Long int and short in must be entered as "long" and "short" respecively.
 * The program uses strtol to convert an input string into a numeric key in
 * base 32 that is compared against a list to find the correct output.
 * A limitation of the current method of using definitons to compare against
 * is that this program likely will not work on computers that do not use 
 * the ascii character table as their default character table. However the
 * implemented method is less function call intensive.  
 */
#include<stdio.h>
#include<stdlib.h>

//Numerial keys used for comparison with command line input
#define INT 19197
#define DOUBLE 462368430
#define FLOAT 16441693
#define LONG 713456
#define SHORT 29942653
#define CHAR 410971

//Prints the string "Hello World!" a number of times equal to num.
void printHello(int num);

int main(int argc, char **argv)
{
	if((argc == 1) | (argc > 2)){
		printf("Printing \"Hello World!\" a number of times equal to the number of bytes in an int\n");
		printHello(sizeof(int));
		printf("Printing \"Hello World!\"  a number of times equal to the number of bytes in a double:\n");
		printHello(sizeof(double));
		return 0;
	}
	//strtol converts to a base 32 integer because there is a uniquie output for each data type supported when parsed by it	
	switch(strtol(argv[1],NULL,32)){
	case INT:
		printf("Printing \"Hello World!\" a number of times equal to the number of bytes in an int:\n");
		printHello(sizeof(int));
		break;	
	case DOUBLE:
		printf("Printing \"Hello World!\" a number of times equal to the number of bytes in a double:\n");
		printHello(sizeof(double));
		break;
	case FLOAT:
		printf("Printing \"Hello World!\" a number of times equal to the number of bytes in a float:\n");
		printHello(sizeof(float));
		break;
	case LONG:
		printf("Printing \"Hello World!\" a number of times equal to the number of bytes in a long int:\n");
		printHello(sizeof(long int));
		break;
	case SHORT:
		printf("Printing \"Hello World!\" a number of times equal to the number of bytes in a short int:\n");
		printHello(sizeof(short int));
		break;
	case CHAR:	
		printf("Printing \"Hello World!\" a number of times equal to the number of bytes in a char:\n");
		printHello(sizeof(char));
		break;
	default:
		printf("Unsupported data type\n");
		break;

	}

	return 0;
}


//Prints the string "Hello World!" a number of times equal to num.
void printHello(int num)
{
	int i = 0;
	for(i = 0;i<num;i++)
		printf("Hello World!\n");
}



