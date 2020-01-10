#include "rules.h"
#include <sqlite3.h>

void init_rules_of_interval(interval *i)
{
}

int init_intervals_callback(void *data, int argc, char **argv, char **azColName) 
{
  scheduler *s = (scheduler *)data;
  
  s->intervals[s->intervalcount].intid = atoi(argv[0]);
  s->intervals[s->intervalcount].seconds = atoi(argv[2]);  
  init_rules_of_interval(&(s->intervals[s->intervalcount]));

  s->intervalcount++;

  return(0);
}

void init_intervals(scheduler *s)
{
  sqlite3 *db;
  char *err_msg = NULL;
  char *sql = NULL;
  int rc;

  if ((rc = sqlite3_open(DBPATH, &db)))
  {
    printf("Can't open database: %s\n", sqlite3_errmsg(db));
  }
  else
  {
//printf("Opened database successfully\n");
    sql = "select * from intervals;";
    if((rc = sqlite3_exec(db, sql, init_intervals_callback, (void*)s, &err_msg)) != SQLITE_OK)
    {
      printf("Failed to select data, %s\n", err_msg);
      sqlite3_free(err_msg);
    }
    else // success
    {
      
    }
  }
  sqlite3_close(db);
}

int init_scheduler_callback(void *data, int argc, char **argv, char **azColName) 
{
  scheduler *s = (scheduler *)data;
  
  s->intervalcount = atoi(argv[0]);
  s->intervals = malloc(s->count*sizeof(interval));

  s->intervalcount = 0;

  return(0);
}
  
void init_scheduler(scheduler *s)
{
  sqlite3 *db;
  char *err_msg = NULL;
  char *sql = NULL;
  int rc;

  if ((rc = sqlite3_open(DBPATH, &db)))
  {
    printf("Can't open database: %s\n", sqlite3_errmsg(db));
  }
  else
  {
//printf("Opened database successfully\n");
    sql = "select count(*) as schedules from intervals;";
    if ((rc = sqlite3_exec(db, sql, init_scheduler_callback, (void*)s, &err_msg)) != SQLITE_OK)
    {
      printf("Failed to select data, %s\n", err_msg);
      sqlite3_free(err_msg);
    }
    else // success
    {
      
    }
  }
  sqlite3_close(db);
}
