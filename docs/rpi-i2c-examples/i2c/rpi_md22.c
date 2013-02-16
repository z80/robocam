// MD22 example c code for Raspberry pi
//
// Drives the motors forward than backward.
//
// By James Henderson,, 2012

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void setAcceleration(void);
void setMotorSpeeds(unsigned char speed);

int fd;														// File descrition
char *fileName = "/dev/i2c-0";								// Name of the port we will be using
int  address = 0x58;										// Address of MD22 shifted right one bit
unsigned char buf[10];										// Buffer for data being read/ written on the i2c bus

int main(int argc, char **argv)
{
	
	printf("**** MD22 test application ****\n");
	
	if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	
	if (ioctl(fd, I2C_SLAVE, address) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}
	
	buf[0] = 7;													// This is the register we wish to read software version from
	
	if ((write(fd, buf, 1)) != 1) {								// Send regiter to read from
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	if (read(fd, buf, 1) != 1) {								// Read back data into buf[]
		printf("Unable to read from slave\n");
		exit(1);
	}
	else {
		printf("Software v: %u \n",buf[0]);
	}
	
	setAcceleration();											// Set acceleration to max this will give us the longest time to reach a set speed
	
	setMotorSpeeds(255);										// speed to full forward
	sleep(5);													// Pause to allow MD22 to reach speed
	setMotorSpeeds(0);											// Full reverse
	sleep(10);
	setMotorSpeeds(128);										// Stop
	sleep(5);
	
	return 0;
}

void setAcceleration(void) {
	
	buf[0] = 3;													// Register to set acceleration
	buf[1] = 255;												// Acceleration value to set
	
	if ((write(fd, buf, 2)) != 2) {	
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
}

void setMotorSpeeds(unsigned char speed) {
	
	buf[0] = 1;													// Register to set speed of motor 1
	buf[1] = speed;
	
	if ((write(fd, buf, 2)) != 2) {
		printf("Error writing to i2c slave\n");
		exit(1);
	}
	
	buf[0] = 2;													// Register to set speed of motor 2
	buf[1] = speed;
	
	if ((write(fd, buf, 2)) != 2) {
		printf("Error writing to i2c slave\n");
		exit(1);
	}
}
