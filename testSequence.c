#include "testSequence.h"
#include "display.h"

void TSinitialise(void)
{
   DSPdebugSystemInfo("Test Sequence: initialised");
}

event_e TSstartTest(int paragraph)
{
    char info[DISPLAY_SIZE];
    sprintf(info, "%s%d", "starting tests of paragraph: ", paragraph);
    DSPshow(info);
    time_before = clock();
    heatingUpDone = 0;
    heatingUpDone1= 0;
    heatingUpDone2= 0;
    heatingUpDone3= 0;
    heatingUpDone4= 0;
    time_totalTimeSafetyLoop = 0;
    return E_CONTINUE;
}

event_e TSdoTest(void)
{
    event_e Local_event = E_CONTINUE;
    if ( ( (clock() - time_before) /1000) - time_totalTimeSafetyLoop == 2)
    {
        DSPshow("Test Sequence: warming up");
        time_totalTimeSafetyLoop -= 1;
    }

    if ( ( (clock() - time_before) /1000) - time_totalTimeSafetyLoop == 7)
    {
        DSPshow("Test Sequence: turning boiler on");
        time_totalTimeSafetyLoop -= 1;
    }

    if ( ( (clock() - time_before) /1000) - time_totalTimeSafetyLoop == 10)
    {
        DSPshow("Test Sequence: letting warm water flow");
        time_totalTimeSafetyLoop -= 1;
    }

    if ( ( (clock() - time_before) /1000) - time_totalTimeSafetyLoop == 13)
    {
        DSPshow("Test Sequence: building pressure");
        time_totalTimeSafetyLoop -= 1;
    }

    if ( ( (clock() - time_before) /1000) - time_totalTimeSafetyLoop == 16)
    {
        DSPshow("Test Sequence: working in normal operation");
        time_totalTimeSafetyLoop -= 1;
    }

    if ( ( (clock() - time_before) /1000) - time_totalTimeSafetyLoop == 25)
    {
        DSPshow("Test Sequence: Test Done");
        time_totalTimeSafetyLoop -= 1;
        Local_event = E_TEST_DONE;
    }

    if ( ( ( (clock() - time_before) /1000) -time_totalTimeSafetyLoop) %3 == 0)
    {
        time_safetyLoop =clock();
        Local_event = E_TIMER;
        DSPshow("run safety test");
    }
//    char info[DISPLAY_SIZE];
//    sprintf(info, "%s%d", "ellapsed time: ", (int)((clock() - time_before)/1000)-time_totalTimeSafetyLoop );
//    DSPdebugSystemInfo(info);
    return Local_event;
}

void TSreturnToTest(void)
{
    time_totalTimeSafetyLoop += ((clock() - time_safetyLoop)/1000) -1;
}
