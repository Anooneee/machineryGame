#include <osbind.h>
#include "psg.h"
#include "sfx.h"

void sfx_attack(){
    /* Setup a channel for sound and turn it on */
    set_noise(12);
    enable_channel(2, 0, 1);
    set_volume(2, 1, 15);
    set_envelope(9, 20);
}

/* for menu clicks */
void sfx_beep(){ 
    set_tone(2, 250);
    enable_channel(2,1,0);
    set_volume(2,0,10);
    set_envelope(9,6);
}

void sfx_enemy_die(){
    set_noise(23);
    enable_channel(1,1,0);
    set_volume(1,1,8);
    set_envelope(10, 30);
}

void sfx_jump(){
    set_noise(17);
    enable_channel(2,0,1);
    set_volume(2,1,10);
/*    set_envelope(4,15);*/
}