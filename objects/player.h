#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H
#include "TYPES.H"    /* for boolean values and UINT and LEFT and RIGHT */
#include "attack.h"

/* -------------- struct ---------------

    Example use:
    Player p1 = create_player(100,250,bitmap)
    for p1 at position (100,250), with other values at default, and pointer to bitmap.

*/

typedef struct Player_character{     /* type definition for player object */
    UINT16 x, y;                     /* position coordinates */
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    int vertical_velocity;              /* vert . displacement per clock tick*/
    int jump_strength;
    int speed;
    int direction;
    bool grounded;
    int attack_cooldown;
    int HEIGHT, WIDTH;            /* 32, 16 */
    UINT32 *bitmap;

} Player ;

/* Move player to position = x + (+/-)speed. (Speed is currently set at 1 by default in create_player()). 
    Has no wall or end of screen checks. */
/* -------------- move example use ---------------
    
    for every movement frame
        if user_input == 'right':
            if wall check and enemy check clear in p1.x + p1.speed:
                move_player_h(p1,RIGHT)
        if user_input == 'left':
            if wall check and enemy check clear in p1.x - p1.speed:
                move_player_h(p1,LEFT)

    ********* LEFT and RIGHT are enums for -1 and 1 defined in TYPES.H *********

*/
void move_player_h(Player *pc, int direction); /* direction should be the enum for LEFT and RIGHT for readbility but it can also work with just -1 and 1 */

/* NOT DONE. "teleport" to end of jump. No roof or end of screen checks*/
void jump_player(Player *pc);

/* NOT DONE. Call every movement frame when player is meant to fall. */
void fall_player(Player *pc, int gravity_strength);

/* Return a weapon object 16 pixels in front of the player. Attack cooldown = 32 or something */
Weapon attack(Player *pc, UINT16 *bitmap);

/* Create player with all default values at position x,y and pointer to bitmap */
Player create_player(int x, int y, UINT32 *bitmap);

void print_player_status(Player p);

#endif