#ifndef MODEL_H
#define MODEL_H

#include "types.h"

typedef enum {
    VERTICAL,
    HORIZONTAL
};

typedef struct Player_character{     /* type definition for player object */
    UINT16 x, y;                     /* position coordinates */
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    int vertical_velocity;              /* vert . displacement per clock tick*/
    int jump_strength;
    int jump_time;
    int speed;
    int direction;
    BOOL grounded;
    int attack_cooldown;
    int HEIGHT, WIDTH;            /* 32, 16 */
    UINT16 *bitmap;
} Player;

typedef struct {
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int direction;
    bool active;
    UINT16 *bitmap;
} Weapon;

typedef struct {
    UINT16 x, y;
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    /* Maybe delete */
    int vertical_velocity; 
    bool grounded;
    bool dead;
    /* Maybe delete */
    int HEIGHT, WIDTH;            /* 32, 16 */
    int direction;
    UINT16 bound_left, bound_right;
    UINT16 *bitmap;
} Enemy;

typedef struct environmental_hazard{
    UINT16 x, y;
    int HEIGHT, WIDTH;
    UINT16 *bitmap;
} Trap;

typedef struct room_door{
    UINT16 x, y;
    int size;           /* if type VERTICAL: grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
    int type;          /* if type HORIZONTAL: grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Exit;

typedef struct horizontal_environment{
    UINT16 x, y;
    int size; /* grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Floor;

typedef struct vertical_environment{
    UINT16 x, y;
    int size; /* grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
}Wall;

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
}Room;

typedef struct display_string{
    int min;
    char colon;
    int sec;
} Display;

typedef struct timer_display{
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int time_passed;
    Display display_value;
} Timer;

/* Create player with all default values at position x,y and pointer to bitmap */
Player create_player(int x, int y, UINT16 *bitmap);

void give_player_horizontal_velocity(Player *pc, int direction);

void move_enemy(Enemy *e);

Weapon create_weapon(UINT16 x, UINT16 y, int direction, UINT16 *bitmap);

Exit create_exit(UINT16 x, UINT16 y, int size, int type);

Trap create_trap(UINT16 x, UINT16 y, UINT16 *bitmap);

Wall create_wall(UINT16 x, UINT16 y, int size);

Floor create_floor(UINT16 x,UINT16 y,int size);

/* Create enemy at x,y with bound positions at x = bound left and x = bound right */
Enemy create_enemy(UINT16 x, UINT16 y, UINT16 bound_left, UINT16 bound_right, UINT16 *bitmap);

/* DO NOT USE THIS */
Room create_room_1();

void jump_player(Player *pc);

void fall_player(Player *pc, int gravity_strength);

Weapon attack(Player *pc, UINT16 *bitmap);

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

/*

Room ROOM_ONE = {
    ROOM_ONE.wall_count = 2;
    ROOM_ONE.walls[0] = create_wall(10,50,148);
    ROOM_ONE.walls[1] = create_wall(350,50,148);

    /* Make floor or roofs *//*
    ROOM_ONE.floor_count = 2;
    ROOM_ONE.floors[0] = create_floor(10,46,340);
    ROOM_ONE.floors[1] = create_floor(10,198,340);

    /* Make exits *//*
    ROOM_ONE.exit_count = 2;
    ROOM_ONE.exits[0] = create_exit(10,80,50,VERTICAL);
    ROOM_ONE.exits[1] = create_exit(130,198,50,HORIZONTAL);

    /* Make enemies *//*
    ROOM_ONE.enemy_count = 2;
    ROOM_ONE.enemies[0] = create_enemy(100,166,50,150,enemy_bitmap);
    ROOM_ONE.enemies[1] = create_enemy(200,166,250,350,enemy_bitmap);

    /* Make traps *//*
    ROOM_ONE.trap_count = 2;
    ROOM_ONE.traps[0] = create_trap(80,182,trap_bitmap);
    ROOM_ONE.traps[1] = create_trap(300,182,trap_bitmap);
}
*/






#endif

