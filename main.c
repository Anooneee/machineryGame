#include <osbind.h>
#include "model.h"
#include "events.h"
#include "render.h"
#include "raster.h" /* For getting vid base*/
#include "input.h"
#include "bitmap.h"
#include "mem.h"
#include "music.h"
#include "psg.h"
#include "Sfx.h"
#include "ISR.h"

UINT32* base;
UINT32* back;
UINT32* temp;

UINT32* original;

long *timer = (long*) 0x462;
long current_time = 0;

static UINT8 screen[32256];

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

	int current_mouse_coords[2] = {0,0};
	int old_mouse_coords[2] = {0,0};

	init_render(base);
	init_render(back);

	while (1) {
		current_mouse_coords[0] = mouse_coords[0];	/* saving current mouse pos to prevent desync later on!!! */
		current_mouse_coords[1] = mouse_coords[1];

		if (mouse_header) {						/* if the mouse moved, do this */
			if ((mouse_header & 0x03) && chosen != 3) break;	/* If clicked, break. header = 111110lr */
			mouse_header = 0;
		}

		chosen = main_menu_get_chosen(current_mouse_coords);

		/* rendering */
		render_main_menu(back, chosen);
		render_mouse((UINT8*)back, current_mouse_coords);

		/* Swap framebuffers: */
		temp = base;
		base = back;
		back = temp;

		Vsync();
		set_video_base(back);

		/* clear old framebuffer */
		clear_main_menu(back);
		clear_mouse(back, old_mouse_coords);

		old_mouse_coords[0] = current_mouse_coords[0];
		old_mouse_coords[1] = current_mouse_coords[1];
	}

	return chosen;
}

int game() {
	/* Variables: */
	UINT8 input = 0x80;

	Timer timer;
	Player p1;
	long old_ssp;
	int oldX;
	int oldY;

	Weapon* sword;

	int room_number = 1;
	Room* room = 0;

	int i;
	int ticks = 0;
	int running = 1; /* 1 if the game is running, 0 if not */
	long time_then;
	int current_note = 0;

	/* Program */
	
	timer = create_timer();
	room = change_map(room, room_number);
	p1 = create_player(room->start_x,room->start_y,player_bitmap);
	sword = 0;

	start_music();

	init_render(base);
	init_render(back);
	render_room(base, room);
	render_room(back, room);
	render_timer((UINT8*)base, &timer);
	render_timer((UINT8*)back, &timer);


	/* main game loop: */
	i = 0;
	while (running) {
		/* Input events portion: */
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
			running = 0;
		}
		if (keyboard[0x1E] && keyboard[0x20]) {	/* Runs if a and d are both released. */
			user_release_d_or_a(&p1);
		}

		/* Main game: */
		if (timer_ticked()) {
			oldX = p1.x;
			oldY = p1.y;

			ticks++;
			if (ticks >= 70) {
				update_timer(&timer);
				ticks = 0;
			}

			/* synchronous events: */
			update_player_grounded(&p1, is_collision_between_player_and_floor(&p1, room));

			if (sword) {
				if (sword->justCreated) {
					save_bg(back, sword);
					sword->justCreated = FALSE;
				}
				render_weapon(back, sword);
				kill_attacked_enemies(room, sword);

				if (p1.attack_cooldown <= 1) {
					clear_weapon(back, sword);
					clear_weapon(base, sword);
					free_weapon(sword);
					sword = 0;
				}
			}

			/* Music playing! */
			upd_music(&current_note);

			/* Conditional events: */
			if (is_collision_between_player_and_exits(&p1, room)) {
				if (room_number == 3) {
					running = 0;
					game_message((UINT8*)base, "You win!", 220, 300);
					game_message((UINT8*)back, "You win!", 220, 300);
				}
				else {
					room_number++;
					room = change_map(room, room_number);

					init_render(base);
					init_render(back);
					render_room(base, room);
					render_room(back, room);

					teleport_player(room->start_x, room->start_y, &p1);
				}
			}

			if (is_player_dead(room, &p1)) {
				game_message((UINT8*)base, "You lose!!!", 220, 300);
				game_message((UINT8*)back, "You lose!!!", 220, 300);
				running = 0;
			}


			move_player_vert(&p1, room);
			move_player_horiz(&p1, room);

			move_enemies_horiz(room);
			decrement_cooldown(&p1);


			/* Rendering portion: */

			render_player((UINT16*)back, &p1);
			render_enemies((UINT16*)back, room);
			render_timer((UINT8*)back, &timer);

			/* Swap framebuffers: */
			temp = base;
			base = back;
			back = temp;

			Vsync();
			set_video_base(back);

			/* Clear the screen around movable entites: */
			clear_player(back, &p1, oldX, oldY);
			clear_enemies(back, room);

		}
	}

	return 0;
}

int main() {
	int i;
	int game_chosen = 0;
	Vector orig;

	disable_midi();
	orig = install_vector(70, ikbd_isr);

	base = get_video_base();
	original = base;
	back = (UINT32*)(((long)my_malloc(32256) + 256) & ~255);	/* Aligning address along 256 bytes */


	for (i = 0; i < 128; i++) {	/* initialize keyboard */
		keyboard[i] = 1;
	}

	game_chosen = main_menu();

	if (game_chosen == 0) {
		game();
	}

	set_video_base(original);

	install_vector(70, orig);
	enable_midi();

	return 0;
}