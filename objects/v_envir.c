#include "v_envir.h"
#include <stdio.h>

void print_wall_status(Wall w){
    printf("Wall: X:%d, Y:%d, Size:%d.\n", w.x,w.y,w.size);
};

Wall create_wall(UINT16 x, UINT16 y, int size){
    Wall w;
        w.x = x;
        w.y = y;
        w.size = size;
    return w;
};
