#ifndef TESTSEQUENCE_H
#define TESTSEQUENCE_H

#include "events.h"
#include <time.h>

void TSinitialise(void);
event_e TSstartTest(int paragraph);
event_e TSdoTest(void);
void TSreturnToTest(void);

clock_t time_before;
clock_t time_safetyLoop;
int time_totalTimeSafetyLoop;
int heatingUpDone;
int heatingUpDone1;
int heatingUpDone2;
int heatingUpDone3;
int heatingUpDone4;

#endif
