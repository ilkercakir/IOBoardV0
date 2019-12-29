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

controller* controller_open(controller_type type, unsigned char databits)
{
	controller *c;
	actuator *a;
	int i, err;

	c = malloc(sizeof(controller));

	c->type = type;
	c->actuators = NULL;
	switch (type)
	{
		case V0:
			c->ochannels = 8; // Q outputs of 74373
			c->aindex = 0;
			c->channel_pins_used = 0;

			c->obits = 2; // Q outputs of 7474
			c->bindex = c->ochannels;

			c->opulses = 2; // 6th and 7th output pins of 74138
			c->pindex = c->ochannels + c->obits;

			c->databits = databits;

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

			if( (err=pthread_mutex_init(&(c->omutex), NULL))!=0 )
			{
				//printf("omutex init failed, %d\n", ret);
				err = CONTROLLER_MUTEX_FAILED;
				break;
			}
		
			err = init_state(c->databits);
			//printf("init_state(%d) = %d\n", c->databits, ret);
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
	pthread_mutex_destroy(&(c->omutex));
	free(c);
}

unsigned char controller_get_value(controller *c)
{
	actuator *a = c->actuators;
	int i,j;

	for(i=0,j=0,c->databits=0x00;a[i].type!=A_VOID && i<c->ochannels;i++)
	{
		switch (a[i].type)
		{
			case A_LEVEL:
				c->databits = c->databits << a[i].pins_used;
				c->databits |= a[i].value;
				break;
			case A_SWITCH:
			case A_PULSE:
			default:
				c->databits = c->databits << 1;
				c->databits |= a[i].value;
				break;
		}
		j+=a[i].pins_used;
		//printf("channel %d, value %x, databits %x\n", i, a[i].value, c->databits);
	}
	c->databits = c->databits << (c->ochannels-j);

	return(c->databits);
}

int ochannel_add(controller *c, char *name, actuator_type type, int numstates)
{
	actuator *a = c->actuators;
	int pins_used, err;

	pthread_mutex_lock(&(c->omutex));
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
	else if (c->channel_pins_used + pins_used > c->ochannels)
	{
		err = CONTROLLER_FULL;
	}
	else
	{
		strcpy(a[c->aindex].name, name);
		a[c->aindex].type = type;
		a[c->aindex].numstates = numstates;
		a[c->aindex].base_pin = c->channel_pins_used;
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

		c->channel_pins_used+=pins_used;
		c->aindex++;

		controller_get_value(c); // updates c->databits;

		err = c->aindex-1;
	}
	pthread_mutex_unlock(&(c->omutex));

	return(err);
}

int obit_add(controller *c, char *name)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->omutex));
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
	pthread_mutex_unlock(&(c->omutex));

	return(err);
}

int opulse_add(controller *c, char *name)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->omutex));
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
	pthread_mutex_unlock(&(c->omutex));

	return(err);
}

unsigned char ochannel_get_value(controller *c, unsigned int channel)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->omutex));
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
	pthread_mutex_unlock(&(c->omutex));

	return(err);
}

void ochannel_set_value(controller *c, unsigned int channel, unsigned char value)
{
	actuator *a = c->actuators;
	unsigned char valuemask;

	pthread_mutex_lock(&(c->omutex));
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
	pthread_mutex_unlock(&(c->omutex));
}

void ochannel_write(controller *c)
{
	pthread_mutex_lock(&(c->omutex));
	write_data(controller_get_value(c));
	pthread_mutex_unlock(&(c->omutex));
}

unsigned char obit_get_value(controller *c, unsigned int bit)
{
	actuator *a = c->actuators;
	int err;

	pthread_mutex_lock(&(c->omutex));
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
	pthread_mutex_unlock(&(c->omutex));

	return(err);
}

void obit_set_value(controller *c, unsigned int bit, unsigned char value)
{
	actuator *a = c->actuators;

	pthread_mutex_lock(&(c->omutex));
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
	pthread_mutex_unlock(&(c->omutex));
}

void opulse_out(controller *c, unsigned int pulse, unsigned int usecs)
{
	actuator *a = c->actuators;

	pthread_mutex_lock(&(c->omutex));
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
	pthread_mutex_unlock(&(c->omutex));
}
