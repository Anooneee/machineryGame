#include <osbind.h>
#include "isr.h"
#define TRAP_28 112

int ticks;

/* Replace old ISR at vector number "num" 
with our own custom vector */
Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}

/* Midi port uses same vector number as IKBD 
- Disable to make sure our custom IKBD ISR doesnt service the wrong interupt */
void disable_midi() {
    long old_ssp = Super(0);
	*((volatile unsigned char*)0xFFFFFA09) &= ~(1 << 7);
	Super(old_ssp);
}

/* Return the environment to normal */
void enable_midi() {
	long old_ssp = Super(0);
	*((volatile unsigned char*)0xFFFFFA09) |= (1 << 7);
	Super(old_ssp);
}

/* VBL ISR will serve as the timer 
- Interupt called every clock tick
- Trigger upd_timer request when a second has passed
- Every call:
	- Trigger upd_music request 
	- Trigger upd_model request
	- Trigger render_req request 
*/
void do_vbl(){
	ticks++;
	if (ticks >= 70) {		/*this is handled in the vbl*/
		upd_timer = 1;
    	ticks = 0;
   	}
	/*time music*/
	upd_music();

	/* Ensures that there are 70 ticks per second*/
    if (ticks >= 70) {
		upd_timer = 1;
		ticks = 0;
    }
	upd_model = 1;
	render_req = 1;
}
