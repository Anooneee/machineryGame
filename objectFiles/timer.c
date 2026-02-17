#include "timer.h"
#include <stdio.h>

typedef struct timer_display{
    int x, y;
    int height, width;
    int time_passed;
    char display_value[];
} Timer;

/* NOT DONE. Call every second that passes */
void update_timer(Timer *t){
    int min;
    int sec;

    t->time_passed = t->time_passed + 1;
    min = t->time_passed / 60;
    sec = t->time_passed % 60;

    /*t->display_value = min + ":" + sec;*/
    update_display(t);
}

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t){
    /* Draw with font the display value */
}