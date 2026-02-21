#include <stdio.h>
#include "player.h"
#include "room.h"
#include "timer.h"
#include "TYPES.H"

int main(){
    Room r;
    Player p;
    Timer t;
    Weapon w;

    r = create_room_1();
    p = create_player(100,100, test_bitmap_32);
    t = create_timer();

    printf("\n-------- Player routines:\n");
    print_player_status(p);
    move_player_h(&p, LEFT);
    jump_player(&p);
    printf("After move LEFT and Jump\n");
    print_player_status(p);
    fall_player(&p, 3);
    w = attack(&p, test_bitmap_16);
    print_player_status(p);
    print_weapon_status(w);
    printf("After attack and fall\n");

    printf("\n-------- Timer routines:\n");
    print_timer_status(t);
    update_timer(&t);
    print_timer_status(t);
    update_timer(&t);
    print_timer_status(t);
    update_timer(&t);
    print_timer_status(t);
    
    printf("\n-------- Room routines:\n");
    print_room_status(r);
    printf("\n-------- Enemy movement:\n");
    if(r.enemy_count>0){
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
        move_enemy(&r.enemies[0],1);
        print_enemy_status(r.enemies[0]);
    }
    printf("Hello World!\n");
    return 0;
};