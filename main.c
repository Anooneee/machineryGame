#include "model.h"
#include "bitmap.h"
#include <osbind.h>
#include "types.h"


UINT32 get_time(){};

int main(){
    Room cur_room;
    Timer timer;
    Player p1;
    Weapon sword;
    int i; /* For loop counters */
    int quit = 0;
    UINT32 timeThen, timeNow, timeElapsed;

    while(quit < 1){
    p1 = create_player(100,100,PLAYERBITMAP);

    if (input in buffer){ /* I'll figure this out later im just mapping it out rn */
        if input_pressed == x:
            w = user_input_x(p1, WEAPONBITMAP);
        if input_pressed == space:
            user_input_space(&p1);
        if input_pressed == d:
            user_input_d(&p1);
        if input_pressed == a:
            user_input_a(&p1);
        if release_input == d or a:
            user_release_d_or_a(&p1);

        if input_pressed == ESC:
            user_input_ESC(); /* This is empty right now */

    }

    /* Updating the game */

    if (time_passed == movement_frame){
            
        /*Every movement frame (.5 seconds):
        - Checks wall collision and Move player according to horizontal velocity
        - Check if there is a floor under the player. Set grounded value accordingly
        - Move player according to jump (vertical) velocity
        - If player not on ground, make player fall according to vertical velocity
        - Move enemy one step forward
        - Lower Attack count down (Max is set in attack function)*/
        every_movement_frame(&p, &cur_room);
        
        for (i=0; i < cur_room.exit_count; i++){ /* Loop every exit in the room and test collision with the player */
            if (is_collision_between_player_and_door(p1, cur_room.exits[i]) == TRUE){
                return 1;
                /* SWITCH ROOMS */
            }
        }
        for (i=0; i < cur_room.trap_count; i++){ /* Loop every trap in the room and test collision with the player */
            if (is_collision_between_player_and_trap(p1 , cur_room.traps[i]) == TRUE){
                return 1;
                /* KILL THE PLAYER */
            }
        }
        /* Test sword collision */
        if (sword.active == TRUE){
            for (i=0; i < cur_room.enemy_count; i++){ /* Loop every enemy in the room and test collision with the weapon */
                if (is_collision_between_sword_and_enemy(sword, cur_room.enemies[i]) == TRUE){
                    cur_room.enemies[i].dead == TRUE;
                }
            }
        }
    }   
    if (time_passed == 1second){
        every_second(&timer);
    }
}
    
    return 0;
}

UINT32 get_time() {
    long old_ssp;
    old_ssp = Super(0);
    timeNow = *timer;
    Super(old_ssp);
    return timer;
}

