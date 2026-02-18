#include "player_character.h"
#include "TYPES.H"    /* for boolean values and UINT */
#include "attack.h"

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
    Player p = {
        .x = x,
        .y = y,
        .grounded = FALSE,
        .attack_cooldown = 0,
        .jump_strength = 64,
        .horizontal_velocity = 0,
        .vertical_velocity = 0,
        .speed = 1,
        .direction = RIGHT,
        .HEIGHT = 32,
        .WIDTH = 16,
        .bitmap = bitmap,
    };
};