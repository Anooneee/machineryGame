#ifndef ATTACK_H
#define ATTACK_H
#include "TYPES.H"    /* for boolean values and UINT and LEFT and RIGHT */

typedef struct {
    UINT16 x, y;
    int HEIGHT, WIDTH;
    int direction;
    UINT16 *bitmap;
} Weapon;

/* Called by player when you want to attack */
Weapon create_weapon(UINT16 x, UINT16 y, int direction, UINT16 *bitmap);

#endif