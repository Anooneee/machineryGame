#ifndef ENEMY_H
#define ENEMY_H
#include <stdbool.h>    /* for boolean values */


typedef struct Enemy{
    unsigned int x, y;
    int horizontal_velocity;            /* horiz . displacement per clock tick */
    int vertical_velocity;              /* vert . displacement per clock tick*/
    bool grounded;
    int HEIGHT, WIDTH;            /* 16, 16 */
    bool dead;
    int bound_left;
    int bound_right;
    unsigned int *bitmap;

} Enemy;

/* To move enemy within bounds. One step forward. */
void move_enemy(Enemy *e, int speed);

#endif