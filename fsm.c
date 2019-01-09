#include "fsm.h"
#include "display.h"
#include "coolDown.h"
#include "error.h"
#include "optionMenu.h"
#include "safety.h"
#include "testSequence.h"

typedef enum {
    S_NO,
    S_START,
    S_INITIALISED,
    S_WAIT_FOR_SETUP,
    S_TESTING,
    S_CHECK_SAFETY,
    S_COOL_DOWN_MACHINE,
    S_ERROR
} state_e;

state_e currentState = S_START;
event_e event = E_NO;
int ParagraphChoice = 0;
char info[DISPLAY_SIZE];
int timerTrigger = 0, startedTest = 0;

event_e generateEvent(void)
{
    event_e Local_event = E_NO;

    switch(currentState)
    {
        case S_NO:
            DSPshowSystemError("current state is not initialised");
            Local_event = E_ERROR;
        break;
        case S_START:
        break;
        case S_INITIALISED:
            Local_event = BTSinitialise();
        break;
        case S_WAIT_FOR_SETUP:
            if(!ParagraphChoice)
            {
                DSPshow("Choose a paragraph");
                Local_event = OMcheckParagraph();
            }
            else
            {
                sprintf(info, "%s%d", "Paragraph choice = ", ParagraphChoice);
                DSPshow(info);
                Local_event = E_SETUP_DONE;
            }
        break;
        case S_TESTING:
            if(timerTrigger)
            {
                Local_event = E_TIMER;
            }
            else if(!startedTest)
            {
                Local_event = TSstartTest(ParagraphChoice);
                startedTest = 1;
            }
            else
            {
                Local_event = TSdoTest();
            }

        break;
        case S_CHECK_SAFETY:
            Local_event = SAreadValues();
        break;
        case S_COOL_DOWN_MACHINE:

        break;
        case S_ERROR:

        break;
    }

    return Local_event;
}

void eventHandler(event_e _event)
{
    state_e nextState = S_NO;

    switch(currentState)
    {
        case S_NO:
            nextState = S_ERROR;
        break;
        case S_START:
            nextState = S_INITIALISED;
        break;
        case S_INITIALISED:
            if(_event == E_CONTINUE)
            {
                nextState = S_WAIT_FOR_SETUP;
            }
        break;
        case S_WAIT_FOR_SETUP:
            switch(_event)
            {
                case E_PARAGRAPH19_1:
                    ParagraphChoice = 19;
                    nextState = S_WAIT_FOR_SETUP;
                break;
                case E_PARAGRAPH21_1:
                    ParagraphChoice = 21;
                    nextState = S_WAIT_FOR_SETUP;
                break;
                case E_SETUP_DONE:
                    nextState = S_TESTING;
                break;
            }
        break;
        case S_TESTING:
            switch (_event)
            {
                case E_CONTINUE:
                    nextState = S_TESTING;
                break;
                case E_TIMER:
                    nextState = S_CHECK_SAFETY;
                break;
                case E_TEST_DONE:
                    nextState = S_COOL_DOWN_MACHINE;
                break;
            }
        break;
        case S_CHECK_SAFETY:
            switch(_event)
            {
                case E_SAFE:
                    TSreturnToTest();
                    nextState = S_TESTING;
                break;
                case E_UNSAFE:
                    nextState = S_COOL_DOWN_MACHINE;
                break;
            }
        break;
        case S_COOL_DOWN_MACHINE:

        break;
        case S_ERROR:
            nextState = S_ERROR;
        break;
    }
    currentState = nextState;
}

event_e BTSinitialise(void)
{
    CDinitialise();
    ERRinitialise();
    OMinitialise();
    SAinitialise();
    TSinitialise();
    DSPshow("   <===============> Boiler Test System <===============> ");
    return E_CONTINUE;
}


