#include "gpio.h"

/*
 * GPIO Pins:
 * 138.A0  - BCM17 WiringPi0
 * 138.A1  - BCM18 WiringPi1
 * 138.A2  - BCM27 WiringPi2
 * 138.E3  - BCM22 WiringPi3
 * 164.A   - BCM23 WiringPi4
 * 74(1).D - BCM23 WiringPi4
 * 74(2).D - BCM23 WiringPi4
 * 165.Q7  - BCM24 WiringPi5
 * 
 * 138.{A2,A1,A0}
 * 0,0,0 164.CLK - Serial Out
 * 0,0,1 373.EN - Parallel Write
 * 0,1,0 165.CP - Serial In
 * 0,1,1 165.PL - Parallel Load
 * 1,0,0 74(1).CLK - Write bit 1
 * 1,0,1 74(2).CLK - Write bit 2
 * 1,1,0 138.O6 - Pulse 1
 * 1,1,1 138.O7 - Pulse 2
 */

void set_address(unsigned int addr)
{
	digitalWrite(0, addr&0x01); // 138.A0
	digitalWrite(1, addr&0x02); // 138.A1
	digitalWrite(2, addr&0x04); // 138.A2
}

void clock_pulse(int duration)
{
	usleep(duration);
	digitalWrite(3, 0); // 138.E3 = 1
	usleep(duration);
	digitalWrite(3, 1); // 138.E3 = 0
}

void output_data_bit(unsigned char databit)
{
	digitalWrite(4, databit); // 164.A = !databit
}

void write_data(unsigned char c)
{
	int i;

	set_address(0); // Serial Out mode
	for(i=0;i<8;c=c<<1,i++)
	{
		output_data_bit(c&0x80); // Highest bit
		clock_pulse(USECS);
	}

	set_address(1); // Write mode
	clock_pulse(USECS);
}

void write_bit(unsigned char addr, unsigned char c)
{
	set_address(addr); // Data Bit Out mode
	output_data_bit(c); // !c
	clock_pulse(USECS);
}

void write_pulse(unsigned char addr, unsigned int usecs)
{
	set_address(addr); // Pulse Out mode
	clock_pulse(usecs);
}

int init_state(unsigned char databits)
{
	if (wiringPiSetup() == -1)
		return GPIO_ERROR;

	// Preset clock HIGH
	digitalWrite(3, 1); // 138.E3 = 0
	pinMode(3, OUTPUT); // aka BCM_GPIO pin 22 // 138.E3

	pinMode(0, OUTPUT); // aka BCM_GPIO pin 17 // 138.A0
	pinMode(1, OUTPUT); // aka BCM_GPIO pin 18 // 138.A1
	pinMode(2, OUTPUT); // aka BCM_GPIO pin 27 // 138.A2
	pinMode(4, OUTPUT); // aka BCM_GPIO pin 23 // 164.A, 74(1).D, 74(2).D
	//pinMode(5, INPUT);  // aka BCM_GPIO pin 24 // 165.Q7

	write_data(databits);

	return GPIO_SUCCESS;
}
