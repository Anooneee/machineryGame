#ifndef ROOM_H
#define ROOM_H
#include "room.h"
#include "trap.h"
#include "enemy.h"
#include "h_environment.h"
#include "v_environment.h"

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

/* NOT DONE AND WILL NOT USE. ONLY FOR TESTING. Example room */
Room create_room1();

#endif