#ifndef statesH
#define statesH

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "iochannels.h"
#include "db.h"
#include "httpget.h"
#include "dev.h"

typedef struct
{
  int staid;
  int sgrid;
  int sdevcount;
  sdev *sdevs;
  int oldvalue;
  int newvalue;
}state;

typedef struct
{
  int traid;
  int staidfrom;
  int staidto;
  int agrid;
  int adevcount;
  adev *adevs;
}statetransition;

typedef struct
{
  int intid;
  int seconds;
  controller *c;
  int statecount;
  state *states;
  int transitioncount;
  statetransition *transitions;
  pthread_t tid;
  int retval;
  int threadrunning;
}stateinterval;

typedef struct
{
 int intervalcount;
 stateinterval *intervals;
 int transitioncount;
 statetransition *transitions;
 controller *c;
}statescheduler;
#endif

void init_state_scheduler(statescheduler *s, controller *c);
void close_state_scheduler(statescheduler *s);
