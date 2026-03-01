#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "model.h"
#include "bitmap.h"

/*player related functions*/
/* "Teleport" to end of h_movement. Has no wall or end of screen checks. */
/* direction should be the enum for LEFT and RIGHT for readibility but it can also work with just -1 and 1 */
void give_player_horizontal_velocity(Player *pc, int direction){             
    (*pc).direction = direction;
    (*pc).horizontal_velocity = (*pc).speed * (*pc).direction;
}

/* Very simple "teleport" to end of jump. No roof or end of screen checks*/
void jump_player(Player *pc){ 
    if((*pc).jump_time <= 0){
        (*pc).vertical_velocity = (*pc).jump_strength;
    }
}

/* NOT DONE. Call every movement frame when player is meant to fall. */
void fall_player(Player *pc, int gravity_strength){
    if ((*pc).grounded == FALSE){
        (*pc).vertical_velocity = -gravity_strength;
        
        (*pc).y = (*pc).y + (*pc).vertical_velocity;
    }
}

/* Return a weapon object 16 pixels in front of the player and start cooldown period */
Weapon attack(Player *pc, UINT16 *bitmap){
    if ((*pc).attack_cooldown <= 0){
        (*pc).attack_cooldown = 32;
        return create_weapon((*pc).x + (16 * (*pc).direction), (*pc).y, (*pc).direction, bitmap);
    }
    /* If the attack cooldown is still happening, summon a weapon outside the screen. */
    return create_weapon(640,400,LEFT,bitmap);
}

/* Create player */
Player create_player(int x, int y, UINT16 *bitmap){
    Player p;
    p.x = x;
    p.y = y;
    p.grounded = FALSE;
    p.attack_cooldown = 0;
    p.jump_strength = 64;
    p.jump_time = 0;
    p.horizontal_velocity = 0;
    p.vertical_velocity = 0;
    p.speed = 1;
    p.direction = RIGHT;
    p.HEIGHT = 32;
    p.WIDTH = 16;
    p.bitmap = bitmap;
	return p;
}


/*Player attack related functions*/
Weapon create_weapon(UINT16 x, UINT16 y, int direction, UINT16 *bitmap){
    Weapon w;
    w.x = x;
    w.y = y;
    w.HEIGHT = 32;
    w.WIDTH = 64;
    w.direction = direction;
    w.bitmap = bitmap;

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
    e.vertical_velocity = 0;
    e.grounded = TRUE;
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

/* Example room */
Room create_room_1(){
    Room r1;

    /* Make walls */
    r1.wall_count = 2;
    r1.walls = malloc(r1.wall_count * sizeof(Wall));
    r1.walls[0] = create_wall(10,50,148);
    r1.walls[1] = create_wall(350,50,148);

    /* Make floor or roofs */
    r1.floor_count = 2;
    r1.floors = malloc(r1.floor_count * sizeof(Floor));
    r1.floors[0] = create_floor(10,46,340);
    r1.floors[1] = create_floor(10,198,340);

    /* Make exits */
    r1.exit_count = 2;
    r1.exits = malloc(r1.exit_count * sizeof(Exit));
    r1.exits[0] = create_exit(10,80,50,VERTICAL);
    r1.exits[1] = create_exit(130,198,50,HORIZONTAL);

    /* Make enemies */
    r1.enemy_count = 2;
    r1.enemies = malloc(r1.enemy_count * sizeof(Enemy));
    r1.enemies[0] = create_enemy(100,166,50,150,enemy_bitmap);
    r1.enemies[1] = create_enemy(200,166,250,350,enemy_bitmap);

    /* Make traps */
    r1.trap_count = 2;
    r1.traps = malloc(r1.trap_count * sizeof(Trap));
    r1.traps[0] = create_trap(80,182,trap_bitmap);
    r1.traps[1] = create_trap(300,182,trap_bitmap);

    return r1;
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
	printf("Y: %u\n", (unsigned int)t.y);
}

void print_timer_status(Timer t) {
	printf("Timer: ");
	printf("Seconds: %u ", (unsigned int)t.display_value.sec);
	printf("Minute: %u\n", (unsigned int)t.display_value.min);
}