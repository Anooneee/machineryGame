#ifndef TRAP_H
#define TRAP_H
#include "TYPES.H" /* for bool, UINT and LEFT/RIGHT */

typedef struct environmental_hazard{
    UINT16 x, y;
    int HEIGHT, WIDTH;
    UINT16 *bitmap;
} Trap;

Trap create_trap(UINT16 x, UINT16 y, UINT16 *bitmap);

void print_trap_status(Trap t);

#endif 