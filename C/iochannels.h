#ifndef iochannelsH
#define iochannelsH

#include "gpio.h"

#define CONTROLLER_SUCCESS 0
#define CONTROLLER_UNKNOWN -2
#define CONTROLLER_FULL -3
#define CONTROLLER_INVALID_ACTUATOR -4
#define CONTROLLER_INVALID_STATES -5

typedef enum { V0 } controller_type;

typedef enum { A_VOID, A_SWITCH, A_LEVEL, A_PULSE } actuator_type;

typedef enum { SWITCH_OFF, SWITCH_ON } switch_values;
typedef enum { PULSE_LOW, PULSE_HIGH } pulse_values;

typedef struct actuatorcontroller controller; // forward

typedef struct
{
	controller *parent;
	char name[50];
	actuator_type type;
	unsigned int numstates;
	unsigned int base_pin;
	unsigned int pins_used;
	unsigned int channel;
	unsigned char value;
} actuator;

struct actuatorcontroller
{
	int err;
	controller_type type;
	unsigned int ochannels; // max channels
	unsigned int obits; // max bits
	unsigned int opulses; // max pulses
	actuator *actuators;
	unsigned int aindex;
	unsigned int channel_pins_used;
	unsigned int bindex;
	unsigned int pindex;
	unsigned char databits;
};

void controller_open(controller **c, controller_type type, unsigned char databits);
void controller_close(controller **c);
int ochannel_add(controller *c, char *name, actuator_type type, int numstates);
int obit_add(controller *c, char *name);
int opulse_add(controller *c, char *name);
unsigned char ochannel_get_value(controller *c, unsigned int channel);
void ochannel_set_value(controller *c, unsigned int channel, unsigned char value);
unsigned char controller_get_value(controller *c);
void ochannel_write(controller *c);
unsigned char obit_get_value(controller *c, unsigned int bit);
void obit_set_value(controller *c, unsigned int bit, unsigned char value);
void opulse_out(controller *c, unsigned int pulse);

#endif
