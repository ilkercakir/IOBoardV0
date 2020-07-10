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
}states;

typedef struct
{
  int staidfrom;
  int staidto;
  int agrid;
  int adevcount;
  adev *adevs;
}transitions;

#endif
