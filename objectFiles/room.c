#include "room.h"
#include "trap.h"
#include "enemy.h"
#include "h_environment.h"
#include "v_environment.h"

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

typedef struct room_structure{
    Trap *traps;
    int trap_count;
    Enemy *enemies;
    int enemy_count;
    Wall *wall;
    int wall_count;
    Floor *floors;   /* Floor is typedef for h_environment which can also be roofs */
    int floor_count;

}Room;

/* Example room */
Room create_room1(){
    Room r1 = {0};

    /* Make enemies */
    r1.enemy_count = 2;
    r1.enemies = malloc(r1.enemy_count * sizeof(Enemy));
    r1.enemies[0] = (Enemy){
        .x=0,
        .y=0,
        .horizontal_velocity=1,
        .vertical_velocity=0,
        .HEIGHT=32,
        .WIDTH=32,
        .grounded=true,
        .dead=false,
        .bound_left=0,
        .bound_right=0,
        .bitmap=test_bitmap_32};

        r1.enemies[1] = (Enemy){
        .x=0,
        .y=0,
        .horizontal_velocity=0,
        .vertical_velocity=0,
        .HEIGHT=32,
        .WIDTH=32,
        .grounded=true,
        .dead=false,
        .bound_left=0,
        .bound_right=0,
        .bitmap=test_bitmap_32};

        /* Make floor or roofs */
        r1.floor_count = 1;
        r1.floors = malloc(r1.floor_count * sizeof(Floor));
        r1.floors[0] = (Floor){
            .x=0, 
            .y=300, 
            .size=100,
        };
        return r1;
};