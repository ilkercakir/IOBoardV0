#ifndef devicesH
#define devicesH

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"

typedef struct
{
	int devid;
	char dtext[31];
	int chnnl;
	int dtype;
	char dttext[21];
	int numstates;
	int initval;
	int dstat;
	char categ;
	char catxt[21];
	char dicon[21];
	char dticon[21];
}device;

typedef struct
{
	int count;
	device *devices;
}iodevices;

void get_devices(iodevices *d, char categ, int fromChannel, int toChannel);
void free_devices(iodevices *d);
#endif
