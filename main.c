#include <osbind.h>
#include <stdio.h>
#include "main.h"
#include "model.h"
#include "events.h"
#include "render.h"
#include "input.h"
#include "bitmap.h"
#include "mem.h"
#include "music.h"
#include "psg.h"
#include "Sfx.h"

UINT32* base;
UINT32* back;
UINT32* temp;
UINT32* original;

long *timer = (long*) 0x462;
long current_time = 0;
int note = 0;
int render_req = 0;
int rdr_room_flag = 0;
int rdr_timer_flag = 0;
int rdr_sword_flag = 0;
int clear_sword_flag = 0;

static UINT8 screen[32256];

char keyboard[128];		/* Stores the state of every key on the board. 0 = pressed, 1 = not pressed. */

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

	init_render(base);

	render_main_menu(base, chosen);

	while (1) {

		/* input portion */
		while (has_input()) {
			input = get_input();

			if (is_mouse_input(input)) {
				clear_mouse_input();
			}
			else {
				keyboard[input & ~(0x80)] = input & 0x80;
			}

			if (!keyboard[0x11]) chosen++;		/* If the user presses W, go to the option above */
			else if (!keyboard[0x1F]) chosen--;	/* If the user presses S, go to the option below */

			if (chosen > 1) chosen = 0;
			if (chosen < 0) chosen = 1;		/* bounds checking for the currently-selected option */

			if (!keyboard[0x1C]) return chosen;	/* if the user presses ENTER, return the currently selected option */

			clear_main_menu(base);
			render_main_menu(base, chosen);
		}
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
	int note_time;

	/* Program */
	
	timer = create_timer();
	room = change_map(room, room_number);
	p1 = create_player(room->start_x,room->start_y,player_bitmap);
	sword = 0;

	start_music();
	note_time = melody[note][2];


	init_render(base);
	init_render(back);
	render_room(base, room);
	render_room(back, room);
	render_timer((UINT8*)base, &timer);
	render_timer((UINT8*)back, &timer);


	/* main game loop: */
	i = 0;
	while (running) {
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
				kill_attacked_enemies(room, sword);

				if (p1.attack_cooldown <= 1) {		
					clear_sword_flag = 2;
								
					free_weapon(sword);
					sword = 0;
				}
			}

			/* Music playing! */


			/*stuff that will go straight into the ISR*/
			if (note_time <= 0) {
				upd_music();
				note_time = melody[note][2];
			}
			else {
			note_time--;
			}
			

			/* Conditional events: */
			if (is_collision_between_player_and_exits(&p1, room)) {
				if (room_number == 5) {
					running = 0;
					game_message((UINT8*)base, "You win!", 220, 300);
					game_message((UINT8*)back, "You win!", 220, 300);
				}
				else {
					room_number++;
					room = change_map(room, room_number);
					rdr_room_flag = 4;
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

			render_frame(back, &p1, room, &timer, sword);

			/* Swap framebuffers: */
			temp = base;
			base = back;
			back = temp;

			Vsync();
			Setscreen(back, back, -1);

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

	disable_interrupts();

	base = (UINT32*)Physbase();
	original = base;
	back = (UINT32*)(((long)my_malloc(32256) + 256) & ~255);	/* Aligning address along 256 bytes */


	for (i = 0; i < 128; i++) {	/* initialize keyboard */
		keyboard[i] = 0x80;
	}

	game_chosen = main_menu();

	if (game_chosen == 0) {
		game();
	}

	enable_interrupts();

	Setscreen(original, original, -1);
	return 0;
}