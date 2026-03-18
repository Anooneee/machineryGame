#include <stdio.h>
#include "types.h"
#include "model.h"
#include "bitmap.h"
#include "mem.h"

/*player related functions*/
/* "Teleport" to end of h_movement. Has no wall or end of screen checks. */
/* direction should be the enum for LEFT and RIGHT for readibility but it can also work with just -1 and 1 */
void give_player_horizontal_velocity(Player *pc, int direction){             
    (*pc).direction = direction;
    (*pc).horizontal_velocity = (*pc).speed * (*pc).direction;
}

void give_player_jump_time(Player *pc, int time){             
    (*pc).jump_time = time;
}

void update_player_grounded(Player *p, bool val) {
	p->grounded = val;
}

void teleport_player(int x, int y, Player *p) {
	p->x = x;
	p->y = y;
}

void decrement_cooldown(Player *p) {
	if (p->attack_cooldown > 0) {
		p->attack_cooldown--;
	}
}

/* Very simple "teleport" to end of jump. No roof or end of screen checks*/
void jump_player(Player *pc){ 
    if((*pc).jump_time > 0){
	(*pc).jump_time--;
        (*pc).vertical_velocity = (*pc).jump_strength;

	(*pc).y -= (*pc).vertical_velocity;
    }
}

/* NOT DONE. Call every movement frame when player is meant to fall. */
void fall_player(Player *pc, int gravity_strength){
    if ((*pc).grounded == FALSE){
        (*pc).vertical_velocity = gravity_strength;
        
        (*pc).y = (*pc).y + (*pc).vertical_velocity;
    }
}

/* Return a weapon object 16 pixels in front of the player and start cooldown period */
Weapon* attack(Player *pc) {
    Weapon* w;
	int weaponX = ((*pc).direction == LEFT) ? (*pc).x - 32 : (*pc).x + 16;
	UINT32* bitmap = ((*pc).direction == LEFT) ? weapon_bitmap_left : weapon_bitmap_right;
    if ((*pc).attack_cooldown <= 0) {
        (*pc).attack_cooldown = 32;
        w = create_weapon(weaponX, (*pc).y + 16, (*pc).direction, bitmap);
        w->active = TRUE;
        return w;
    }
    /* If the attack cooldown is still happening, return NULL. */
    return 0;
}


/* Create player */
Player create_player(int x, int y, UINT16 *bitmap){
    Player p;
    p.x = x;
    p.y = y;
    p.grounded = FALSE;
    p.attack_cooldown = 0;
    p.jump_strength = 1;
    p.jump_time = 0;
    p.horizontal_velocity = 0;
    p.vertical_velocity = 0;
    p.speed = 4;
    p.direction = RIGHT;
    p.HEIGHT = 32;
    p.WIDTH = 16;
    p.bitmap = bitmap;
	return p;
}


/*Player attack related functions*/
Weapon* create_weapon(UINT16 x, UINT16 y, int direction, UINT32 *bitmap){
	Weapon* w = my_malloc(sizeof(Weapon));
	w->x = x;
	w->y = y;
	w->active = FALSE;
	w->HEIGHT = 8;
	w->WIDTH = 32;
	w->direction = direction;
	w->bitmap = bitmap;
	return w;
}


/*enemy related functions*/

/* Move enemy within bounds. One step forward. */
void move_enemy(Enemy *e){
    if((*e).x + (*e).horizontal_velocity > (*e).bound_right || (*e).x + (*e).horizontal_velocity < (*e).bound_left){
        (*e).direction = (*e).direction * (-1);
    }
    (*e).x = (*e).x + ((*e).horizontal_velocity * (*e).direction);
}

/* Create enemy at x,y with bound positions at x = bound left and x = bound right */
Enemy create_enemy(UINT16 x, UINT16 y, UINT16 bound_left, UINT16 bound_right, UINT16 *bitmap){
    Enemy e;
    e.x = x;
    e.y = y;
    e.bound_left = bound_left;
    e.bound_right = bound_right;
    e.HEIGHT = 32;
    e.WIDTH = 16;
    e.direction = RIGHT;
    e.horizontal_velocity = 1;
    e.dead = FALSE;
    e.bitmap = bitmap;
    return e;
}


/*floor related functions*/

Floor create_floor(UINT16 x,UINT16 y,int size){
    Floor f;
    f.x = x;
    f.y = y;
    f.size = size;
    return f;
}


/*wall related functions*/

Wall create_wall(UINT16 x, UINT16 y, int size){
    Wall w;
        w.x = x;
        w.y = y;
        w.size = size;
    return w;
}




/*door functions*/

Exit create_exit(UINT16 x, UINT16 y, int size, int type){
    Exit e;
    e.x = x;
    e.y =y;
    e.size = size;
    e.type = type;
    return e;
}



/*trap related functions*/

Trap create_trap(UINT16 x, UINT16 y, UINT16 *bitmap){
    Trap t;
    t.x = x;
    t.y = y;
    t.HEIGHT = 16;
    t.WIDTH = 16;
    t.bitmap = bitmap;
    return t;
}

/*time related functions*/

/* Call every second that passes */
void update_timer(Timer *t){
    (*t).time_passed = (*t).time_passed + 1;
    if((*t).time_passed == 60){
        (*t).display_value.min = (*t).display_value.min + 1;
        (*t).time_passed = 0;
    }
    (*t).display_value.sec = (*t).time_passed;
    /*
    (*t).display_value.min = (*t).time_passed / 60;
    (*t).display_value.sec = (*t).time_passed % 60;
    */
    update_display(t);
}

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t){
    /* Draw with font the display value */
}

/* Create timer duh */
Timer create_timer(){
    Timer t;
    t.HEIGHT = 32;
    t.WIDTH = 64;
    t.time_passed = 0;
    t.x = 0;
    t.y = 0;
    t.display_value.colon = ':';
    t.display_value.min = 0;
    t.display_value.sec = 0;
    return t;
}

/*room functions*/

void free_room(Room* r) {
	my_free(r->walls);
	my_free(r->floors);
	my_free(r->exits);
	my_free(r->enemies);
	my_free(r->traps);

	my_free(r);
	r = 0;
}

void free_weapon(Weapon* w) {
	my_free(w);
}

Room* create_room_1(){
    Room* r = my_malloc(sizeof(Room));

    /* Make walls */
    r->wall_count = 2;
    r->walls = my_malloc(r->wall_count * sizeof(Wall));
    r->walls[0] = create_wall(0,0,300);
    r->walls[1] = create_wall(632,0,300);

    /* Make floor or roofs */
    r->floor_count = 3;
    r->floors = my_malloc(r->floor_count * sizeof(Floor));
    r->floors[0] = create_floor(0,0,640);
    r->floors[1] = create_floor(0,300,640);
    r->floors[2] = create_floor(30,260,20);

    /* Make exits */
    r->exit_count = 1;
    r->exits = my_malloc(r->exit_count * sizeof(Exit));
    r->exits[0] = create_exit(632,250,50,VERTICAL);

    /* Make enemies */
    r->enemy_count = 2;
    r->enemies = my_malloc(r->enemy_count * sizeof(Enemy));
    r->enemies[0] = create_enemy(200,267,180,220,enemy_bitmap);
    r->enemies[1] = create_enemy(400,267,380,420,enemy_bitmap);

    /* Make traps */
    r->trap_count = 2;
    r->traps = my_malloc(r->trap_count * sizeof(Trap));
    r->traps[0] = create_trap(110,283,trap_bitmap);
    r->traps[1] = create_trap(450,283,trap_bitmap);

    return r;
}

Room* create_room_2(){
	return create_room_1();
}

Room* create_room_3(){
	return create_room_1();
}

Room* create_room_4(){
	return create_room_1();
}

Room* create_room_5(){
	return create_room_1();
}



/* Use print_object_status routines for each object in the room, up to 3 of each kind. */
void print_room_status(Room r){
	int i;

    printf("Room:\n");
	for (i = 0; i < r.wall_count && i < 3; i++) {
		print_wall_status(r.walls[i]);
	}
	for (i = 0; i < r.floor_count && i < 3; i++) {
		print_floor_status(r.floors[i]);
	}
	for (i = 0; i < r.exit_count && i < 3; i++) {
		print_exit_status(r.exits[i]);
	}
	for (i = 0; i < r.enemy_count && i < 3; i++) {
		print_enemy_status(r.enemies[i]);
	}
	for (i = 0; i < r.trap_count && i < 3; i++) {
		print_trap_status(r.traps[i]);
	}
}

void print_wall_status(Wall t) {
	printf("Wall: ");
	printf("X: %u ", (unsigned int)t.x);
	printf("Y: %u\n", (unsigned int)t.y);
}

void print_floor_status(Floor t) {
	printf("Floor: ");
	printf("X: %u ", (unsigned int)t.x);
	printf("Y: %u\n", (unsigned int)t.y);
}

void print_exit_status(Exit t) {
	printf("Exit: ");
	printf("X: %u ", (unsigned int)t.x);
	printf("Y: %u\n", (unsigned int)t.y);
}

void print_enemy_status(Enemy t) {
	printf("Enemy: ");
	printf("X: %u ", (unsigned int)t.x);
	printf("Y: %u\n", (unsigned int)t.y);
}

void print_trap_status(Trap t) {
	printf("Trap: ");
	printf("X: %u ", (unsigned int)t.x);
	printf("Y: %u\n", (unsigned int)t.y);
}

void print_player_status(Player t) {
	printf("Player: ");
	printf("X: %u ", (unsigned int)t.x);
	printf("Y: %u\n", (unsigned int)t.y);
}

void print_weapon_status(Weapon t) {
	printf("Weapon: ");
	printf("X: %u ", (unsigned int)t.x);
	printf("Y: %u", (unsigned int)t.y);
	printf("Active: %u\n", (bool) t.active);
}

void print_timer_status(Timer t) {
	printf("Timer: ");
	printf("Seconds: %u ", (unsigned int)t.display_value.sec);
	printf("Minute: %u\n", (unsigned int)t.display_value.min);
}