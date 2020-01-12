#ifndef rulesH
#define rulesH

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "iochannels.h"
#include "db.h"

typedef struct
{
  int chnnl;
  int devid;
  int fromval;
  int toval;
}sdev;

typedef struct
{
  int chnnl;
  int devid;
  int value;
}adev;

typedef struct
{
  int rulid;
  int sgrid;
  int agrid;
  int sdevcount;
  sdev *sdevs;
  int adevcount;
  adev *adevs;
}rule;

typedef struct
{
  int intid;
  int seconds;
  controller *c;
  int rulecount;
  rule *rules;
  pthread_t tid;
  int retval;
  int threadrunning;
}interval;

typedef struct
{
 int intervalcount;
 interval *intervals;
 controller *c;
}scheduler;

void init_scheduler(scheduler *s, controller *c);
void close_scheduler(scheduler *s);
#endif
