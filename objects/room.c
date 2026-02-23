#include <stdio.h>
#include <stdlib.h>
#include "room.h"

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

/* Use print_object_status routines for each object in the room, up to 3 of each kind. */
void print_room_status(Room r){
    printf("Room:\n");
    if(r.wall_count > 0){
        print_wall_status(r.walls[0]);
    }
    if(r.wall_count > 1){
        print_wall_status(r.walls[1]);
    }
    if(r.wall_count > 2){
        print_wall_status(r.walls[2]);
    }
    if(r.floor_count > 0){
        print_floor_status(r.floors[0]);
    }
    if(r.floor_count > 1){
        print_floor_status(r.floors[1]);
    }
    if(r.floor_count > 2){
        print_floor_status(r.floors[2]);
    }
    if(r.exit_count > 0){
        print_exit_status(r.exits[0]);
    }
    if(r.exit_count > 1){
        print_exit_status(r.exits[1]);
    }
    if(r.exit_count > 2){
        print_exit_status(r.exits[2]);
    }
    if(r.enemy_count > 0){
        print_enemy_status(r.enemies[0]);
    }
    if(r.enemy_count > 1){
        print_enemy_status(r.enemies[1]);
    }
    if(r.enemy_count > 2){
        print_enemy_status(r.enemies[2]);
    }
    if(r.trap_count > 0){
        print_trap_status(r.traps[0]);
    }
    if(r.trap_count > 1){
        print_trap_status(r.traps[1]);
    }
    if(r.trap_count > 2){
        print_trap_status(r.traps[2]);
    }
};