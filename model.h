#ifndef MODEL_H
#define MODEL_H

#include "types.h"

typedef enum {
    VERTICAL,
    HORIZONTAL,
};

typedef struct Player_character{     /* type definition for player object */
    UINT16 x, y;                     /* position coordinates */
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    int vertical_velocity;              /* vert . displacement per clock tick*/
    int jump_strength;
    int speed;
    int direction;
    BOOL grounded;
    int attack_cooldown;
    int HEIGHT, WIDTH;            /* 32, 16 */
    UINT32 *bitmap;
} Player;

typedef struct {
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int direction;
    UINT16 *bitmap;
} Weapon;

typedef struct room_door{
    UINT16 x, y;
    int size;           /* if type VERTICAL: grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
    int type;          /* if type HORIZONTAL: grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Exit;

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

typedef struct {
    UINT16 x, y;
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    /* Maybe delete */
    int vertical_velocity; 
    bool grounded;
    bool dead;
    /* Maybe delete */
    int HEIGHT, WIDTH;            /* 32, 16 */
    UINT16 bound_left, bound_right;
    UINT16 *bitmap;
} Enemy;

typedef struct horizontal_environment{
    UINT16 x, y;
    int size; /* grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Floor;

typedef struct vertical_environment{
    UINT16 x, y;
    int size; /* grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
}Wall;

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

typedef struct environmental_hazard{
    UINT16 x, y;
    int HEIGHT, WIDTH;
    UINT16 *bitmap;
} Trap;

/* Create player with all default values at position x,y and pointer to bitmap */
Player create_player(int x, int y, UINT32 *bitmap);

Weapon create_weapon(UINT16 x, UINT16 y, int direction, UINT16 *bitmap);

Exit create_exit(UINT16 x, UINT16 y, int size, int type);

Trap create_trap(UINT16 x, UINT16 y, UINT16 *bitmap);

Wall create_wall(UINT16 x, UINT16 y, int size);

Floor create_floor(UINT16 x,UINT16 y,int size);

/* Create enemy at x,y with bound positions at x = bound left and x = bound right */
Enemy create_enemy(UINT16 x, UINT16 y, UINT16 bound_left, UINT16 bound_right, UINT16 *bitmap);



void jump_player(Player *pc);

void fall_player(Player *pc, int gravity_strength);

Weapon attack(Player *pc, UINT16 *bitmap);


/* Call every second that passes. Calls update_display when done */
void update_timer(Timer *t);

/* NOT DONE. Draw with font the display value */
void update_display(Timer *t);

/* Call to return timer */
Timer create_timer();


#endif

