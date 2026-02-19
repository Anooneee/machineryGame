#include <stdio.h>
#include "trap.h"
#include "enemy.h"
#include "v_envir.h"
#include "h_envir.h"
#include "door.h"

unsigned int test_bitmap_32[32] = {
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,

};
unsigned int test_bitmap_16[16] = {
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
};

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

/* Example room */
Room create_room_1(){
    Room r1;

    /* Make walls */
    r1.wall_count = 2;
    r1.walls = malloc(r1.wall_count * sizeof(Wall));
    r1.walls[0] = create_wall(10,50,150);
    r1.walls[1] = create_wall(350,50,300);

    /* Make floor or roofs */
    r1.floor_count = 2;
    r1.floors = malloc(r1.floor_count * sizeof(Floor));
    r1.floors[0] = create_floor(50,350,150);
    r1.floors[1] = create_floor(50,200,400);

    /* Make exits */
    r1.exit_count = 2;
    r1.exits = malloc(r1.exit_count * sizeof(Exit));
    r1.exits[0] = create_exit(50,350,150,VERTICAL);
    r1.exits[1] = create_exit(50,200,400,HORIZONTAL);

    /* Make enemies */
    r1.enemy_count = 2;
    r1.enemies = malloc(r1.enemy_count * sizeof(Enemy));
    r1.enemies[0] = create_enemy(100,300,50,150,test_bitmap_16);
    r1.enemies[1] = create_enemy(300,200,250,350,test_bitmap_16);

    /* Make traps */
    r1.trap_count = 2;
    r1.traps = malloc(r1.trap_count * sizeof(Trap));
    r1.traps[0] = create_trap(50,330,test_bitmap_16);
    r1.traps[1] = create_trap(300,200,test_bitmap_16);

    return r1;
};

void print_status(Room r){
    printf("Enemy count %d", r.enemy_count);

};