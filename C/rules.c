#include "rules.h"
#include <sqlite3.h>

int init_rules_of_interval_callback(void *data, int argc, char **argv, char **azColName) 
{
  interval *i = (interval *)data;
  
  i->rules[i->rulecount].rulid = atoi(argv[0]);
  i->rules[i->rulecount].sgrid = atoi(argv[1]);
  i->rules[i->rulecount].agrid = atoi(argv[2]);  
  init_count_sensors_of_rule(&(s->intervals[s->intervalcount]));
  init_sensors_of_rule(&(s->intervals[s->intervalcount]));

  s->rulecount++;

  return(0);
}

void init_rules_of_interval(interval *i)
{
  sqlite3 *db;
  char *err_msg = NULL;
  char sql[100];
  int rc;

  if ((rc = sqlite3_open(DBPATH, &db)))
  {
    printf("Can't open database: %s\n", sqlite3_errmsg(db));
  }
  else
  {
//printf("Opened database successfully\n");
    sprintf(sql, "select ruledef.rulid, ruledef.sgrid, ruledef.agrid from rules inner join ruledef on rules.rulid = ruledef.rulid where rules.intid = %d;", i->intid);
    if((rc = sqlite3_exec(db, sql, init_intervals_callback, (void*)i, &err_msg)) != SQLITE_OK)
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

int init_count_rules_of_interval_callback(void *data, int argc, char **argv, char **azColName) 
{
  interval *i = (interval *)data;
  
  i->rulecount = atoi(argv[0]);
  i->rules = malloc(i->rulecount*sizeof(rule));

  i->rulecount = 0;

  return(0);
}

void init_count_rules_of_interval(interval *i)
{
  sqlite3 *db;
  char *err_msg = NULL;
  char sql[100];
  int rc;

  if ((rc = sqlite3_open(DBPATH, &db)))
  {
    printf("Can't open database: %s\n", sqlite3_errmsg(db));
  }
  else
  {
//printf("Opened database successfully\n");
    sprintf(sql, "select count(*) as rulecount from rules where intid = %d;", i->intid);
    if((rc = sqlite3_exec(db, sql, init_intervals_callback, (void*)i, &err_msg)) != SQLITE_OK)
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

int init_intervals_callback(void *data, int argc, char **argv, char **azColName) 
{
  scheduler *s = (scheduler *)data;
  
  s->intervals[s->intervalcount].intid = atoi(argv[0]);
  s->intervals[s->intervalcount].seconds = atoi(argv[2]);  
  init_count_rules_of_interval(&(s->intervals[s->intervalcount]));
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
  s->intervals = malloc(s->intervalcount*sizeof(interval));

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
