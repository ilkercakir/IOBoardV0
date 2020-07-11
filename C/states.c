#include "states.h"

int init_actuators_of_transition_callback(void *data, int argc, char **argv, char **azColName) 
{
	statetransition *st = (statetransition *)data;

	st->adevs[st->adevcount].chnnl = atoi(argv[0]);
	st->adevs[st->adevcount].devid = atoi(argv[1]);
	st->adevs[st->adevcount].value = atoi(argv[2]);  
//printf("init_actuators_of_transition_callback %d %d %d %d\n", st->adevs[st->adevcount].value, st->adevs[st->adevcount].devid, st->adevs[st->adevcount].chnnl, st->adevcount);
	st->adevcount++;

	return(0);
}

void init_actuators_of_transition(statetransition *st)
{
	sqlite3 *db;
	char *err_msg = NULL;
	char sql[200];
	int rc;

	if ((rc = sqlite3_open(DBPATH, &db)))
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else
	{
//printf("Opened database successfully\n");
		sprintf(sql, "select devices.chnnl, devices.devid, agdev.value from agdev inner join devices on devices.devid = agdev.devid where agdev.devgr = %d;", st->agrid);
		if((rc = sqlite3_exec(db, sql, init_actuators_of_transition_callback, (void*)st, &err_msg)) != SQLITE_OK)
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

int init_count_actuators_of_transition_callback(void *data, int argc, char **argv, char **azColName) 
{
	statetransition *st = (statetransition *)data;
  
	st->adevcount = atoi(argv[0]);
	st->adevs = malloc(st->adevcount*sizeof(adev));
//printf("init_count_actuators_of_transition_callback %d\n", st->adevcount);
	st->adevcount = 0;

	return(0);
}

void init_count_actuators_of_transition(statetransition *st)
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
		sprintf(sql, "select count(*) as actuatorcount from agdev where devgr = %d;", st->agrid);
		if((rc = sqlite3_exec(db, sql, init_count_actuators_of_transition_callback, (void*)st, &err_msg)) != SQLITE_OK)
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

int init_state_transitions_callback(void *data, int argc, char **argv, char **azColName) 
{
	statescheduler *s = (statescheduler *)data;

	s->transitions[s->transitioncount].traid = atoi(argv[0]);
	s->transitions[s->transitioncount].staidfrom = atoi(argv[1]);
	s->transitions[s->transitioncount].staidto = atoi(argv[2]);
	s->transitions[s->transitioncount].agrid = atoi(argv[3]);
//printf("init_state_transitions_callback %d %d %d %d %d\n", s->transitioncount, s->transitions[s->transitioncount].traid, s->transitions[s->transitioncount].staidfrom, s->transitions[s->transitioncount].staidto, s->transitions[s->transitioncount].agrid);
	init_count_actuators_of_transition(&(s->transitions[s->transitioncount]));
	init_actuators_of_transition(&(s->transitions[s->transitioncount]));

	s->transitioncount++;

	return(0);
}

void init_state_transitions(statescheduler *s)
{
	sqlite3 *db;
	char *err_msg = NULL;
	char sql[200];
	int rc;

	if ((rc = sqlite3_open(DBPATH, &db)))
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else
	{
//printf("Opened database successfully\n");
		sprintf(sql, "select transdef.traid, transdef.staidfrom, transdef.staidto, transdef.agrid from transitions inner join transdef on transitions.traid = transdef.traid;");
		if((rc = sqlite3_exec(db, sql, init_state_transitions_callback, (void*)s, &err_msg)) != SQLITE_OK)
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

int init_count_state_transitions_callback(void *data, int argc, char **argv, char **azColName) 
{
	statescheduler *s = (statescheduler *)data;

	s->transitioncount = atoi(argv[0]);
	s->transitions = malloc(s->transitioncount*sizeof(statetransition));
//printf("init_count_state_intervals_callback %d\n", s->intervalcount);
	s->transitioncount = 0;

	return(0);
}
  
void init_count_state_transitions(statescheduler *s)
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
		sql = "select count(*) as trans from transitions;";
		if ((rc = sqlite3_exec(db, sql, init_count_state_transitions_callback, (void*)s, &err_msg)) != SQLITE_OK)
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

int init_sensors_of_state_callback(void *data, int argc, char **argv, char **azColName) 
{
	state *st = (state *)data;

	st->sdevs[st->sdevcount].chnnl = atoi(argv[0]);
	st->sdevs[st->sdevcount].devid = atoi(argv[1]);
	st->sdevs[st->sdevcount].fromval = atoi(argv[2]);  
	st->sdevs[st->sdevcount].toval = atoi(argv[3]); 
//printf("init_sensors_of_state_callback %d %d %d %d %d\n", st->sdevcount, st->sdevs[st->sdevcount].chnnl, st->sdevs[st->sdevcount].devid, st->sdevs[st->sdevcount].fromval, st->sdevs[st->sdevcount].toval);
	st->sdevcount++;

	return(0);
}

void init_sensors_of_state(state *st)
{
	sqlite3 *db;
	char *err_msg = NULL;
	char sql[200];
	int rc;

	if ((rc = sqlite3_open(DBPATH, &db)))
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else
	{
//printf("Opened database successfully\n");
		sprintf(sql, "select devices.chnnl, devices.devid, sgdev.fromval, sgdev.toval from sgdev inner join devices on devices.devid = sgdev.devid where sgdev.devgr = %d;", st->sgrid);
		if((rc = sqlite3_exec(db, sql, init_sensors_of_state_callback, (void*)st, &err_msg)) != SQLITE_OK)
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

int init_count_sensors_of_state_callback(void *data, int argc, char **argv, char **azColName) 
{
	state *st = (state *)data;
  
	st->sdevcount = atoi(argv[0]);
	st->sdevs = malloc(st->sdevcount*sizeof(sdev));
//printf("init_count_sensors_of_state_callback %d\n", st->sdevcount);
	st->sdevcount = 0;

	return(0);
}

void init_count_sensors_of_state(state *st)
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
		sprintf(sql, "select count(*) as sensorcount from sgdev where devgr = %d;", st->sgrid);
		if((rc = sqlite3_exec(db, sql, init_count_sensors_of_state_callback, (void*)st, &err_msg)) != SQLITE_OK)
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

int init_states_of_interval_callback(void *data, int argc, char **argv, char **azColName) 
{
	stateinterval *i = (stateinterval *)data;

	i->states[i->statecount].staid = atoi(argv[0]);
	i->states[i->statecount].sgrid = atoi(argv[1]);
	i->states[i->statecount].newvalue = 0; // false
//printf("init_states_of_interval_callback %d %d %d\n", i->statecount, i->states[i->statecount].staid, i->states[i->statecount].sgrid);
	init_count_sensors_of_state(&(i->states[i->statecount]));
	init_sensors_of_state(&(i->states[i->statecount]));

	i->statecount++;

	return(0);
}

void init_states_of_interval(stateinterval *i)
{
	sqlite3 *db;
	char *err_msg = NULL;
	char sql[200];
	int rc;

	if ((rc = sqlite3_open(DBPATH, &db)))
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else
	{
//printf("Opened database successfully\n");
		sprintf(sql, "select statedef.staid, statedef.sgrid from states inner join statedef on states.staid = statedef.staid where states.intid = %d;", i->intid);
		if((rc = sqlite3_exec(db, sql, init_states_of_interval_callback, (void*)i, &err_msg)) != SQLITE_OK)
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

int init_count_states_of_interval_callback(void *data, int argc, char **argv, char **azColName) 
{
	stateinterval *i = (stateinterval *)data;
  
	i->statecount = atoi(argv[0]);
	i->states = malloc(i->statecount*sizeof(state));
//printf("init_count_states_of_interval_callback %d\n", i->statecount);

	i->statecount = 0;

	return(0);
}

void init_count_states_of_interval(stateinterval *i)
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
		sprintf(sql, "select count(*) as statecount from states where intid = %d;", i->intid);
		if((rc = sqlite3_exec(db, sql, init_count_states_of_interval_callback, (void*)i, &err_msg)) != SQLITE_OK)
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

int init_state_intervals_callback(void *data, int argc, char **argv, char **azColName) 
{
	statescheduler *s = (statescheduler *)data;
  
	s->intervals[s->intervalcount].intid = atoi(argv[0]);
	s->intervals[s->intervalcount].seconds = atoi(argv[2]);
	s->intervals[s->intervalcount].c = s->c;
//printf("init_state_intervals_callback %d %d %d\n", s->intervalcount, s->intervals[s->intervalcount].intid, s->intervals[s->intervalcount].seconds);
	init_count_states_of_interval(&(s->intervals[s->intervalcount]));
	init_states_of_interval(&(s->intervals[s->intervalcount]));

	s->intervalcount++;

	return(0);
}

void init_state_intervals(statescheduler *s)
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
		sql = "select * from intervals where itype = 'S';";
		if((rc = sqlite3_exec(db, sql, init_state_intervals_callback, (void*)s, &err_msg)) != SQLITE_OK)
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

int init_count_state_intervals_callback(void *data, int argc, char **argv, char **azColName) 
{
	statescheduler *s = (statescheduler *)data;

	s->intervalcount = atoi(argv[0]);
	s->intervals = malloc(s->intervalcount*sizeof(stateinterval));
//printf("init_count_state_intervals_callback %d\n", s->intervalcount);
	s->intervalcount = 0;

	return(0);
}
  
void init_count_state_intervals(statescheduler *s)
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
		sql = "select count(*) as schedules from intervals where itype = 'S';";
		if ((rc = sqlite3_exec(db, sql, init_count_state_intervals_callback, (void*)s, &err_msg)) != SQLITE_OK)
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

void* state_interval_thread(void *args)
{
	stateinterval *ival = (stateinterval *)args;
	controller *c = ival->c;
	state *st, *oldst, *newst;
	statetransition *t;
	sdev *s;
	adev *a;
	int i, j, k, l;
	unsigned char value;
	int sensorval;
	httpclient h;

	int ctype = PTHREAD_CANCEL_ASYNCHRONOUS;
	int ctype_old;
	pthread_setcanceltype(ctype, &ctype_old);

	ival->threadrunning = 1;
	do
	{
//printf("interval task %d\n", ival->intid);
		if (c)
			ichannel_read(c);

		for(i=0;i<ival->statecount;i++)
		{
			sensorval = 1;
			st = &(ival->states[i]);
			st->oldvalue = st->newvalue;
			for(j=0;(j<st->sdevcount) && (sensorval);j++)
			{
				s = &(st->sdevs[j]);
//printf("%d %d %d %d\n", s->chnnl, s->devid, s->fromval, s->toval);
				if (c)
					value = ichannel_get_value(c, s->chnnl);
				else
					value = jsonReadChannel(&h, s->chnnl, 0);
//printf("sensor %d channel %d value %d\n", s->devid, s->chnnl, value);
				sensorval &= ((value >= s->fromval) && (value <= s->toval));
			}
			st->newvalue = sensorval;
		}

		// transition check
		for(i=0;i<ival->transitioncount;i++)
		{
			t = &(ival->transitions[i]);
			for(j=0;j<ival->statecount;j++)
			{
				oldst = &(ival->states[j]);
				if (oldst->oldvalue && (oldst->staid == t->staidfrom))
				{
					for(k=0;k<ival->statecount;k++)
					{
						newst = &(ival->states[k]);
						if (newst->newvalue && (newst->staid == t->staidto))
						{
							for(l=0;l<t->adevcount;l++)
							{
								a = &(t->adevs[l]);
//printf("%d %d %d\n", a->chnnl, a->devid, a->value);
								if (a->chnnl < 8) // channel
								{
									if (c)
									{
										ochannel_set_value(c, a->chnnl, (unsigned char)a->value);
										ochannel_write(c);
									}
									else
										jsonWriteChannel(&h, a->chnnl, 0, (unsigned char)a->value);
								}
								else if (a->chnnl < 10) // bit
								{
									if (c)
										obit_set_value(c, (unsigned int)a->chnnl, (unsigned char)a->value);
									else
										jsonWriteBit(&h, a->chnnl, 0, (unsigned char)a->value);
								}
								else if (a->chnnl < 12) // pulse
								{
									if (c)
										opulse_out(c, (unsigned int)a->chnnl, a->value);
									else
										jsonWritePulse(&h, a->chnnl, 0, a->value);
								}
							}
							printf("transition %d, from %d to %d\n", i, t->staidfrom, t->staidto);
						}
					}
				}
			}
		}
/*
		for(i=0;i<ival->statecount;i++)
		{
			st = &(ival->states[i]);
			for(j=0;j<st->sdevcount;j++)
			{
				s = &(st->sdevs[j]);
				printf("state %d, device %d, %d -> %d\n", st->staid, s->devid, st->oldvalue, st->newvalue);
			}
		}
		printf("\n");
*/

		sleep(ival->seconds);
	}while (ival->threadrunning);

	ival->retval = 0;
	pthread_exit(&(ival->retval));
}

void init_state_interval_threads(statescheduler *s)
{
	int i, err;

	for(i=0;i<s->intervalcount;i++)
	{
		s->intervals[i].transitioncount = s->transitioncount;
		s->intervals[i].transitions = s->transitions;
		err = pthread_create(&(s->intervals[i].tid), NULL, &state_interval_thread, (void *)&(s->intervals[i]));
		if (err)
			printf("pthread_create error, interval %d\n", i);
	}
}

void close_state_interval_threads(statescheduler *s)
{
	int i, err;

	for(i=0;i<s->intervalcount;i++)
	{
		s->intervals[i].threadrunning = 0;
	}

	for(i=0;i<s->intervalcount;i++)
	{
		err = pthread_join(s->intervals[i].tid, NULL);
		if (err)
			printf("pthread_join error, interval %d\n", i);
	}
}

void init_state_scheduler(statescheduler *s, controller *c)
{
	s->c = c;
	init_count_state_intervals(s);
	init_state_intervals(s);
//printf("intervals %d\n", s->intervalcount);

	init_count_state_transitions(s);
	init_state_transitions(s);

	init_state_interval_threads(s);
}

void close_state_scheduler(statescheduler *s)
{
	int i, j;

	close_state_interval_threads(s);

	for(i=0;i<s->intervalcount;i++)
	{
		for(j=0;j<s->intervals[i].statecount;j++)
		{
			free(s->intervals[i].states[j].sdevs);
		}
		free(s->intervals[i].states);
	}
	free(s->intervals);
}
