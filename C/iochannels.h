#ifndef iochannelsH
#define iochannelsH

#include <pthread.h>
#include "gpio.h"

#define CONTROLLER_SUCCESS 0
#define CONTROLLER_UNKNOWN -2
#define CONTROLLER_FULL -3
#define CONTROLLER_INVALID_ACTUATOR -4
#define CONTROLLER_INVALID_STATES -5
#define CONTROLLER_MUTEX_FAILED -6

typedef enum { V0 } controller_type;

typedef enum { A_VOID, A_SWITCH, A_LEVEL, A_PULSE } actuator_type; // Must be inline with database table IOBoard.devicetypes
typedef enum { S_VOID = 4, S_SWITCH, S_LEVEL } sensor_type; // Must be inline with database table IOBoard.devicetypes

typedef enum { SWITCH_OFF, SWITCH_ON } switch_values;
typedef enum { PULSE_LOW, PULSE_HIGH } pulse_values;

typedef struct actuatorsensorcontroller controller; // forward

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

typedef struct
{
	controller *parent;
	char name[50];
	sensor_type type;
	unsigned int numstates;
	unsigned int base_pin;
	unsigned int pins_used;
	unsigned int channel;
	unsigned char value;
} sensor;

struct actuatorsensorcontroller
{
	int err;
	controller_type type;
	unsigned int ochannels; // max output channels
	unsigned int obits; // max output bits
	unsigned int opulses; // max output pulses
	actuator *actuators;
	unsigned int aindex;
	unsigned int ochannel_pins_used;
	unsigned int bindex;
	unsigned int pindex;
	unsigned char odatabits;

	unsigned int ichannels; // max input channels
	sensor *sensors;
	unsigned int sindex;
	unsigned int ichannel_pins_used;
	unsigned char idatabits;
	
	pthread_mutex_t iomutex;
};

controller* controller_open(controller_type type, unsigned char databits, int usegpio);
void controller_close(controller *c);
int ochannel_add(controller *c, char *name, actuator_type type, int numstates);
int obit_add(controller *c, char *name);
int opulse_add(controller *c, char *name);
unsigned char ochannel_get_value(controller *c, unsigned int channel);
void ochannel_set_value(controller *c, unsigned int channel, unsigned char value);
unsigned char controller_get_ovalue(controller *c);
void ochannel_write(controller *c);
unsigned char obit_get_value(controller *c, unsigned int bit);
void obit_set_value(controller *c, unsigned int bit, unsigned char value);
unsigned char opulse_get_value(controller *c, unsigned int pulse);
void opulse_set_value(controller *c, unsigned int pulse, unsigned char value);
void opulse_out(controller *c, unsigned int pulse, unsigned int usecs);
void controller_set_ivalue(controller *c, unsigned char value);
int ichannel_add(controller *c, char *name, sensor_type type, int numstates);
unsigned char ichannel_get_value(controller *c, unsigned int channel);
unsigned char ichannel_read(controller *c);
#endif
