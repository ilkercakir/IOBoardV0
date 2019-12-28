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
	int pins_used;

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
		return (CONTROLLER_INVALID_ACTUATOR);

	if (c->channel_pins_used + pins_used > c->ochannels)
		return (CONTROLLER_FULL);

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

	return(c->aindex-1);
}

int obit_add(controller *c, char *name)
{
	actuator *a = c->actuators;

	if (c->bindex >= c->ochannels + c->obits)
		return (CONTROLLER_FULL);

	strcpy(a[c->bindex].name, name);
	a[c->bindex].type = A_SWITCH;
	a[c->bindex].numstates = 2;
	a[c->bindex].base_pin = c->bindex - c->ochannels + 4;
	a[c->bindex].pins_used = 1;
	a[c->bindex].channel = c->bindex;
	a[c->bindex].value = SWITCH_OFF; // Default value

	c->bindex++;

	return(c->bindex-1);
}

int opulse_add(controller *c, char *name)
{
	actuator *a = c->actuators;

	if (c->pindex >= c->ochannels + c->obits + c->opulses)
		return (CONTROLLER_FULL);

	strcpy(a[c->pindex].name, name);
	a[c->pindex].type = A_PULSE;
	a[c->pindex].numstates = 2;
	a[c->pindex].base_pin = c->pindex - c->ochannels - c->opulses + 6;
	a[c->pindex].pins_used = 1;
	a[c->pindex].channel = c->pindex;

	c->pindex++;

	return(c->pindex-1);
}

unsigned char ochannel_get_value(controller *c, unsigned int channel)
{
	actuator *a = c->actuators;

	if (!c->aindex) // no channels added
		return(0);

	if (channel >= c->aindex) // channel outside bounds
		return(0);

	return(a[channel].value);
}

void ochannel_set_value(controller *c, unsigned int channel, unsigned char value)
{
	actuator *a = c->actuators;
	unsigned char valuemask;

	if (!c->aindex) // no channels added
		return;

	if (channel >= c->aindex) // channel outside bounds
		return;

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

void ochannel_write(controller *c)
{
	write_data(controller_get_value(c));
}

unsigned char obit_get_value(controller *c, unsigned int bit)
{
	actuator *a = c->actuators;

	if (c->bindex == c->ochannels) // no bits added
		return(0);

	if ((bit < c->ochannels) || (bit >= (c->ochannels + c->obits))) // bit outside bounds
		return(0);

	return(a[bit].value);
}

void obit_set_value(controller *c, unsigned int bit, unsigned char value)
{
	actuator *a = c->actuators;

	if (c->bindex == c->ochannels) // no bits added
		return;

	if ((bit < c->ochannels) || (bit >= (c->ochannels + c->obits))) // bit outside bounds
		return;

	if (value)
		a[bit].value = 0x01;
	else
		a[bit].value = 0x00;

	write_bit(a[bit].base_pin, a[bit].value);
}

void opulse_out(controller *c, unsigned int pulse, unsigned int usecs)
{
	actuator *a = c->actuators;

	if (c->pindex == c->ochannels + c->obits) // no pulses added
		return;

	if ((pulse < c->ochannels + c->obits) || (pulse >= (c->ochannels + c->obits + c->opulses))) // pulse outside bounds
		return;

	write_pulse(a[pulse].base_pin, usecs);
}
