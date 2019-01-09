#include <fsm.h>


int main()
{
    event_e currentEvent = E_START;

    eventHandler(currentEvent);
    // Endless loop
    while (1)
    {
       currentEvent = generateEvent();
       eventHandler(currentEvent);
    }
    return 0;
}
