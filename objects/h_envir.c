#include "h_envir.h"
#include <stdio.h>

void print_floor_status(Floor f){
    printf("X:%d, Y:%d, Size:%d.\n", f.x,f.y,f.size);
};

Floor create_floor(UINT16 x,UINT16 y,int size){
    Floor f;
    f.x = x;
    f.y = y;
    f.size = size;
    return f;
};