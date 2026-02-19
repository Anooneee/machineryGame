#ifndef ROOM_STRUCTURE_H
#define ROOM_STRUCTURE_H
#include "door.h"
#include "trap.h"
#include "enemy.h"
#include "v_envir.h"
#include "h_envir.h"

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

/* NOT DONE AND PROBABLY WILL NOT USE. ONLY FOR TESTING. Example room */
Room create_room_1();

/* printf position of every object in the room */
void print_status(Room r);

#endif