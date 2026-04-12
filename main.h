#ifndef MAIN_H
#define MAIN_H

#include "types.h" /* Assuming UINT32, UINT8, etc. are defined here */
#include "model.h"

/* 
 * Global Variables
 * These are defined in the .c file and made available to other modules 
 */
extern UINT32* base;
extern UINT32* back;
extern UINT32* temp;
extern UINT32* original;

extern long *timer;
extern long current_time;
extern int render_req;
extern int note;
extern int render_rq;
extern int rdr_room_flag;
extern int rdr_timer_flag;
extern int rdr_sword_flag;
extern int clear_sword_flag;


/* 
 * Function Prototypes
 */

/**
 * Checks if the system clock (0x462) has incremented.
 * Returns: TRUE if a tick occurred, FALSE otherwise.
 */
bool timer_ticked();

/**
 * Handles the logic and rendering for the main menu.
 * Returns: The index of the menu option chosen by the user.
 */
int main_menu();

/**
 * The main game loop handling input, physics updates, and double-buffered rendering.
 * Returns: 0 upon completion.
 */
int game();

/**
 * Entry point. Initializes hardware, ISRs, and memory buffers.
 */
int main();

#endif /* MAIN_H */