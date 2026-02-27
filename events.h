#ifndef EVENTS_H
#define EVENTS_H
#include "TYPES.H"
#include "model.h"

/* ---------------------- Asynchronous (Input) Events -----------------------------*/
/* Call when input is clicked */

/* Kinda useless. Need to fix/make better later */
Weapon user_input_x(Player *p, UINT16 *bitmap);

/* Jump! if on ground */
void user_input_space(Player *p);

void user_input_d(Player *p);
void user_input_a(Player *p);
void user_release_d_or_a(Player *p);

/* This is empty */
void user_input_ESC();


/* ---------------------- Conditional Events (Mostly collisions) -----------------------------*/
bool is_collision_between_player_and_enemy(Player p, Enemy e);
bool is_collision_between_player_and_trap(Player p, Trap t);
bool is_collision_between_player_and_wall(Player p, Wall line);
bool is_collision_between_player_and_floor(Player p, Floor line);
bool is_collision_between_sword_and_enemy(Weapon w, Enemy e);
bool is_collision_between_player_and_door(Player p, Exit d);
/* Figure out how to kill enemy/player */

/* ---------------------- Synchronous (Timed) Events -----------------------------*/
/* Call when time has passed (IDK howw)*/

/* Only updates timer right now*/
void every_second(Timer *t); /* Call every 70 ticks */

/*Every movement frame (.5 seconds):
- Checks wall collision and Move player according to horizontal velocity
- Check if there is a floor under the player. Set grounded value accordingly
- Move player according to jump (vertical) velocity
- If player not on ground, make player fall according to vertical velocity
- Move enemy one step forward
- Lower Attack count down (Max is set in attack function)*/
void every_movement_frame(Player *p, Room *r); /* Call every ~35 ticks */

#endif