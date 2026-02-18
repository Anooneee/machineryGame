#include "enemy.h"
#include "TYPES.H"    /* for boolean values and UINT */

typedef struct Enemy{               /* type definition for enemy object */
    UINT16 x, y;                    /* position coordinates */
    int horizontal_velocity;
    /* Maybe delete these */
    int vertical_velocity;
    bool grounded;
    bool dead;
    /* Maybe delete above? */
    int HEIGHT, WIDTH;              /* 32, 16 */
    UINT16 bound_left, bound_right;
    UINT16 *bitmap;

} Enemy;

/* Move enemy within bounds. One step forward. */
void move_enemy(Enemy *e, int speed){
    (*e).horizontal_velocity = speed;
    if((*e).x + (*e).horizontal_velocity > (*e).bound_right & (*e).x + (*e).horizontal_velocity < (*e).bound_left){
        speed = speed * (-1);
    }
    (*e).x = (*e).x + (*e).horizontal_velocity;
}

/* Create enemy at x,y with bound positions at x = bound left and x = bound right */
Enemy create_enemy(UINT16 x, UINT16 y, UINT16 bound_left, UINT16 bound_right, UINT16 *bitmap){
    Enemy e = {
        .x = x,
        .y = y,
        .bound_left = bound_left,
        .bound_right = bound_right,
        .HEIGHT = 32,
        .WIDTH = 16,
        .horizontal_velocity = 0,
        .vertical_velocity = 0,
        .grounded = TRUE,
        .dead = FALSE,
        .bitmap = bitmap,
    };
    return e;
}
