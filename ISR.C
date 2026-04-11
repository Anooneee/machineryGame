#include "ISR.h"
#define TRAP_28 28
#define TRAP_KB 70


int seconds;
typedef void (*Vector)();


static Vector Org_VBL;
static Vector Org_IKBD;


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
    Org_IKBD = install_vector(TRAP_KB, kbd_isr);
    disable_midi();
    Super(old_ssp);
}

void uninstall_vectors(){
    long oldssp;
    long old_ssp = Super(0);
    install_vector(TRAP_28, Org_VBL);
    install_vector(TRAP_KB, Org_IKBD);
    enable_midi();
    Super(old_ssp);
}

void do_vbl(){
    static int note_time = 0;
    static int clock_tick = 0;
    ticks++;
    clock_tick++;

    /*time music*/
    if (note_time =< 0) {
		*current_note = *current_note + 1;

		if (*current_note > 28) {
			*current_note = 0;
		}
        update_music(*current_note);
		note_time = melody[*current_note][2];
	}
	else {
		note_time--;
	}

    /*sync events*/ 
            
    /*update game model*/

	/*frame buffer stuff*/
    render_req = 1;
}

void do_kbd(){

}