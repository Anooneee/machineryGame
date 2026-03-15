#include <osbind.h>
#include <stdio.h>
#include "model.h"
#include "events.h"
#include "render.h"
#include "input.h"
#include "bitmap.h"

int main(){
	UINT32* base;
	Room* room;
	char input;
	Timer timer;
	Player p1;
	Weapon* sword;
	int i, ticks; /* For loop counters */

	int loop = 1;

	p1 = create_player(100,100,player_bitmap);
	timer = create_timer();
	room = create_room_1();
	sword = NULL;

	base = (UINT32*)Physbase();

	init_render(base);
	render_room(base, room);

	/* main game loop: */
	while (loop) {
		/* Input portion: */
		if (has_input()) {
			input = get_input();

			switch (input){
				case 'x':
					/*sword = user_input_x(&p1, weapon_bitmap);*/
					break;
				case ' ':
					user_input_space(&p1);
					break;
				case 'd':
					user_input_d(&p1);
					break;
				case 'a':
					user_input_a(&p1);
					break;
				case 0x1B: /* if pressed escape */
					user_input_ESC();
					loop = 0;
					break;
			}
		}
		else {
			user_release_d_or_a(&p1);
		}

		if (1) { /* REPLACE: if clock ticked, run... */
			ticks++;
			if (ticks >= 70) {
				update_timer(&timer);
				ticks = 0;
			}

			/* sync + cond events: */
			update_player_grounded(&p1, is_collision_between_player_and_floor(&p1, room));

			clear_player(base, &p1);
			clear_enemies(base, room);
			if (sword) {
				clear_weapon(base, sword);
			}

			move_player_vert(&p1);
			move_player_horiz(&p1);
			move_enemies_horiz(room);

			/* Rendering portion: */

			render_timer((UINT8*)base, &timer);
			render_player((UINT16*)base, &p1);
			render_enemies((UINT16*)base, room);

			/*if (sword) {
				render_weapon((UINT16*)base, sword);
			}*/
		}
	}

	/*free_rooms();*/
/*
    if (time_passed == movement_frame){
            
        Every movement frame (.5 seconds):
        - Checks wall collision and Move player according to horizontal velocity
        - Check if there is a floor under the player. Set grounded value accordingly
        - Move player according to jump (vertical) velocity
        - If player not on ground, make player fall according to vertical velocity
        - Move enemy one step forward
        - Lower Attack count down (Max is set in attack function)
        every_movement_frame(&p, &cur_room);
        
        for (i=0; i < cur_room.exit_count; i++){ Loop every exit in the room and test collision with the player
            if (is_collision_between_player_and_door(p1, cur_room.exits[i]) == TRUE){
                return 1;
                SWITCH ROOMS
            }
        }
        for (i=0; i < cur_room.trap_count; i++){ Loop every trap in the room and test collision with the player
            if (is_collision_between_player_and_trap(p1 , cur_room.traps[i]) == TRUE){
                return 1;
                KILL THE PLAYER
            }
        }
        Test sword collision
        if (sword.active == TRUE){
            for (i=0; i < cur_room.enemy_count; i++){ Loop every enemy in the room and test collision with the weapon
                if (is_collision_between_sword_and_enemy(sword, cur_room.enemies[i]) == TRUE){
                    cur_room.enemies[i].dead == TRUE;
                }
            }
        }
    }   
    if (time_passed == 1second){
        every_second(&timer);
    }

    */
    return 0;
}