// LCD03-162 example c code for the Raspberry pi
//
// Displays text on the LCD03 screen.
//
// By James Henderson, 2012.

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
	printf("**** LCD03-162 test program ****\n");
	
	int fd;														// File descrition
	char *fileName = "/dev/i2c-0";								// Name of the port we will be using
	int  address = 0x63;										// Address of LCD03 shifted right one bit
	char buf[10];										
	
	if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	
	if (ioctl(fd, I2C_SLAVE, address) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}
	
	buf[0] = 0;													// Commands to clear the screen
	buf[1] = 12;
	
	if ((write(fd, buf, 2)) != 2) {								// clear the screen
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	printf("Sending text to LCD03\n");
	
	// textString1 will be the top line of text, the leading space is sent to the LCD03
	// because text must be sent to the command register (0), however if a non zero is recieved
	// first anything after that point is displayed on the screen. The leading space
	// ensures all text will be displayed.
	char textString1[21] = " ********************";					
	if ((write(fd, textString1, 21)) != 21) {					
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	char textString2[21] = " *  LCD03 test for  *";
	if ((write(fd, textString2, 21)) != 21) {					
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	char textString3[21] = " *   raspberry pi   *";
	if ((write(fd, textString3, 21)) != 21) {					
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	char textString4[21] = " ********************";
	if ((write(fd, textString4, 21)) != 21) {					
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	return 0;
}
