#include <stdio.h>
#include "player.h"
#include "room.h"

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
int main(){
    Room r;
    Player p;

    r = create_room_1();
    p = create_player(100,100, test_bitmap_32);
    print_room_status(r);
    print_player_status(p);

    

    printf("Hello World!\n");
    return 0;
};