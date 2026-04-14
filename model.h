#ifndef MODEL_H
#define MODEL_H

#include "types.h"

/* Used for code readbility in room_door/exit structure */
typedef enum {
    VERTICAL,
    HORIZONTAL
};

/* Structure for the main playable character 
- Position is top-left corner
*/
typedef struct Player_character{    /* type definition for player object */
    UINT16 x, y;                    /* position coordinates */
    int horizontal_velocity;        /* horiz . displacement per clock tick */
    int vertical_velocity;          /* vert . displacement per clock tick*/
    int jump_strength;              /* 1 */
    int jump_time;
    int speed;                      /* 2 */
    int direction;
    BOOL grounded;
    int attack_cooldown;
    int HEIGHT, WIDTH;              /* 32, 16 */
    char image;                     /* For animation tracking */
} Player;

/* Structure for simple weapon
- Considered non-existent if active = FALSE
*/
typedef struct {
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int direction;
    bool active;
    UINT32 *bitmap;
    char justCreated;
} Weapon;

/* Structure for simple enemy 
- Hitbox harms player
- Only moves x-direction within hardcoded bounds
- Considered dead if dead = TRUE
*/
typedef struct {
    UINT16 x, y;
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    bool dead;
    int HEIGHT, WIDTH;            /* 32, 16 */
    int direction;
    UINT16 bound_left, bound_right;
    UINT16 *bitmap;
} Enemy;

/* Spikes that harm the player when they collide */
typedef struct environmental_hazard{
    UINT16 x, y;
    int HEIGHT, WIDTH; /* 16x16 */
    UINT16 *bitmap;
} Trap;

/* Simple door structure 
- In main, triggers room number increase if collides with the player
*/
typedef struct room_door{
    UINT16 x, y;
    int size;           /* if type VERTICAL: grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
    int type;          /* if type HORIZONTAL: grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
		int go_to_room;		/* room counter should change to this when entered */
}Exit;

/* Simple floor or roof structure 
(All roofs can be floors if you try!)
*/
typedef struct horizontal_environment{
    UINT16 x, y;
    int size; /* grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Floor;

/* Simple wall structure */
typedef struct vertical_environment{
    UINT16 x, y;
    int size; /* grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
}Wall;

/* Basic structure to build each room */
typedef struct room_structure{
    Wall *walls;
    int wall_count;
    Floor *floors;   /* Floor is typedef for h_environment which can also be roofs */
    int floor_count;
    Exit *exits;
    int exit_count;
    Enemy *enemies;
    int enemy_count;
    Trap *traps;
    int trap_count;
    int start_x;
    int start_y;
}Room;

/* Properties of the timer */
/* Timer displayed on the screen in format 00:00 */
typedef struct display_string{
    int min;
    char colon;
    int sec;
} Display;

/* Simple timer structure */
typedef struct timer_display{
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int time_passed;
    Display display_value;
} Timer;

/* Create player with all default values at position x,y and pointer to bitmap */
Player create_player(int x, int y);

/* Used to time length of jump. Time is kept track of in events.c */
void give_player_jump_time(Player *pc, int time);

/* "Teleport" to end of h_movement. 
- Has no wall or end of screen checks. 
- Direction should be the enum for LEFT and RIGHT for readibility but it can also work with just -1 and 1 
*/
void give_player_horizontal_velocity(Player *pc, int direction);

/* Update grounded value */
void update_player_grounded(Player *p, bool val);

/* Move player to new x and y locations with no checks */
void teleport_player(int x, int y, Player *p);

/* Lower attack cooldown */
void decrement_cooldown(Player *p);

/* Very simple "teleport" to end of jump.
- Vertical velocity according to jump_strength property
- No roof or end of screen checks*/
void jump_player(Player *pc);

/* Call every frame when player is meant to fall. */
void fall_player(Player *pc, int gravity_strength);

/* Return a weapon object 16 pixels in front of the player and start cooldown period */
Weapon* attack(Player *pc);

/* Move enemy within bounds. 
- One step forward. 
- Direction will be flipped if next step is outside bounds
*/
void move_enemy(Enemy *e);

/* Return pointer to a new weapon structure */
Weapon* create_weapon(UINT16 x, UINT16 y, int direction, UINT32 *bitmap);

/* Create invisible exit door
- Position starts at (x,y) left top corner
- Type (VERTICAL/HORIZONTAL) determines if size will grow down or rightwards */
Exit create_exit(UINT16 x, UINT16 y, int size, int type, int go_to_room);

/* Create simple 16x16 trap
- Postion is top-left corner */
Trap create_trap(UINT16 x, UINT16 y, UINT16 *bitmap);

/* Create simple wall 
- Position starts at (x,y) and ends at (x,y+size) */
Wall create_wall(UINT16 x, UINT16 y, int size);

/* Create simple floor/roof 
- Position starts at (x,y) and ends at (x+size,y) */
Floor create_floor(UINT16 x,UINT16 y,int size);

/* Create enemy at x,y with bound positions at x = bound left and x = bound right */
Enemy create_enemy(UINT16 x, UINT16 y, UINT16 bound_left, UINT16 bound_right, UINT16 *bitmap);

/* Deconstructor for room/room objects */
void free_room(Room* r);
/* Deconstructor for weapon object */
void free_weapon(Weapon* w);

/* Custom rooms */
Room* create_room_1();
Room* create_room_2();
Room* create_room_3();
Room* create_room_4();
Room* create_room_5();

/* Call every second that passes. Calls update_display when done */
void update_timer(Timer *t);

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t);

/* Call to return timer */
Timer create_timer();

/* DEBUG FUNCTIONS: Ran to test statuses */
void print_room_status(Room r);

void print_wall_status(Wall w);

void print_floor_status(Floor f);

void print_exit_status(Exit e);

void print_enemy_status(Enemy e);

void print_trap_status(Trap t);

void print_player_status(Player p);

void print_weapon_status(Weapon p);

void print_timer_status(Timer p);





#endif

