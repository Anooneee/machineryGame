#ifndef HORIZONTAL_ENVIRONMENT_H
#define HORIZONTAL_ENVIRONMENT_H
#include "TYPES.H" /* for bool, UINT and LEFT/RIGHT */

typedef struct horizontal_environment{
    UINT16 x, y;
    int size; /* grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Floor;

Floor create_floor(UINT16 x,UINT16 y,int size);

void print_floor_status(Floor f);
#endif