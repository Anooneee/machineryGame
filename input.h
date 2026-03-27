#ifndef INPUT_H
#define INPUT_H

#include "types.h"

	/* returns TRUE if there is pending mouse/key input */
bool has_input();

	/* returns TRUE if the given scancode indicates a mouse input */
bool is_mouse_input(UINT8 scancode);

	/* returns the keycode from IKBD RDR */
char get_input();

	/* returns the qwerty key that corresponds to the keycoded in IKBD RDR */
char get_input_key(UINT8 scancode);

	/* Takes in an array of mouse_coords[2], with x and y, and then moves them by the IKBD RDR inputs */
	/* Returns the lower two bits of the ikbd scancode - in other words, it returns 000000lr, with l = left click, and r = right click */
char handle_mouse(int* mouse_coords, UINT8 scancode);

	/* If a mouse input is caused but we don't want to handle the mouse, we can use this to clear the ikbd RDR! */
void clear_mouse_input();

	/* Disables IRQ */
void disable_interrupts();

	/* Enables IRQ */
void enable_interrupts();

#endif