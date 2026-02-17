#include "trap.h"

typedef struct environmental_hazard{
    int x, y;
    int height, width;
    unsigned int bitmap[];
} Trap;