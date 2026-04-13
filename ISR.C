#include "ISR.h"
#include <osbind.h>

#define TRAP_28 28

static Vector Org_VBL;
int note_time =0;
int clock_tick = 0;
int ticks = 0;

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

void install_vectors(){
    Org_VBL = install_vector(TRAP_28, trap28_isr);
    trap28();
    disable_midi();
}

void uninstall_vectors(){
    install_vector(TRAP_28, Org_VBL);
    enable_midi();
}

void do_vbl(){
    
    /*if(g_active_player != NULL && g_active_room != NULL){*/
    ticks++;
    clock_tick++;

    /*time music*/
    if (note_time <= 0) {
			upd_music();
			note_time = melody[note][2];
	}
	else {
		note_time--;
	}

    /*sync events*/

    if (ticks >= 70) {
	    upd_timer = 1;
	    ticks = 0;
    }

    update_model();

    /*update game model from asynchronous event requests*/


	/*frame buffer stuff*/
    render_req = 1;
}