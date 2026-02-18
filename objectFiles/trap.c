#include "trap.h"
#include "TYPES.H"    /* for boolean values and UINT */

typedef struct environmental_hazard{
    UINT16 x, y;
    int HEIGHT, WIDTH;
    UINT16 *bitmap;
} Trap;

Trap create_trap(UINT16 x, UINT16 y, UINT16 *bitmap){
    Trap t = {
        .x = x,
        .y = y,
        .HEIGHT = 16,
        .WIDTH = 16,
        .bitmap = bitmap,
    };
    return t;
}
