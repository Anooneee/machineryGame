#include "player.h"
#include <stdbool.h>    /* for boolean values */

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

/* "Teleport" to end of h_movement. Has no wall or end of screen checks. */
void move_player_h(Player *pc, int h_direction){ /* h_direction is either negative for left or positive for right */
    pc->horizontal_velocity = h_direction;
    pc->x = pc->x + pc->horizontal_velocity;
    pc->horizontal_velocity = 0;
}

/* Very simple "teleport" to end of jump. No roof or end of screen checks*/
void jump_player(Player *pc){ 
    pc->vertical_velocity = pc->jump_strength;
    pc->y = pc->y + pc->vertical_velocity;
    pc->vertical_velocity = 0;
}

/* Routine double checks if player is not on ground. Call every frame with gravity value*/
void fall_player(Player *pc, int gravity_strength){
    if (pc->grounded == false){
        pc->vertical_velocity = -gravity_strength;
        /* while (pc->grounded == false){
            pc->y = pc->y + pc->vertical_velocity;
            
            if detech ground: change grounded to true

        } */
        pc->y = pc->y + pc->vertical_velocity;
        pc->vertical_velocity = 0;
    }
}

/* Not done */
void attack(Player *pc){
    /* Summon sword object */
    /* sword.x = pc.x + 16 */
    /* sword.y = pc.y */
}