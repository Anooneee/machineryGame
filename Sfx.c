#include <osbind.h>
#include "psg.h"

void sfx_attack(){
    int i;
    int v;

    /* Setup a channel for sound and turn it on */
    enable_channel(0, 3, 0);
    set_volume(3, 0, 15); 

    for (i = 350; i >= 120; i += 10)
    {
        set_tone(0, i); /* Tone goes down as sound continues to make swoop noise */
    }

    /* Make tone fade away as sound goes */
    for (v = 15; v >= 0; v--)
    {
        set_volume(0, 0, v);
    }

    stop_sound();
}

void sfx_beep(){ /* for menu clicks */
    int i;

    enable_channel(0,1,0);
    set_volume(0,0,10);
    for (i = 0; i < 50; i++) /* Do for 50 ticks (more than a half second)*/
    {
        set_tone(0, 80);
    }
    stop_sound();
}

void sfx_enemy_die(){
    int i;

    enable_channel(0,1,0);
    set_volume(0,0,10);
    for (i = 0; i < 50; i++) /* Do for 50 ticks (more than a half second)*/
    {
        set_tone(0, 80);
    }
    stop_sound();
   
}

void sfx_jump(){
    int i;

    enable_channel(0,1,0);
    set_volume(0,0,10);
    for (i = 0; i < 50; i++) /* Do for 50 ticks (more than a half second)*/
    {
        set_tone(0, 80);
    }
    stop_sound();
   
}