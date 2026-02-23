#ifndef ENEMY_H
#define ENEMY_H
#include "TYPES.H"    /* for boolean values and UINT and LEFT/RIGHT*/

typedef struct {
    UINT16 x, y;
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    /* Maybe delete */
    int vertical_velocity; 
    bool grounded;
    bool dead;
    /* Maybe delete */
    int HEIGHT, WIDTH;            /* 32, 16 */
    UINT16 bound_left, bound_right;
    UINT16 *bitmap;

} Enemy;

/* Move enemy within bounds. One step forward. */
void move_enemy(Enemy *e, int speed);

/* Create enemy at x,y with bound positions at x = bound left and x = bound right */
Enemy create_enemy(UINT16 x, UINT16 y, UINT16 bound_left, UINT16 bound_right, UINT16 *bitmap);

void print_enemy_status(Enemy e);

#endif