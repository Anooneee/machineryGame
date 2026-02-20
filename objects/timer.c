#include "timer.h"
#include <stdio.h>

void print_timer_status(Timer t){
    printf("X:%d, Y:%d, Size:%dx%d, Time_passed:%d.\n", t.x,t.y,t.HEIGHT,t.WIDTH,t.time_passed);
};


/* Call every second that passes */
void update_timer(Timer *t){
    (*t).time_passed = (*t).time_passed + 1;
    (*t).display_value.min = (*t).time_passed / 60;
    (*t).display_value.sec = (*t).time_passed % 60;

    update_display(t);
};

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t){
    /* Draw with font the display value */
}

/* Create timer duh */
Timer create_timer(){
    Timer t;
    t.HEIGHT = 32;
    t.WIDTH = 64;
    t.time_passed = 0;
    t.x = 0;
    t.y = 0;
    t.display_value.colon = ':';
    t.display_value.min = 0;
    t.display_value.sec = 0;
    return t;
};