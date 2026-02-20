#ifndef TIMER_DISPLAY_H
#define TIMER_DISPLAY_H
#include "TYPES.H"    /* for boolean values and UINT and LEFT and RIGHT */

typedef struct display_string{
    int min;
    char colon;
    int sec;
} Display;

typedef struct timer_display{
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int time_passed;
    Display display_value;
} Timer;

/* Call every second that passes. Calls update_display when done */
void update_timer(Timer *t);

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t);

/* Call to return timer */
Timer create_timer();

void print_timer_status(Timer t);

#endif