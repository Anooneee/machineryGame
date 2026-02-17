#ifndef TRAP_H
#define TRAP_H

typedef struct environmental_hazard{
    int x, y;
    int height, width;
    unsigned int bitmap[];
} Trap;

#endif 