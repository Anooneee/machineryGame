#include <osbind.h>
#include "input.h"

#define RECEIVE_DISABLE 0x16
#define RECEIVE_ENABLE 0x96

volatile UINT8 * const IKBD_control = 0xFFFFFC00;
volatile const UINT8 * const IKBD_status = 0xFFFFFC00;
volatile const UINT8 * const IKBD_RDR = 0xFFFFFC02;

bool has_input() {
	char status;

	long old_ssp = Super(0);		/* Enter supervisor mode */
	status = (*IKBD_status & 0x01);
	Super(old_ssp);

	return status;
}

char get_input() {
	char scancode;

	long old_ssp = Super(0);		/* Enter supervisor mode */
	scancode = *IKBD_RDR;
	Super(old_ssp);

	return scancode;
}

void disable_interrupts() {
	long old_ssp = Super(0);		/* Enter supervisor mode */
	*IKBD_control = RECEIVE_DISABLE;	/* Change IKBD settings */
	Super(old_ssp);
}

void enable_interrupts() {
	long old_ssp = Super(0);		/* Enter supervisor mode */
	*IKBD_control = RECEIVE_ENABLE;		/* Return to normal IKBD settings */
	Super(old_ssp);
}

char get_input_key(UINT8 scancode) {
	if ((scancode & 0xF8) != 0xF8) {					/* If scancode isn't mouse input, proceed */
		char *unshifted = (char *)((Keytbl(-1, -1, -1))->unshift);	/* Get keytable */
		return unshifted[scancode];
	}
	return 0;
}

char handle_mouse(int* mouse_coords, UINT8 scancode) {

	while (!has_input());
	mouse_coords[0] += (signed char)get_input();

	while (!has_input());
	mouse_coords[1] += (signed char)get_input();

	return scancode & 0x03;
}

void clear_mouse_input() {
	while (!has_input());
	get_input();

	while (!has_input());
	get_input();
}

bool is_mouse_input(UINT8 scancode) {
	return ((scancode & 0xF8) == 0xF8);
}