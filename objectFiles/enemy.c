#include "enemy.h"
#include <stdbool.h>    /* for boolean values */

typedef struct Enemy{               /* type definition for enemy object */
    unsigned int x, y;                  /* position coordinates */
    int horizontal_velocity;
    /* Maybe delete these */
    int vertical_velocity;
    bool grounded;
    bool dead;
    /* Maybe delete above? */
    int HEIGHT, WIDTH;            /* 32, 16 */
    int bound_left;
    int bound_right;
    unsigned int *bitmap;

} Enemy;

/* To move enemy within bounds. One step forward. */
void move_enemy(Enemy *e, int speed){
    e->horizontal_velocity = speed;
    if(e->x + e->horizontal_velocity > e->bound_right & e->x + e->horizontal_velocity < e->bound_left){
        speed = speed * (-1);
    }
    e->x = e->x + e->horizontal_velocity;
}
