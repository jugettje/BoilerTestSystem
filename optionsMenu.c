#include "optionMenu.h"
#include "display.h"
#include "keyboard.h"

void OMinitialise(void)
{
   DSPdebugSystemInfo("Options Menu: initialised");
}

char OMinputParagraph()
{
    int paragraphIsOk = 0;
    char paragraph = '0';
    while (!paragraphIsOk)
    {
        paragraph = KYBgetchar();
        switch(paragraph)
        {
            case '1':
            case '2':
               paragraphIsOk = 1;
               break;
            default:
               DSPdebugSystemInfo("Options Menu: unknown paragraph");
               DSPsimulationSystemInfo("Paragraphs: <1> 19  <2> 21");
               break;
        }
    }
    return paragraph;
}

event_e OMcheckParagraph(void)
{
    char paragraph = '0';
    event_e event = E_NO;

    DSPsimulationSystemInfo("Paragraphs: <1> 19.1  <2> 21.1");
    paragraph = OMinputParagraph();

    switch(paragraph)
    {
        case '1':
            event = E_PARAGRAPH19_1;
            DSPdebugSystemInfo("19");
        break;
        case '2':
            event = E_PARAGRAPH21_1;
            DSPdebugSystemInfo("21");
        break;
    }
    return event;
}
