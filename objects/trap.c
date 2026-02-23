#include "trap.h"
#include "TYPES.H"    /* for boolean values and UINT */
#include <stdio.h>

void print_trap_status(Trap t){
    printf("X:%d, Y:%d, HEIGHT:%d, WIDTH:%d.\n", t.x,t.y,t.HEIGHT,t.WIDTH);
};

Trap create_trap(UINT16 x, UINT16 y, UINT16 *bitmap){
    Trap t;
    t.x = x;
    t.y = y;
    t.HEIGHT = 16;
    t.WIDTH = 16;
    t.bitmap = bitmap;
    return t;
};
