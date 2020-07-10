#ifndef statesH
#define statesH

typedef struct
{
  int staid;
  int sgrid;
  int sdevcount;
  sdev *sdevs;
  int oldvalue;
  int value;
}state;

typedef struct
{
  int staidfrom;
  int staidto;
  int agrid;
  int adevcount;
  adev *adevs;
}transition;

typedef struct
{
  int intid;
  int seconds;
  controller *c;
  int statecount;
  state *states;
  pthread_t tid;
  int retval;
  int threadrunning;
}stateinterval;

typedef struct
{
 int intervalcount;
 stateinterval *intervals;
 controller *c;
}statescheduler;
#endif
