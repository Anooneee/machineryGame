#ifndef ROOM_STRUCTURE_H
#define ROOM_STRUCTURE_H
#include "room_structure.h"
#include "trap.h"
#include "enemy.h"
#include "vertical_environment.h"
#include "horizontal_environment.h"

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

/* NOT DONE AND PROBABLY WILL NOT USE. ONLY FOR TESTING. Example room */
Room create_room_1();

#endif