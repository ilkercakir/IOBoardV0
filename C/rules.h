#ifndef rulesH
#define rulesH

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "iochannels.h"
#include "db.h"
#include "httpget.h"

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
}ruleinterval;

typedef struct
{
 int intervalcount;
 ruleinterval *intervals;
 controller *c;
}rulescheduler;

void init_rule_scheduler(rulescheduler *s, controller *c);
void close_rule_scheduler(rulescheduler *s);
#endif
