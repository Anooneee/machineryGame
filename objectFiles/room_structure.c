#include "player_character.h"
#include "trap.h"
#include "enemy.h"
#include "vertical_environment.h"
#include "horizontal_environment.h"

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
Room create_room_1(){
    Room r1 = {0};

    /* Make enemies */
    r1.enemy_count = 2;
    r1.enemies = malloc(r1.enemy_count * sizeof(Enemy));
    r1.enemies[0] = create_enemy(100,300,50,150,test_bitmap_16);
    r1.enemies[1] = create_enemy(300,200,250,350,test_bitmap_16);

    /* Make floor or roofs */
    r1.floor_count = 1;
    r1.floors = malloc(r1.floor_count * sizeof(Floor));
    r1.floors[0] = create_floor(50,350,150);
    return r1;
};