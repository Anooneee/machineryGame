#include "events.h"
#include "model.h"
#include "Sfx.h"


/*
Asynchronous (Input) Events
*/

/* This is lame and kinda useless function we should get rid of. I only put it here to finish the inputs but it redunant*/
Weapon* user_input_x(Player *p){
	return attack(p);
}

void user_input_space(Player *p){
    if((*p).grounded == TRUE){
        give_player_jump_time(p, 60);
        (*p).grounded == FALSE;
    }
}

void user_input_d(Player *p){
    give_player_horizontal_velocity(p,RIGHT);
}

void user_input_a(Player *p){
    give_player_horizontal_velocity(p,LEFT);
}

void user_release_d_or_a(Player *p){
    (*p).horizontal_velocity = 0;
}

void user_input_ESC(){
    return; /* Quit the program */
}

/*conditional*/

bool is_collision_between_player_and_enemy(Player* p, Enemy* e){
    bool is_hit = FALSE;
    if ((p->x <= e->x + e->WIDTH && p->x + p->WIDTH >= e->x) &&   /* FIND IF p X IS WITHIN e X */
        (p->y <= e->y + e->HEIGHT && p->y + p->HEIGHT >= e->y) ){ /* FIND IF p Y IS WITHIN e Y */
        is_hit = TRUE;
    }
    return is_hit;
}

bool is_collision_between_player_and_trap(Player* p, Trap* t){
    bool is_hit = FALSE;
    if ((p->x <= t->x + t->WIDTH && p->x + p->WIDTH >= t->x) &&   /* FIND IF p X IS WITHIN t X */
        (p->y <= t->y + t->HEIGHT && p->y + p->HEIGHT >= t->y) ){ /* FIND IF p Y IS WITHIN t Y */
        is_hit = TRUE;
    }
    return is_hit;
}

bool is_collision_between_player_and_wall(Player* p, Room* r) {
	int i;
	Wall* w;
	int next_x = p->x + p->horizontal_velocity;

	for (i = 0; i < r->wall_count; i++) {
		w = &(r->walls[i]);

		if ((next_x <= (w->x + 8) && (next_x + p->WIDTH) >= w->x) && (p->y <= (w->y + w->size) && (p->y+p->HEIGHT) >= w->y)){
			return TRUE;
		}
	}
	return FALSE;
}

bool is_collision_between_player_and_floor(Player *p, Room *r) {
	int i;

	for (i = 0; i < r->floor_count; i++) {
		if (p->y + p->HEIGHT + 1 == r->floors[i].y) {
			if (p->x + p->WIDTH >= r->floors[i].x && p->x <= r->floors[i].x + r->floors[i].size - 1) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

bool is_collision_between_player_and_roof(Player *p, Room *r) {
	int i;

	for (i = 0; i < r->floor_count; i++) {
		if (p->y == r->floors[i].y + 4) {
			if (p->x + p->WIDTH >= r->floors[i].x && p->x <= r->floors[i].x + r->floors[i].size - 1) {
				return TRUE;
			}
		}
	}
	return FALSE;
}


bool is_collision_between_sword_and_enemy(Weapon* w, Enemy* e){
    bool is_hit = FALSE;
    if ((w->x <= e->x + e->WIDTH && w->x + w->WIDTH >= e->x) &&   /* FIND IF w X IS WITHIN e X */
        (w->y <= e->y + e->HEIGHT && w->y + w->HEIGHT >= e->y)){ /* FIND IF w Y IS WITHIN e Y */
        is_hit = TRUE;
    }
    return is_hit;
}

void kill_attacked_enemies(Room* r, Weapon* w) {
	int i;
	Enemy* e;
	
	for (i = 0; i < r->enemy_count; i++) {
		e = &(r->enemies[i]);
		if (is_collision_between_sword_and_enemy(w, e)) {
			e->dead = TRUE;
			sfx_enemy_die();
		}
	}
}

bool is_player_dead(Room* r, Player* p) {
	int i;

	Trap* t;
	Enemy* e;

	for (i = 0; i < r->trap_count; i++) {
		t = &(r->traps[i]);
		if (is_collision_between_player_and_trap(p, t)) {
			return TRUE;
		}
	}

	for (i = 0; i < r->enemy_count; i++) {
		e = &(r->enemies[i]);
		if (!e->dead && is_collision_between_player_and_enemy(p, e)) {
			return TRUE;
		}
	}

	return FALSE;
}

bool is_collision_between_player_and_exits(Player *p, Room *r) {
	int i;
	Exit* d;

	int next_x = p->x + p->horizontal_velocity;

	for (i = 0; i < r->exit_count; i++) {
		d = &(r->exits[i]);

		if (d->type == VERTICAL){
			if ((next_x <= d->x + 8 && next_x + p->WIDTH >= d->x) && (p->y <= d->y + d->size && p->y+p->HEIGHT >= d->y)){
				return TRUE;
			}
		}
		else {
			if((p->x+p->WIDTH >= d->x && p->x <= d->x+d->size) && (p->y <= d->y && p->y+p->HEIGHT + 1 >= d->y)){
				return TRUE;
			}
		}
	}
	return FALSE;
}

void next_room(){
	if(room_number == 5){
		end_game();
		win_lose = 1;
	}
	else{
		room_number++;
		g_active_room = change_map(g_active_room, room_number);
		rdr_room_flag = 4;
		teleport_player(g_active_room->start_x, g_active_room->start_y, g_active_player);
	}	
}

void end_game(){
	game_done = 1;
}

/*Synchronous events*/

void every_second(Timer *t){ /* 70 ticks */
    update_timer(t);
}

void move_player_horiz(Player *p, Room* r) {
	if (!is_collision_between_player_and_wall(p, r)) {
		p->x += p->horizontal_velocity;
	}
}

void move_player_vert(Player *p, Room* r) {
	if (p->jump_time > 0) {
		if (!is_collision_between_player_and_roof(p, r)) {
			jump_player(p);
		}
		else {
			give_player_jump_time(p, 0);
		}
	}
	else {
		fall_player(p, 1);
	}
}

void move_enemies_horiz(Room *r) {
	int i;
	for (i = 0; i < r->enemy_count; i++) {
		move_enemy(&(r->enemies[i]));
	}
}

Room* change_map(Room* r, int room_number) {
	if (r) {
		free_room(r);
	}
	switch (room_number) {
		case 1:
			return create_room_1();
		case 2:
			return create_room_2();
		case 3:
			return create_room_3();
		case 4:
			return create_room_4();
		case 5:
			return create_room_5();
		default:
			return 0;
	}
}