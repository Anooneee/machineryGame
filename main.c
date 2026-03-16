#include <osbind.h>
#include <stdio.h>
#include "model.h"
#include "events.h"
#include "render.h"
#include "input.h"
#include "bitmap.h"

#define START_X 100
#define START_Y 40

int main(){
	char input;

	Timer timer;
	Player p1;

	Weapon* sword;

	int room_number;
	Room* room = 0;

	UINT32* base;

	int i, ticks; /* For loop counters */

	int loop = 1;
	room_number = 1;

	p1 = create_player(START_X,START_Y,player_bitmap);
	timer = create_timer();
	room = change_map(room, room_number);
	sword = 0;

	base = (UINT32*)Physbase();

	init_render(base);
	render_room(base, room);

	/* main game loop: */
	while (loop) {
		/* Input portion: */
		if (has_input()) {
			input = get_input();

			switch (input){
				case 'a':
					user_input_a(&p1);
					break;
				case 'd':
					user_input_d(&p1);
					break;
				case ' ':
					user_input_space(&p1);
					break;
				case 'x':
					sword = user_input_x(&p1);
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

			/* synchronous events: */
			update_player_grounded(&p1, is_collision_between_player_and_floor(&p1, room));

			clear_player(base, &p1);
			clear_enemies(base, room);

			if (sword) {
				render_weapon(base, sword);
				kill_attacked_enemies(room, sword);

				clear_weapon(base, sword);
				free_weapon(sword);
				sword = 0;
			}

			/* Conditional events: */
			if (is_collision_between_player_and_exits(&p1, room)) {
				if (room_number == 5) {
					loop = 0;
					game_message((UINT8*)base, "You win!");
				}
				else {
					room_number++;
				}
				room = change_map(room, room_number);
				init_render(base);
				render_room(base, room);
				teleport_player(START_X, START_Y, &p1);
			}

			if (is_player_dead(room, &p1)) {
				game_message((UINT8*)base, "You lose!!!");
				loop = 0;
			}

			move_player_vert(&p1);
			if (!is_collision_between_player_and_wall(&p1, room)) {
				move_player_horiz(&p1);	
			}
			move_enemies_horiz(room);
			decrement_cooldown(&p1);

			/* Rendering portion: */

			render_timer((UINT8*)base, &timer);
			render_player((UINT16*)base, &p1);
			render_enemies((UINT16*)base, room);

		}
	}

	return 0;
}