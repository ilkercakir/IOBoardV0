#ifndef gpioH
#define gpioH

#include <wiringPi.h>
#include <unistd.h>

#define GPIO_SUCCESS 0
#define GPIO_ERROR -1

#define USECS 1000 // clock half pulse width

void set_address(unsigned int addr);
void clock_pulse(int duration);
void output_data_bit(unsigned char databit);
void write_data(unsigned char c);
void write_bit(unsigned char addr, unsigned char c);
void write_pulse(unsigned char addr, unsigned int usecs);
unsigned char read_data();
int init_state(unsigned char databits);

#endif
