#ifndef FSM_H
#define FSM_H

#include "events.h"

event_e generateEvent(void);
void eventHandler(event_e evnt);

event_e BTSinitialise(void);


#endif
