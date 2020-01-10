#ifndef rulesH
#define rulesH

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
  sdev *sdevs;
  adev *adevs;
}rule;

typedef struct
{
  int intid;
  int seconds;
  rule *rules;
}interval;

typedef struct
{
 interval *intervals;
}scheduler;

#endif
