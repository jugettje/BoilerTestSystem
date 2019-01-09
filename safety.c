#include "safety.h"
#include "display.h"
#include "keyboard.h"


void SAinitialise(void)
{
   DSPdebugSystemInfo("Safety: initialised");
}

char SAreadInput(void)
{
    int correctInput = 0;
    char safe = '0';
    while(!correctInput)
    {
        safe = KYBgetchar();
        switch(safe)
        {
            case '1':
            case '2':
                correctInput = 1;
            break;
            default:
                DSPdebugSystemInfo("Safety: unknown input");
                DSPsimulationSystemInfo("temp too high?: <1> yes  <2> no");
            break;
        }
    }
    return safe;
}

event_e SAreadValues(void)
{
    event_e event = E_NO;
    char safe = '0';
    DSPsimulationSystemInfo("temp too high?: <1> yes  <2> no");
    safe = SAreadInput();
    switch(safe)
    {
        case '1':
            event = E_UNSAFE;
        break;
        case '2':
            event = E_SAFE;
        break;
    }
    return event;
}
