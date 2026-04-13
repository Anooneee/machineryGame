#include <osbind.h>
#include "isr.h"
#define TRAP_28 112

int ticks;

Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}

void disable_midi() {
	long old_ssp = Super(0);
	*((volatile unsigned char*)0xFFFFFA09) &= ~(1 << 7);
	Super(old_ssp);
}

void enable_midi() {
	long old_ssp = Super(0);
	*((volatile unsigned char*)0xFFFFFA09) |= (1 << 7);
	Super(old_ssp);
}

void do_vbl(){
    ticks++;

    /*time music*/
    
	upd_music();
    if (ticks >= 70) {
	    upd_timer = 1;
	    ticks = 0;
    }
}
