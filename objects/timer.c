#include "timer.h"

typedef struct timer_display{
    UINT16 x, y;
    int height, width;
    int time_passed;
    Display display_value;
} Timer;

typedef struct display_string{
    int min;
    char colon;
    int sec;
} Display;

/* Call every second that passes */
void update_timer(Timer *t){
    (*t).time_passed = (*t).time_passed + 1;
    (*t).display_value.min = (*t).time_passed / 60;
    (*t).display_value.sec = (*t).time_passed % 60;

    update_display(t);
}

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t){
    /* Draw with font the display value */
}

/* Create timer duh */
Timer create_timer(){
    Timer t = {
        .height = 32,
        .width = 64,
        .time_passed = 0,
        .x = 0,
        .y = 0,
        .display_value = {
            .colon = ':',
            .min = 0,
            .sec = 0,
        }
    };
    return t;
};