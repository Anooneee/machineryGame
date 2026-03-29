#ifndef RENDER_H
#define RENDER_H

#include "types.h"
#include "model.h"

void init_render(UINT32* base);

	/* functions to plot and erase bitmaps for the cursor (for the main menu) */

void render_mouse(UINT8* base, int* mouse_coords);
void clear_mouse(UINT32* base, int* mouse_coords);

	/* functions for erasing the bitmap for the player, enemies, and weapon */

void clear_player(UINT32* base, Player* p, int x, int y);
void clear_enemies(UINT32* base, Room* room);
void clear_weapon(UINT32* base, Weapon* w);

	/* functions for rendering every piece of the screen */

void render_player(UINT16* base, Player* p);
void render_weapon(UINT32* base, Weapon* w);

void render_enemies(UINT16* base, Room* r);
void render_enemy(UINT16* base, Enemy* e);

void render_trap(UINT16* base, Trap* t);
void render_exit(UINT32* base, Exit* e);
void render_left_wall(UINT8* base, Wall* w);
void render_right_wall(UINT8* base, Wall* w);
void render_floor(UINT32* base, Floor* f);
void render_room(UINT32* base, Room* r);

	/* render the current timer in the top left of the screen */

void render_timer(UINT8* base, Timer* t);

	/* print a message at the given coordinates */

void game_message(UINT8* base, char* message, int x, int y);

	/* functions for rendering and clearing the main menu. Automatically highlights the currently selected button */

void render_main_menu(UINT32* base, char chosen);
void clear_main_menu(UINT32* base);

#endif