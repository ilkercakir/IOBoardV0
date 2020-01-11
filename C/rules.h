#ifndef rulesH
#define rulesH

#define DBPATH "/var/sqlite3DATA/IOBoard.db"

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
  int rulecount;
  rule *rules;
}interval;

typedef struct
{
 int intervalcount;
 interval *intervals;
}scheduler;

void init_scheduler(scheduler *s);
void close_scheduler(scheduler *s);
#endif
