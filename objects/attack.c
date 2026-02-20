#include "attack.h"
#include "TYPES.H"    /* for boolean values and UINT and LEFT and RIGHT */
#include <stdio.h>

void print_weapon_status(Weapon w){
    printf("X:%d, Y:%d, Direction:%d, Height:%d, Width:%d.\n", w.x,w.y,w.direction,w.HEIGHT,w.WIDTH);
};

Weapon create_weapon(UINT16 x, UINT16 y, int direction, UINT16 *bitmap){
    Weapon w;
    w.x = x;
    w.y = y;
    w.HEIGHT = 32;
    w.WIDTH = 64;
    w.direction = direction;
    w.bitmap = bitmap;
};
