/*
 * SRF01.c
 * 
 * SRF01 example code for raspberry pi.
 * Displays the SRF01 software version to st screen and performs a ranging
 * 
 * By James Henderson, 2012
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

void writeBytes(int descriptor, int count);
void readBytes(int descriptor, int count);
void displaySoftwareValue(int fd);
int getRangeCM(int fd);

char serialBuffer[10];									// Serial buffer sto store data for I/O

int main(int argc, char **argv)
{
	int fd;												// File descriptor of port we will talk to 
	char *portName = "/dev/ttyAMA0";					// Name of the UART port on the Raspberry pi
	struct termios options;								// Port options
	
	fd = open(portName, O_RDWR | O_NOCTTY);				// Open port for read and write not making it a controlling terminal
	if (fd == -1)
	{
		perror("openPort: Unable to open port ");		// If open() returns an error
	} 
	tcgetattr(fd, &options);
	cfsetispeed(&options, B9600);						// Set baud rate
	cfsetospeed(&options, B9600);
						
	cfmakeraw(&options);
	
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);
	
	usleep(10000);										// Sleep for UART to power up and set options
	
	displaySoftwareValue(fd);							// Display the software version of the SRF01
	
	int range = getRangeCM(fd);
	printf("Range in CM = %i\n", range);
	fflush(stdout);
	
	close(fd);											// Close port
	
	return 0;
}

void writeBytes(int descriptor, int count) {
	tcsendbreak(descriptor, 1);										// send break
	if ((write(descriptor, serialBuffer, count)) == -1) {			// Send data out	
		perror("Error writing");
		close(descriptor);											// Close port if there is an error
		exit(1);
	}
}

void readBytes(int descriptor, int count) {
	tcflush(descriptor, TCIFLUSH);									// As serial port RX will pick up what we send out of TX and store it in a buffer we flush this data befpre reading
	if (read(descriptor, serialBuffer, count) == -1) {				// Read back data into buf[]
		perror("Error reading ");
		close(descriptor);											// Close port if there is an error
		exit(1);
	}
}

void displaySoftwareValue(int fd) {

	serialBuffer[0] = 0x01;											//SRF01 address
	serialBuffer[1] = 0x5D;
	
	
	writeBytes(fd, 2);
	readBytes(fd, 1);
	
	printf("SRTF01 Software v: %d \n",serialBuffer[0]);				// display the software version
	
}

int getRangeCM(int fd) {
	
	serialBuffer[0] = 1;
	serialBuffer[1] = 0x54;
	
	writeBytes(fd, 2);
	usleep(7000);
	readBytes(fd, 2);
	
	int range = serialBuffer[1];
	range |= (serialBuffer[0] << 8);
	
	return range;

}
	
