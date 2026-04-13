#include <osbind.h>
#include <stdio.h>
#include "main.h"

#define VBL_ISR 28

UINT32* base;
UINT32* back;
UINT32* temp;
UINT32* original;

long *timer = (long*) 0x462;
long current_time = 0;
int note = 0;
int render_req = 0;
int rdr_room_flag = 0;
int vbl_ticks = 0;
int rdr_timer_flag = 0;
int rdr_sword_flag = 0;
int clear_sword_flag = 0;
int game_done = 0;
int win_lose = 0;
int next_rm = 0;
int room_number = 0;
int upd_timer = 0;

extern void vbl_isr();

Player* g_active_player = NULL;
Room* g_active_room = NULL;


static UINT8 screen[32256];

char keyboard[128];		/* Stores the state of every key on the board. 0 = pressed, 1 = not pressed. */

extern void vbl_isr();

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

	
	Room* room = 0;

	int i;
	int ticks = 0;
	int running = 1; /* 1 if the game is running, 0 if not */
	long time_then;
	int current_note = 0;
	int note_time;
	room_number = 1;

	/* Program */
	
	timer = create_timer();
	room = change_map(room, room_number);
	p1 = create_player(room->start_x,room->start_y,player_bitmap);
	sword = 0;

	g_active_player = &p1;
	g_active_room = room;

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
		
			

			
			/* synchronous events: */
			

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

			
	
			if (is_collision_between_player_and_exits(g_active_player, g_active_room)){
				next_rm = 1;
			}

			if (is_player_dead(room, &p1)) {
				end_game();
			}
			if (upd_timer == 1){
				update_timer(&timer);
		    	upd_timer = 0;
			}
		}
		
			update_model();

			/* Rendering portion: */
			if(render_req = 1){
				oldX = p1.x;
				oldY = p1.y;
				render_frame(back, &p1, room, &timer, sword);
				/* set_video_base(); */
				temp = base;
				base = back;
				back = temp;
				Vsync();
				Setscreen(back, back, -1);
				/* Clear the screen around movable entites: */
				clear_player(back, &p1, oldX, oldY);
				clear_enemies(back, room);
				render_req = 0;
			}
	

	return 0;
}

void update_model(){
	if (game_done == 0){
		move_player_vert(g_active_player, g_active_room);
		move_player_horiz(g_active_player, g_active_room);
		move_enemies_horiz(g_active_room);
		decrement_cooldown(g_active_player);
		update_player_grounded(g_active_player, is_collision_between_player_and_floor(g_active_player, g_active_room));
		if(next_rm == 1){
			next_room(room_number);
			next_rm = 0;
		}
	}
}

int main() {
	int i;
	int game_chosen = 0;
	Vector orig_VBL;

	install_vectors();

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
	uninstall_vectors();
	return 0;
}