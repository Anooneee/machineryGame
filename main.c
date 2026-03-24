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

UINT32* base;
UINT32* back;
UINT32* temp;

UINT32* original;

long *timer = (long*) 0x462;
long current_time = 0;

char keyboard[128];

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

int main_menu() {
	UINT8 input = 0;
	char chosen = 0;
	int mouse_coords[2] = {0,0}; /* index 0 = x, index 1 = y */

	init_render(base);

	while (1) {
		if (has_input()) {
			input = get_input();

			if (is_mouse_input(input)) {
				clear_mouse(base, mouse_coords);

				chosen = handle_mouse(mouse_coords, input);

				if (mouse_coords[0] < 0) {
					mouse_coords[0] = 0;
				} else if (mouse_coords[0] > 631) {
					mouse_coords[0] = 631;
				}

				if (mouse_coords[1] < 0) {
					mouse_coords[1] = 0;
				} else if (mouse_coords[1] > 391) {
					mouse_coords[1] = 391;
				}					/* setting bounds for mouse */
			}
		}

		render_mouse((UINT8*)base, mouse_coords);

		if (chosen) {
			break;
		}
	}

	Setscreen(original, -1, -1);

	return chosen;
}

int game() {
	/* Variables: */
	UINT8 input;

	Timer timer;
	Player p1;
	int oldX;
	int oldY;

	Weapon* sword;

	int room_number = 1;
	Room* room = 0;

	int i, ticks = 0; /* For loop counters */
	int loop = 1; /* 1 if the game is running, 0 if not */

	/* Program */

	p1 = create_player(START_X,START_Y,player_bitmap);
	timer = create_timer();
	room = change_map(room, room_number);
	sword = 0;

	init_render(base);
	init_render(back);
	render_room(base, room);
	render_room(back, room);
	render_timer((UINT8*)base, &timer);
	render_timer((UINT8*)back, &timer);

	/* main game loop: */
	while (loop) {

		/* Input portion: */

		/* recieve input and sort it into the corresponding keyboard array */
		while (has_input()) {
			input = get_input();

			if (is_mouse_input(input)) {				/* clear IKBD if a mouse movement was detected */
				clear_mouse_input();
			}
			else {
				keyboard[input & ~(0x80)] = input & 0x80;	/* If a key is pressed, that spot in the keyboard array will be set to 0. Else, it will be a nonzero value */
			}
		}
		/* Welcome to magic number zone. I will regrettably be using EXTENSIVE magic numbers to parse input here.
		I don't really see a better way of doing this, so I'll just be commenting what each number means. */
		if (!keyboard[0x1E]) {	/* 0x1E = a */
			user_input_a(&p1);
		}
		if (!keyboard[0x20]) {	/* 0x20 = d */
			user_input_d(&p1);
		}
		if (!keyboard[0x39]) {	/* 0x39 = space */
			user_input_space(&p1);
		}
		if (!keyboard[0x2D]) {	/* 0x2D = x */
			if (!p1.attack_cooldown) {
						sword = user_input_x(&p1);
			}
		}
		if (!keyboard[0x01]) {	/* 0x01 = esc */
			user_input_ESC();
			loop = 0;
		}
		if (keyboard[0x1E] && keyboard[0x20]) {	/* Runs if a and d are both released. */
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

int main() {
	int i;
	int game_chosen = 0;

	disable_interrupts();

	base = (UINT32*)Physbase();
	original = base;
	back = my_malloc(32000);

	for (i = 0; i < 128; i++) {	/* initialize keyboard */
		keyboard[i] = 0x80;
	}


	game_chosen = main_menu();

	if (game_chosen == 2) {
		game();
	}

	Setscreen(original, -1, -1);

	enable_interrupts();

	return 0;
}