#ifndef INPUT_H
#define INPUT_H

#include "types.h"

/* 
Input.h/c only stores the global variables used for processing the keyboard and mouse. 
Also, the declaration for ikbd_isr() is stored here... Say hi, ikbd_isr()!
*/

extern volatile char mouse_state;	/* Used exclusively in the ikbd_isr, you can 
extern volatile char mouse_header;	/* Stores data on the mouse header. Can be used to process clicks */
extern volatile int mouse_coords[];	/* x and y coords */
extern volatile char keyboard[128];	/* keyboard[i] = 0 if keycode i is being pressed, and keyboard[i] = 1 if released. */

void ikbd_isr(); /* "hi" */
/* 
TO NOTE: The ikbd_isr is written entirely in assembly.
It takes an input byte, reads it as a mouse/keyboard input, and then updates the proper global variable according to the contents of that byte.
*/

#endif