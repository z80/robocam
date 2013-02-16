/*
 * MD49.c
 * 
 * MD49 example code for raspberry pi.
 * Runs the motors to an encoder value and back while displaying the encoder values on the screen.
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
void setMode(int fd, char mode);
void driveMotors(int fd, char speed);
void resetEncoders(int fd);
void displayDecoderValues(int fd);

char serialBuffer[10];									// Serial buffer sto store data for I/O
signed int encoder1, encoder2;							// To store the encoder values

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
	
	displaySoftwareValue(fd);							// Display the software version of the MD49
	
	setMode(fd, 1);										// Set the mode of the MD49 to 1
	
	resetEncoders(fd);									// Reset the encode values to 0
	
	do {												// Run motors forward to an encoder value
		driveMotors(fd, 100);
		displayDecoderValues(fd);
	}while(encoder1 < 0x4000);
	
	do {												// Run motors backwards
		driveMotors(fd, -100);
		displayDecoderValues(fd);
	}while(encoder1 > 0);
	
	driveMotors(fd, 0);									// Stop motors before exit
	
	close(fd);											// Close port
	
	return 0;
}

void writeBytes(int descriptor, int count) {
	if ((write(descriptor, serialBuffer, count)) == -1) {							// Send data out	
		perror("Error writing");
		close(descriptor);															// Close port if there is an error
		exit(1);
	}
}

void readBytes(int descriptor, int count) {
	if (read(descriptor, serialBuffer, count) == -1) {								// Read back data into buf[]
		perror("Error reading ");
		close(descriptor);															// Close port if there is an error
		exit(1);
	}
}

void displaySoftwareValue(int fd) {
	serialBuffer[0] = 0;															// Sync byte of 0
	serialBuffer[1] = 0x29;															// Command to get software version
	
	writeBytes(fd, 2);
	readBytes(fd, 1);
	
	printf("MD49 Software v: %d \n",serialBuffer[0]);								// display the software version
	
}

void setMode(int fd, char mode) {
	
	serialBuffer[0] = 0;
	serialBuffer[1] = 0x34;															// Command to set mode
	serialBuffer[2] = mode; 														// Mode we wish to set
	
	writeBytes(fd, 3);
	
}

void driveMotors(int fd, char speed) {
	
	serialBuffer[0] = 0;
	serialBuffer[1] = 0x31;															// Command to set motor speed
	serialBuffer[2] = speed;														// Speed to be set
	
	serialBuffer[3] = 0;
	serialBuffer[4] = 0x32;
	serialBuffer[5] = speed;
	
	writeBytes(fd, 6);
}

void resetEncoders(int fd) {
	
	serialBuffer[0] = 0;
	serialBuffer[1] = 0x35;															// Command to reset encoder values
	
	writeBytes(fd, 2);
}

void displayDecoderValues(int fd) {
	
	serialBuffer[0] = 0;
	serialBuffer[1] = 0x25;															// Command to return encoder values
	
	writeBytes(fd, 2);
	readBytes(fd, 8);
	
	encoder1 = serialBuffer[0] << 24;												// Put together first encoder value
	encoder1 |= (serialBuffer[1] << 16);
	encoder1 |= (serialBuffer[2] << 8);
	encoder1 |= (serialBuffer[3]);
	
	printf("\rencoder 1 : %08X ", encoder1);										// Display it
	
	encoder2 = serialBuffer[4] << 24;												// Second decoder value
	encoder2 |= (serialBuffer[5] << 16);
	encoder2 |= (serialBuffer[6] << 8);
	encoder2 |= (serialBuffer[7]);
	
	printf("encoder 2 : %08X   ", encoder2);
	
	fflush(stdout);																	// Flush output to ensure that data is displayed on the screen
}

