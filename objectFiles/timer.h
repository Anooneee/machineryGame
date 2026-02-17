#ifndef TIMER_H
#define TIMER_H

typedef struct timer_display{
    int x, y;
    int height, width;
    int time_passed;
    char display_value[];
} Timer;

/* NOT DONE. Call every second that passes. Calls update_display when done */
void update_timer(Timer *t);

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t);

#endif