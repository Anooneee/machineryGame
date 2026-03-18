#include <osbind.h>
#include <stdio.h>
#include "model.h"
#include "events.h"
#include "render.h"
#include "input.h"
#include "bitmap.h"
#include "mem.h"

#define START_X 96
#define START_Y 40

UINT32* original;

long *timer = (long*) 0x462;
long current_time = 0;

bool timer_ticked() {
	long old_ssp = Super(0);

	if (current_time != *timer) {
		current_time = *timer;
		Super(old_ssp);
		return TRUE;
	}
	Super(old_ssp);
	return FALSE;
}

int main(){
	/* Variables: */
	char input;

	Timer timer;
	Player p1;
	int oldX;
	int oldY;

	Weapon* sword;

	int room_number = 1;
	Room* room = 0;

	UINT32* base;
	UINT32* back;
	UINT32* temp;

	int i, ticks = 0; /* For loop counters */
	int loop = 1; /* 1 if the game is running, 0 if not */

	/* Program */

	p1 = create_player(START_X,START_Y,player_bitmap);
	timer = create_timer();
	room = change_map(room, room_number);
	sword = 0;

	base = (UINT32*)Physbase();
	original = base;
	back = my_malloc(32000);

	init_render(base);
	init_render(back);
	render_room(base, room);
	render_room(back, room);
	render_timer((UINT8*)base, &timer);
	render_timer((UINT8*)back, &timer);

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
					if (!p1.attack_cooldown) {
						sword = user_input_x(&p1);
					}
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

		if (timer_ticked()) {
			oldX = p1.x;
			oldY = p1.y;

			ticks++;
			if (ticks >= 70) {
				update_timer(&timer);
				ticks = 0;
				render_timer((UINT8*)back, &timer);
			}

			/* synchronous events: */
			update_player_grounded(&p1, is_collision_between_player_and_floor(&p1, room));

			if (sword) {
				render_weapon(back, sword);
				kill_attacked_enemies(room, sword);

				if (p1.attack_cooldown <= 1) {
					clear_weapon(back, sword);
					clear_weapon(base, sword);
					free_weapon(sword);
					sword = 0;
				}
			}

			/* Conditional events: */
			if (is_collision_between_player_and_exits(&p1, room)) {
				if (room_number == 5) {
					loop = 0;
					game_message((UINT8*)base, "You win!");
					game_message((UINT8*)back, "You win!");
				}
				else {
					room_number++;
					room = change_map(room, room_number);

					init_render(base);
					init_render(back);
					render_room(base, room);
					render_room(back, room);
					render_timer((UINT8*)back, &timer);

					teleport_player(START_X, START_Y, &p1);
				}
			}

			if (is_player_dead(room, &p1)) {
				game_message((UINT8*)base, "You lose!!!");
				game_message((UINT8*)back, "You lose!!!");
				loop = 0;
			}


			move_player_vert(&p1, room);
			move_player_horiz(&p1, room);

			move_enemies_horiz(room);
			decrement_cooldown(&p1);

			/* Rendering portion: */

			render_player((UINT16*)back, &p1);
			render_enemies((UINT16*)back, room);


			/* Swap framebuffers: */
			temp = base;
			base = back;
			back = temp;

			Vsync();
			Setscreen(base, -1, -1);

			/* Clear the screen around movable entites: */
			clear_player(back, &p1, oldX, oldY);
			clear_enemies(back, room);

		}
	}

	Setscreen(original, -1, -1);

	return 0;
}