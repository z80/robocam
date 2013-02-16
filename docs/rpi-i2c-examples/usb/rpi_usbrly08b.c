/*****************************************************
USBRLY08b test application for linux.

This code communicates with the USBRLY08b by first 
opening a port to comunicate with the device using fopen().
Data can then be written to the device using fwrite()
and fflush() or read using fread(). Once finished it
then closes the open port using fclose().

By James Henderson, 2012

*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

void displayData(void);								// Displays module id and software version
void displayHelp(void);								// Displays help data
int getStates(void);

char sbuf[2];									// char array that stores data to be written
int fd;
char bin[10];

int main(int argc, char *argv[])
{

	printf("*************************************\n");
	printf("USBRLY08b linux test application\n");
	printf("By James Henderson, 2012\n");	
	printf("*************************************\n\n");

	if(argc < 2)								// check for correct aruguments passed
	{
		displayHelp();
	}
	else if(argc > 3)
	{
		displayHelp();
	}
	else
	{
	int i; 
		for(i = 1; i < argc; i++)
		{
			if(strcmp(argv[i], "-h") == 0)
			{
				displayHelp();
			}
			else
			{
				struct termios defaults;							// to store innitial default port settings
				struct termios config;								// These will be our new settings
				const char *device = "/dev/ttyACM0";
				fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
				if(fd == -1) {
  					printf( "failed to open port\n" );
				} else {
					if (tcgetattr(fd, &defaults) < 0) perror("tcgetattr");  		// Grab  settings  for port
					cfmakeraw(&config);							// make options for raw data
					if (tcsetattr(fd, TCSANOW, &config) < 0) perror("tcsetattr config");   	// Set options for port
					
					displayData();
					int states;
					sprintf(bin,"%s",argv[1]);		// Store the input binary in bin[] as a char 
					states = getStates();			// Calculate the states of the relays
					sbuf[0] = 0x5C;				// Set relays
					sbuf[1] = states;
					if (write(fd, sbuf, 2) < 0) perror("write");	// Write data to USBRLY08b
					if (tcdrain(fd) < 0) perror("tcdrain");
					
					if (tcsetattr(fd, TCSANOW, &defaults) < 0) perror("tcsetattr default");	// Restore port default before closing
				}				
				close(fd);					// Close the file we opened
			}
		}
	}	

	return(0);

}

void displayData(void)
{
char ver, id;
	sbuf[0] = 0x5A;							// Send byte to return software version and module id
	if (write(fd, sbuf, 1) < 0) perror("displayData write");	// Write data to USBRLY08b
	if (tcdrain(fd) < 0) perror("displayData tcdrain");
	if (read(fd, sbuf, 2) < 0) perror("displayData read");		// Read data back from USBRLY08b
	id = sbuf[0];
	ver = sbuf[1];
	printf("Module id: %u \n", id);
	printf("Module software version: %u \n", ver);
}


void displayHelp(void)
{
		printf("Usage: usbrly08b -[option] RELAYSTATE\n");
		printf("OPTIONS\n");
		printf("	-h : this screen\n");
		printf("RELAYSTATE\n");
		printf("	An 8 bit binary value used to select states of relays\n");
		printf("	0 turning a relay off and 1 turning it on.\n");
}

int getStates(void)
{
int sum, x, i, b;

	sum = 0;						// will hold the value of the binary number input
	
	b = 7;
	/*
	Create the binary value input from a character array by looking
	at each element and shifting a 1 or 0 into place in a char.
	*/
	for(i = 0; i < 8; i++)
	{
		x = 0;						// Clear x before we put anything into it

		if(bin[i] == '1')
		{
			x = 0x01 << b;
		}
		else if(bin[i] == '0')
		{
			x = 0x00 << b;
		}
		else
		{
			printf("Invalid input.\n\n");		// If neither a 1 or 0 is found display and error and return 1
			displayHelp();
			return -1;
		}

		b--;						// Will shift value by 1 less place next loop round

		sum += x;
	}
	return(sum);
}
