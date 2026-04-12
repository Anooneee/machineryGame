#include "ISR.h"
#include <osbind.h>

#define TRAP_28 28

extern void vbl_isr();

static Vector Org_VBL;


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
	*((volatile unsigned char*)0xFFFFFA09) &= ~(1 << 7);
}

void enable_midi() {
	*((volatile unsigned char*)0xFFFFFA09) |= (1 << 7);
}

void install_vectors(){
    long oldssp;
    long old_ssp = Super(0);
    Org_VBL = install_vector(TRAP_28, vbl_isr);
    disable_midi();
    Super(old_ssp);
}

void uninstall_vectors(){
    long oldssp;
    long old_ssp = Super(0);
    install_vector(TRAP_28, Org_VBL);
    enable_midi();
    Super(old_ssp);
}

void do_vbl(){
    static int note_time;
    static int clock_tick = 0;
	static int ticks = 0;
    ticks++;
    clock_tick++;

    /*time music*/
    if (note_time =< 0) {
		update_music();
		note_time = melody[note][2];
	}
	else {
		note_time--;
	}

    /*sync events*/ 

            
    /*update game model*/

	/*frame buffer stuff*/
    render_req = 1;
}