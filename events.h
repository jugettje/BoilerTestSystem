#ifndef EVENTS_H
#define EVENTS_H

/* all possible events
 * <refer to picture nr documentation>!
 */
typedef enum{
    E_NO,
    E_START,
    E_CONTINUE,
    E_SETUP_DONE,
    E_TEST_DONE,
    E_TIMER,
    E_SAFE,
    E_UNSAFE,
    E_COOLED_DOWN,
    E_ERROR,
    E_PARAGRAPH19_1,
    E_PARAGRAPH21_1,
    E_RESET
}event_e;

#endif
