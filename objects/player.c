#include "player.h"
#include "TYPES.H"    /* for boolean values and UINT */
#include <stdio.h>

void print_player_status(Player p){
    printf("Player: X:%d, Y:%d, Size:%dx%d, Attack_cooldown:%d, Direction Facing:%d, On Ground:%d, Speed:%d, Jump_strength:%d, Horizontal_velocity:%d, Vertical_velocity:%d.\n", p.x,p.y,p.HEIGHT,p.WIDTH,p.attack_cooldown,p.direction,p.grounded,p.speed,p.jump_strength,p.horizontal_velocity,p.vertical_velocity);
};


/* "Teleport" to end of h_movement. Has no wall or end of screen checks. */
void move_player_h(Player *pc, int direction){              /* direction should be the enum for LEFT and RIGHT for readibility but it can also work with just -1 and 1 */
    (*pc).direction = direction;
    (*pc).horizontal_velocity = (*pc).speed * (*pc).direction;
    (*pc).x = (*pc).x + (*pc).horizontal_velocity;
    (*pc).horizontal_velocity = 0;
};

/* Very simple "teleport" to end of jump. No roof or end of screen checks*/
void jump_player(Player *pc){ 
    (*pc).vertical_velocity = (*pc).jump_strength;
    (*pc).y = (*pc).y + (*pc).vertical_velocity;
    (*pc).vertical_velocity = 0;
};

/* NOT DONE. Call every movement frame when player is meant to fall. */
void fall_player(Player *pc, int gravity_strength){
    if ((*pc).grounded == FALSE){
        (*pc).vertical_velocity = -gravity_strength;
        
        (*pc).y = (*pc).y + (*pc).vertical_velocity;
        /* 
            if detect ground at new location + 1: change grounded to true
        */
        (*pc).vertical_velocity = 0;
    }
};

/* Return a weapon object 16 pixels in front of the player and start cooldown period */
Weapon attack(Player *pc, UINT16 *bitmap){
    if ((*pc).attack_cooldown <= 0){
        (*pc).attack_cooldown = 32;
        return create_weapon((*pc).x + (16 * (*pc).direction), (*pc).y, (*pc).direction, bitmap);
    }
};

/* Create player */
Player create_player(int x, int y, UINT32 *bitmap){
    Player p;
    p.x = x;
    p.y = y;
    p.grounded = FALSE;
    p.attack_cooldown = 0;
    p.jump_strength = 64;
    p.horizontal_velocity = 0;
    p.vertical_velocity = 0;
    p.speed = 1;
    p.direction = RIGHT;
    p.HEIGHT = 32;
    p.WIDTH = 16;
    p.bitmap = bitmap;
};