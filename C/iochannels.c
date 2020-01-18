/*
 * iochannels.c
 * 
 * Copyright 2019  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <string.h>
#include <math.h>
#include <malloc.h>

#include "iochannels.h"

// Controller interface

controller* controller_open(controller_type type, unsigned char databits, int usegpio)
{
	controller *c;
	actuator *a;
	sensor *s;
	int i, err = CONTROLLER_SUCCESS;

	c = malloc(sizeof(controller));

	c->type = type;
	c->actuators = NULL;
	switch (type)
	{
		case V0:
			c->ochannels = 8; // Q outputs of 74373
			c->aindex = 0;
			c->ochannel_pins_used = 0;

			c->obits = 2; // Q outputs of 7474
			c->bindex = c->ochannels;

			c->opulses = 2; // 6th and 7th output pins of 74138
			c->pindex = c->ochannels + c->obits;

			c->odatabits = databits;

			c->actuators = malloc((c->ochannels + c->obits + c->opulses)*sizeof(actuator));
			for(i=c->aindex;i<c->ochannels;i++)
			{
				a = &(c->actuators[i]);
				a->parent = c;
				strcpy(a->name, "");
				a->type = A_VOID;
				a->numstates = 0;
				a->channel = i;
				a->base_pin = 0;
				a->pins_used = 0;
			}

			for(i=c->bindex;i<c->ochannels+c->obits;i++)
			{
				a = &(c->actuators[i]);
				a->parent = c;
				strcpy(a->name, "");
				a->type = A_VOID;
				a->numstates = 0;
				a->channel = i;
				a->base_pin = 0;
				a->pins_used = 0;
			}

			for(i=c->pindex;i<c->ochannels+c->obits+c->opulses;i++)
			{
				a = &(c->actuators[i]);
				a->parent = c;
				strcpy(a->name, "");
				a->type = A_VOID;
				a->numstates = 0;
				a->channel = i;
				a->base_pin = 0;
				a->pins_used = 0;
			}

			c->ichannels = 8; // Q outputs of 74165
			c->sindex = 0;
			c->ichannel_pins_used = 0;
			c->sensors = malloc(c->ichannels*sizeof(sensor));
			for(i=c->sindex;i<c->ichannels;i++)
			{
				s = &(c->sensors[i]);
				s->parent = c;
				strcpy(s->name, "");
				s->type = S_VOID;
				s->numstates = 0;
				s->channel = i;
				s->base_pin = 0;
				s->pins_used = 0;
			}

			if( (err=pthread_mutex_init(&(c->iomutex), NULL))!=0 )
			{
				//printf("iomutex init failed, %d\n", ret);
				err = CONTROLLER_MUTEX_FAILED;
				break;
			}

			if (usegpio)
				err = init_state(c->odatabits);
			//printf("init_state(%d) = %d\n", c->odatabits, ret);
			break;
		default:
			err = CONTROLLER_UNKNOWN;
			break;
	}

	c->err = err;

	return(c);
}

void controller_close(controller *c)
{
	if (c->actuators)
		free(c->actuators);
	if (c->sensors)
		free(c->sensors);
	pthread_mutex_destroy(&(c->iomutex));
	free(c);
}

// Actuator interface

unsigned char controller_get_ovalue(controller *c)
{
	actuator *a = c->actuators;
	int i,j;

	for(i=0,j=0,c->odatabits=0x00;i<c->ochannels;i++)
	{
		if (a[i].type==A_VOID)
			break;
		switch (a[i].type)
		{
			case A_LEVEL:
				c->odatabits = c->odatabits << a[i].pins_used;
				c->odatabits |= a[i].value;
				break;
			case A_SWITCH:
			case A_PULSE:
			default:
				c->odatabits = c->odatabits << 1;
				c->odatabits |= a[i].value;
				break;
		}
		j+=a[i].pins_used;
		//printf("channel %d, value %x, databits %x\n", i, a[i].value, c->odatabits);
	}
	c->odatabits = c->odatabits << (c->ochannels-j);

	return(c->odatabits);
}

int ochannel_add(controller *c, char *name, actuator_type type, int numstates)
{
	actuator *a = c->actuators;
	int pins_used, err;

	pthread_mutex_lock(&(c->iomutex));
	switch (type)
	{
		case A_LEVEL:
			if (!numstates) return(CONTROLLER_INVALID_STATES);
			pins_used = ceil(log(numstates) / log(2)); // s = 2**n; n = ceil(ln(s)/ln(2))
			break;
		case A_SWITCH:
		case A_PULSE:
			pins_used = 1;
			break;
		case A_VOID:
		default:
			pins_used = 0;
			break;
	}

	if (type == A_VOID)
	{
		err = CONTROLLER_INVALID_ACTUATOR;
	}
	else if (c->ochannel_pins_used + pins_used > c->ochannels)
	{
		err = CONTROLLER_FULL;
	}
	else
	{
		strcpy(a[c->aindex].name, name);
		a[c->aindex].type = type;
		a[c->aindex].numstates = numstates;
		a[c->aindex].base_pin = c->ochannel_pins_used;
		a[c->aindex].pins_used = pins_used;
		a[c->aindex].channel = c->aindex;
		switch (type)
		{
			case A_LEVEL:
				a[c->aindex].value = 0; // Default value
				break;
			case A_SWITCH:
			case A_PULSE:
			default:
				a[c->aindex].value = SWITCH_OFF; // Default value
				break;
		}

		c->ochannel_pins_used+=pins_used;
		c->aindex++;

		controller_get_ovalue(c); // updates c->odatabits;

		err = c->aindex-1;
	}
	pthread_mutex_unlock(&(c->iomutex));

	return(err);
}

int obit_add(controller *c, char *name)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->iomutex));
	if (c->bindex >= c->ochannels + c->obits)
	{
		err = CONTROLLER_FULL;
	}
	else
	{
		strcpy(a[c->bindex].name, name);
		a[c->bindex].type = A_SWITCH;
		a[c->bindex].numstates = 2;
		a[c->bindex].base_pin = c->bindex - c->ochannels + 4;
		a[c->bindex].pins_used = 1;
		a[c->bindex].channel = c->bindex;
		a[c->bindex].value = SWITCH_OFF; // Default value
		c->bindex++;
		err = c->bindex-1;
	}
	pthread_mutex_unlock(&(c->iomutex));

	return(err);
}

int opulse_add(controller *c, char *name)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->iomutex));
	if (c->pindex >= c->ochannels + c->obits + c->opulses)
	{
		err = CONTROLLER_FULL;
	}
	else
	{
		strcpy(a[c->pindex].name, name);
		a[c->pindex].type = A_PULSE;
		a[c->pindex].numstates = 2;
		a[c->pindex].base_pin = c->pindex - c->ochannels - c->opulses + 6;
		a[c->pindex].pins_used = 1;
		a[c->pindex].channel = c->pindex;
		c->pindex++;
		err = c->pindex-1;
	}
	pthread_mutex_unlock(&(c->iomutex));

	return(err);
}

unsigned char ochannel_get_value(controller *c, unsigned int channel)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->iomutex));
	if (!c->aindex) // no channels added
	{
		err = 0;
	}
	else if (channel >= c->aindex) // channel outside bounds
	{
		err = 0;
	}
	else
	{
		err = a[channel].value;
	}
	pthread_mutex_unlock(&(c->iomutex));

	return(err);
}

void ochannel_set_value(controller *c, unsigned int channel, unsigned char value)
{
	actuator *a = c->actuators;
	unsigned char valuemask;

	pthread_mutex_lock(&(c->iomutex));
	if (!c->aindex) // no channels added
	{
	}
	else if (channel >= c->aindex) // channel outside bounds
	{
	}
	else
	{
		switch (a[channel].type)
		{
			case A_LEVEL:
				valuemask = pow(2, a[channel].pins_used) - 1;
				value &= valuemask;
				break;
			case A_SWITCH:
			case A_PULSE:
			default:
				if (value)
					value = 0x01;
				else
					value = 0x00;
				break;
		}
		a[channel].value = value;
	}
	pthread_mutex_unlock(&(c->iomutex));
}

void ochannel_write(controller *c)
{
	pthread_mutex_lock(&(c->iomutex));
	write_data(controller_get_ovalue(c));
	pthread_mutex_unlock(&(c->iomutex));
}

unsigned char obit_get_value(controller *c, unsigned int bit)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->iomutex));
	if (c->bindex == c->ochannels) // no bits added
	{
		err = 0;
	}
	else if ((bit < c->ochannels) || (bit >= (c->ochannels + c->obits))) // bit outside bounds
	{
		err = 0;
	}
	else
	{
		err = a[bit].value;
	}
	pthread_mutex_unlock(&(c->iomutex));

	return(err);
}

void obit_set_value(controller *c, unsigned int bit, unsigned char value)
{
	actuator *a = c->actuators;

	pthread_mutex_lock(&(c->iomutex));
	if (c->bindex == c->ochannels) // no bits added
	{
	}
	else if ((bit < c->ochannels) || (bit >= (c->ochannels + c->obits))) // bit outside bounds
	{
	}
	else
	{
		if (value)
			a[bit].value = 0x01;
		else
			a[bit].value = 0x00;

		write_bit(a[bit].base_pin, a[bit].value);
	}
	pthread_mutex_unlock(&(c->iomutex));
}

void opulse_out(controller *c, unsigned int pulse, unsigned int usecs)
{
	actuator *a = c->actuators;

	pthread_mutex_lock(&(c->iomutex));
	if (c->pindex == c->ochannels + c->obits) // no pulses added
	{
	}
	else if ((pulse < c->ochannels + c->obits) || (pulse >= (c->ochannels + c->obits + c->opulses))) // pulse outside bounds
	{
	}
	else
	{
		write_pulse(a[pulse].base_pin, usecs);
	}
	pthread_mutex_unlock(&(c->iomutex));
}


// Sensor interface

void controller_set_ivalue(controller *c, unsigned char value)
{
	sensor *s = c->sensors;
	int i,j;
	unsigned char valuemask;

	c->idatabits = value;

	for(i=0,j=c->ichannels;i<c->ichannels;i++)
	{
		if (s[i].type==S_VOID)
			break;
		j -= s[i].pins_used;
		s[i].value = value;
		s[i].value = s[i].value >> j;
		valuemask = pow(2, s[i].pins_used) - 1;
		s[i].value &= valuemask;

		//printf("channel %d, value %x\n", i, s[i].value);
	}
}

int ichannel_add(controller *c, char *name, sensor_type type, int numstates)
{
	sensor *s = c->sensors;
	int pins_used, err;

	pthread_mutex_lock(&(c->iomutex));
	switch (type)
	{
		case S_LEVEL:
			if (!numstates) return(CONTROLLER_INVALID_STATES);
			pins_used = ceil(log(numstates) / log(2)); // s = 2**n; n = ceil(ln(s)/ln(2))
			break;
		case S_SWITCH:
			pins_used = 1;
			break;
		case S_VOID:
		default:
			pins_used = 0;
			break;
	}

	if (type == S_VOID)
	{
		err = CONTROLLER_INVALID_ACTUATOR;
	}
	else if (c->ichannel_pins_used + pins_used > c->ichannels)
	{
		err = CONTROLLER_FULL;
	}
	else
	{
		strcpy(s[c->sindex].name, name);
		s[c->sindex].type = type;
		s[c->sindex].numstates = numstates;
		s[c->sindex].base_pin = c->ichannel_pins_used;
		s[c->sindex].pins_used = pins_used;
		s[c->sindex].channel = c->sindex;
		switch (type)
		{
			case S_LEVEL:
				s[c->sindex].value = 0; // Default value
				break;
			case S_SWITCH:
			default:
				s[c->sindex].value = SWITCH_OFF; // Default value
				break;
		}

		c->ichannel_pins_used+=pins_used;
		c->sindex++;

		err = c->sindex-1;
	}
	pthread_mutex_unlock(&(c->iomutex));

	return(err);
}

unsigned char ichannel_get_value(controller *c, unsigned int channel)
{
	sensor *s = c->sensors;
	int err;

	pthread_mutex_lock(&(c->iomutex));
	if (!c->sindex) // no channels added
	{
		err = 0;
	}
	else if (channel >= c->sindex) // channel outside bounds
	{
		err = 0;
	}
	else
	{
		err = s[channel].value;
	}
	pthread_mutex_unlock(&(c->iomutex));

	return(err);
}

unsigned char ichannel_read(controller *c)
{
	unsigned char value;

	pthread_mutex_lock(&(c->iomutex));
	value = read_data();
	controller_set_ivalue(c, value);
	pthread_mutex_unlock(&(c->iomutex));

	return(value);
}
