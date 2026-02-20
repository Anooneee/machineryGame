#include "enemy.h"
#include "TYPES.H"    /* for boolean values and UINT */
#include <stdio.h>

void print_enemy_status(Enemy e){
    printf("Enemy: X:%d, Y:%d, Bound_left:%d, Bound_right:%d, HEIGHT:%d, WIDTH:%d, Horizontal_velocity:%d, Vertical_velocity:%d, Grounded:%d, Dead:%d.\n", e.x,e.y,e.bound_left,e.bound_right,e.HEIGHT,e.WIDTH,e.horizontal_velocity,e.vertical_velocity,e.grounded,e.dead);
};

/* Move enemy within bounds. One step forward. */
void move_enemy(Enemy *e, int speed){
    (*e).horizontal_velocity = speed;
    if((*e).x + (*e).horizontal_velocity > (*e).bound_right & (*e).x + (*e).horizontal_velocity < (*e).bound_left){
        speed = speed * (-1);
    }
    (*e).x = (*e).x + (*e).horizontal_velocity;
}

/* Create enemy at x,y with bound positions at x = bound left and x = bound right */
Enemy create_enemy(UINT16 x, UINT16 y, UINT16 bound_left, UINT16 bound_right, UINT16 *bitmap){
    Enemy e;
    e.x = x;
    e.y = y;
    e.bound_left = bound_left;
    e.bound_right = bound_right;
    e.HEIGHT = 32;
    e.WIDTH = 16;
    e.horizontal_velocity = 0;
    e.vertical_velocity = 0;
    e.grounded = TRUE;
    e.dead = FALSE;
    e.bitmap = bitmap;
    return e;
};

/*
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
int main(){
    Enemy e = create_enemy(150,300,100,200,test_bitmap_16);
    print_status(e);
    return 0;
};*/