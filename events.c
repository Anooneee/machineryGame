#include "events.h"
#include "model.h"


/*
Asynchronous (Input) Events
*/

/* This is lame and kinda useless function we should get rid of. I only put it here to finish the inputs but it redunant*/
void user_input_x(Player *p, Weapon *w, UINT16 *bitmap){
	w = attack(p,bitmap);
}

void user_input_space(Player *p){
    if((*p).grounded == TRUE){
        give_player_jump_time(p, 30);
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

bool is_collision_between_player_and_enemy(Player p, Enemy e){
    bool is_hit = FALSE;
    if ((p.x <= e.x + e.WIDTH && p.x + p.WIDTH >= e.x) &&   /* FIND IF p X IS WITHIN e X */
        (p.y <= e.y + e.HEIGHT && p.y + p.HEIGHT >= e.y) ){ /* FIND IF p Y IS WITHIN e Y */
        is_hit = TRUE;
    }
    return is_hit;
}

bool is_collision_between_player_and_trap(Player p, Trap t){
    bool is_hit = FALSE;
    if ((p.x <= t.x + t.WIDTH && p.x + p.WIDTH >= t.x) &&   /* FIND IF p X IS WITHIN t X */
        (p.y <= t.y + t.HEIGHT && p.y + p.HEIGHT >= t.y) ){ /* FIND IF p Y IS WITHIN t Y */
        is_hit = TRUE;
    }
    return is_hit;
}

bool is_collision_between_player_and_wall(Player p, Wall line){
    bool is_hit = FALSE;
    if ((p.x <= line.x && p.x + p.WIDTH >= line.x) && 
        (p.y >= line.y && p.y + p.HEIGHT <= line.y + line.size)){
            is_hit = TRUE;
    }
    return is_hit;
}

bool is_collision_between_player_and_floor(Player *p, Room *r) {
	int i;

	for (i = 0; i < r->floor_count; i++) {
		if (p->y + p->HEIGHT + 1 == r->floors[i].y) {
			if (p->x + p->WIDTH >= r->floors[i].x && p->x <= r->floors[i].x + r->floors[i].size) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

bool is_collision_between_sword_and_enemy(Weapon w, Enemy e){
    bool is_hit = FALSE;
    if ((w.x <= e.x + e.WIDTH && w.x + w.WIDTH >= e.x) &&   /* FIND IF w X IS WITHIN e X */
        (w.y <= e.y + e.HEIGHT && w.y + w.HEIGHT >= e.y) ){ /* FIND IF w Y IS WITHIN e Y */
        is_hit = TRUE;
    }
    return is_hit;
}

bool is_collision_between_player_and_door(Player p, Exit d){
    bool is_hit = FALSE;

    if (d.type == VERTICAL){
        if ((p.x <= d.x && p.x + p.WIDTH >= d.x) && (p.y >= d.y && p.y+p.HEIGHT <= d.y + d.size)){
            is_hit = TRUE;
        }
    }
    
    if(d.type == HORIZONTAL){
        if((p.x+p.WIDTH >= d.x && p.x <= d.x+d.size) && (p.y <= d.y && p.y+p.HEIGHT >= d.y)){
            is_hit = TRUE;
        }
    }

    return is_hit;
}



/*
Every second:
- Increment Timer (every 70 ticks(frames)?)

Every movement frame (.5 seconds):
- Move player according to horizontal velocity
- Move player according to jump (vertical) velocity
- If player not on ground, make player fall according to vertical velocity
- Move enemy one step forward
- Lower Attack count down (Max is set in attack function)

Every frame: /////// I added these to every movement frame /////////////
- Check if there is a floor under the player. Set grounded value accordingly
- Check if there is a wall in front of the player according to the horizontal velocity. If so, set horizzontal velocity = 0;
*/

void every_second(Timer *t){ /* 70 ticks */
    update_timer(t);
}

void move_player_horiz(Player *p) {
	p->x += p->horizontal_velocity;
}

void move_player_vert(Player *p) {
	if (p->jump_time > 0) {
		p->jump_time--;
		p->vertical_velocity = p->jump_strength;
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

/*
void every_movement_frame(Player *p, Room *r){
    Weapon w;
    Player player_test;
    int i;

    if((*p).horizontal_velocity != 0){
        player_test = *p;
        player_test.x + player_test.horizontal_velocity;
        for (i=0; i < (*r).wall_count; i++){
            if (is_collision_between_player_and_wall(player_test , (*r).walls[i]) == TRUE){
                (*p).horizontal_velocity = 0;
            }
            else{
                (*p).x = (*p).x + (*p).horizontal_velocity;
            }
        }
    }

    player_test = *p;
    player_test.y + player_test.vertical_velocity; 
    for (i=0; i < (*r).floor_count; i++){ 
        if (is_collision_between_player_and_floor(player_test , (*r).floors[i]) == TRUE){ 
            (*p).vertical_velocity = 0;
        } 
        else {
            (*p).y = (*p).y + (*p).vertical_velocity;
        }

        if (((*p).x + (*p).WIDTH >= (*r).floors[i].x && (*p).x <= (*r).floors[i].x + (*r).floors[i].size) && ((*p).y + (*p).HEIGHT == (*r).floors[i].y + 1)) {
            (*p).grounded = TRUE;
        }
        else{
            (*p).grounded = FALSE;
            fall_player(p,3);
        }
    }

    for (i=0; i < (*r).enemy_count; i++){
        move_enemy(&(*r).enemies[i]);
    }

    if((*p).attack_cooldown > 0){
        (*p).attack_cooldown = (*p).attack_cooldown - 5;
    }

    if((*p).vertical_velocity > 0){
        if((*p).jump_time < 30){
            (*p).jump_time = (*p).jump_time + 5;
        }
        else {
            (*p).vertical_velocity = 0;
        }
    }
    else{
        (*p).jump_time = 0;
    }
}*/