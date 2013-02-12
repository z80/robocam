// CMPS03 example c code for the Raspberry pi
// 
// Reads the bearing from the CMPS03 and displays
// it on the screen.
//
// By James Henderson, 2012


#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("**** CMPS03 test program ****\n");
	
	int fd;														// File descrition
	char *fileName = "/dev/i2c-0";								// Name of the port we will be using
	int  address = 0x60;										// Address of CMPS03 shifted right one bit
	unsigned char buf[10];										// Buffer for data being read/ written on the i2c bus
	
	if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	
	if (ioctl(fd, I2C_SLAVE, address) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}
		
	buf[0] = 0;													// This is the register we want to read from
	
	if ((write(fd, buf, 1)) != 1) {								// Send register we want to read from	
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	if (read(fd, buf, 4) != 4) {								// Read back data into buf[]
		printf("Unable to read from slave\n");
		exit(1);
	}
	else {
		unsigned char highByte = buf[2];
		unsigned char lowByte = buf[3];
		unsigned int result = (highByte <<8) + lowByte;			// Calculate bearing as a word value
		printf("Software v: %u \n",buf[0]);
		printf("Bearing as byte: %u \n",buf[1]);
		printf("Bearing as decimal: %u.%u\n",result/10, result%10); // display bearing with decimal place
	}
	
	return 0;
}

