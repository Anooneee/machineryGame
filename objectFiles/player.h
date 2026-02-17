#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>    /* for boolean values */


/* -------------- struct ---------------

    Example initialize:
    Player p1 = {x,y,0,0,64,false,false,32,16, bitmap[BITMAP_HEIGHT]} 
    for at postion (x,y), not moving, jump strength == 64pixels, not on the floor, and not attacking, with size (32,16), and bitmap

*/

typedef struct Player_character{     /* type definition for player object */
    unsigned int x, y;                  /* position coordinates */
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    int vertical_velocity;              /* vert . displacement per clock tick*/
    int jump_strength;
    bool grounded;
    bool attacking;
    int HEIGHT, WIDTH;            /* 32, 16 */
    unsigned int *bitmap;
} Player ;

/* NOT DONE. "Teleport" to end of h_movement. Has no wall or end of screen checks. */
void move_player_h(Player *pc, int h_direction);

/* NOT DONE. "teleport" to end of jump. No roof or end of screen checks*/
void jump_player(Player *pc);

/* NOT DONE. Routine double checks if player is not on ground. Call every frame with gravity value*/
void fall_player(Player *pc, int gravity_strength);

/* NOT DONE */
void attack(Player *pc);

#endif