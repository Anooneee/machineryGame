#include "door.h"

typedef enum {
    VERTICAL,
    HORIZONTAL,
}type;

typedef struct room_door{
    UINT16 x, y;
    int size;           /* if type VERTICAL: grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
    type type;          /* if type HORIZONTAL: grow from left most side. Example at position (5,10) and size 10, end point will be (15,10)*/
}Exit;

Exit create_vertial_exit(UINT16 x, UINT16 y, int size, type type){
    Exit e = {
        .x = x,
        .y = y,
        .size = size,
        .type = type,
    };
    return e;
}