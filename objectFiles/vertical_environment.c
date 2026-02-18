#include "vertical_environment.h"

typedef struct vertical_environment{
    UINT16 x, y;
    int size; /* grow from top most side. Example at position (5,10) and size 10, end point will be (5,20)*/
}Wall;

Wall create_wall(UINT16 x, UINT16 y, int size){
    Wall w = {
        .x = x,
        .y = y,
        .size = size
    };
    return w;
};
