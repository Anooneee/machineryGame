#include "attack.h"
#include "TYPES.H"    /* for boolean values and UINT and LEFT and RIGHT */

typedef struct {
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int direction;
    UINT16 *bitmap;
} Weapon;

Weapon create_weapon(UINT16 x, UINT16 y, int direction, UINT16 *bitmap){
    Weapon w = {
        .x = x,
        .y = y,
        .HEIGHT = 32,
        .WIDTH = 64,
        .direction = direction,
        .bitmap = bitmap,
    };
};
