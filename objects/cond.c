#include "cond.h"
#include "TYPES.H"
#include "player.h"
#include "room.h"

bool is_collision_between_player_and_enemy(Player p, Enemy e){
    bool is_hit = FALSE;
    if ((p.x <= e.x + e.WIDTH && p.x + p.WIDTH >= e.x) &&   /* FIND IF p X IS WITHIN e X */
        (p.y <= e.y + e.HEIGHT && p.y + p.HEIGHT >= e.y) ){ /* FIND IF p Y IS WITHIN e Y */
        is_hit = TRUE;
    }
    return is_hit;
};

bool is_collision_between_player_and_trap(Player p, Trap t){
    bool is_hit = FALSE;
    if ((p.x <= t.x + t.WIDTH && p.x + p.WIDTH >= t.x) &&   /* FIND IF p X IS WITHIN t X */
        (p.y <= t.y + t.HEIGHT && p.y + p.HEIGHT >= t.y) ){ /* FIND IF p Y IS WITHIN t Y */
        is_hit = TRUE;
    }
    return is_hit;
};

bool is_collision_between_player_and_wall(Player p, Wall line){
    bool is_hit = FALSE;
    if ((p.x <= line.x && p.x + p.WIDTH >= line.x) && 
        (p.y >= line.y && p.y + p.HEIGHT <= line.y + line.size)){
            is_hit = TRUE;
    }
    return is_hit;
};

bool is_collision_between_player_and_floor_and_grounded(Player *p, Floor line){
    bool is_hit = FALSE;
    if (((*p).x + (*p).WIDTH >= line.x && (*p).x <= line.x + line.size) && 
        ((*p).y <= line.y && (*p).y + (*p).HEIGHT >= line.y)){ 
            is_hit = TRUE;
    }
    /* Player is grounded if floor is 1 pix below them */
    if (((*p).x + (*p).WIDTH >= line.x && (*p).x <= line.x + line.size) && 
        ((*p).y + (*p).HEIGHT == line.y + 1)){ 
            (*p).grounded = TRUE;
    }
    return is_hit;
};

bool is_collision_between_sword_and_enemy(Weapon w, Enemy e){
    bool is_hit = FALSE;
    if ((w.x <= e.x + e.WIDTH && w.x + w.WIDTH >= e.x) &&   /* FIND IF w X IS WITHIN e X */
        (w.y <= e.y + e.HEIGHT && w.y + w.HEIGHT >= e.y) ){ /* FIND IF w Y IS WITHIN e Y */
        is_hit = TRUE;
    }
    return is_hit;
};

bool is_collision_between_player_and_door(Player p, Exit d){
    bool is_hit = FALSE;

    if (d.type == VERTICAL){
        if ((p.x <= d.x && p.x + p.WIDTH >= d.x) && (p.y >= d.y && p.y+p.HEIGHT <= d.y + d.size)){
            is_hit = TRUE;
        }
    }
    
    if(d.type == HORIZONTAL){
        if((p.x+p.WIDTH >= d.x && p.x <= d.x+d.size) && (p.y <= d.y && p.y+p.HEIGHT >= d.y)){
            is_hit = TRUE;
        }
    }

    return is_hit;
}

/* ONLY FOR ORGANIZTION HERE ---- MOVE EACH TEST TO APPROITATE PLACES WHEN DONE  */
int test_collisions(Player *p, Room r){
    int i;
    Weapon w; /* WHEN YA MOVE TESTS TO APPORIANTE PLACES, WILL HAVE ACCESSS TO REAL WEAPON*/

    /* MOVE TO TEST WHENEVER ENEMY MOVES (EVERY SECOND)*/
    for (i=0; i < r.enemy_count; i++){ /* Loop every enemy in the room and test collision with the player */
        if (is_collision_between_player_and_enemy(*p , r.enemies[i]) == TRUE){
            return 1;
            /* KILL YOURSELF */
        }
    }

    /* MOVE TO TEST WHENEVER PLAYER MOVES */
    for (i=0; i < r.wall_count; i++){ /* Loop every wall in the room and test collision with the player */
        if (is_collision_between_player_and_wall(*p , r.walls[i]) == TRUE){
            (*p).horizontal_velocity = 0;
        }
    }
    
    for (i=0; i < r.floor_count; i++){ /* Loop every floor in the room and test collision with the player */
        if (is_collision_between_player_and_floor_and_grounded(p , r.floors[i]) == TRUE){ /* Pass pointer to player so collsion tester can change the grounded flag if needed */
            (*p).vertical_velocity = 0;
        }
        else{
            if ((*p).grounded == FALSE){
                fall_player(p,3);
            }
        }
    }
    
    for (i=0; i < r.exit_count; i++){ /* Loop every exit in the room and test collision with the player */
        if (is_collision_between_player_and_door(*p, r.exits[i]) == TRUE){
            return 1;
            /* SWITCH ROOMS */
        }
    }

    for (i=0; i < r.trap_count; i++){ /* Loop every trap in the room and test collision with the player */
        if (is_collision_between_player_and_trap(*p , r.traps[i]) == TRUE){
            return 1;
            /* KILL YOURSELF */
        }
    }

    /* MOVE TO TEST WHENEVER WEAPON IS SUMMONED THEN EVERY ENEMY MOVEMENT (SECOND) UNTIL SWORD DISAPPEARS */
    for (i=0; i < r.enemy_count; i++){ /* Loop every enemy in the room and test collision with the weapon */
        if (is_collision_between_sword_and_enemy(w , r.enemies[i]) == TRUE){
            return 1;
            /* KILL THE ENEMY */
        }
    }

    return 0;
};


/*
Collison box calculations: peudocode cuz meyh brain hurt

Hitbox vs point
Box(x, y, size, direction)

If direction VERTICAL:
    // Hitbox == (x,y to y + size)
    so if(point.x == line.x && (point.y > line.y && point.y < line.y + size))
            hit! = true;
    }

If direction HORIZONTAL:
    if(point.y == line.y && (point.x > line.x && point.x < line.x + size))
            hit! = true;
    }

Box(x, y, HEIGTH, WIDTH)
// Hitbox == (x,y to x+WIDTH,y+HEIGHT)
    if (point.x > box.x && point.x < box.x+WIDTH) && (point.y > box.y && point.y < box.y+HEIGTH)

*/

/*
Hitbox vs hitbox

If direction VERTICAL:
    so if((object.x <= line.x && object.x+WIDTH >= line.x) && 
        (object.y >= line.y && object.y+HEIGHT <= line.y + size))
            hit! = true;
    }

If direction HORIZONTAL:
    so if((object.x+WIDTH >= line.x && object.x <= line.x+size) && 
        (object.y <= line.y && object.y+HEIGHT >= line.y))
            hit! = true;
    }

Box(x, y, HEIGTH, WIDTH)
// Hitbox == (x,y to x+WIDTH,y+HEIGHT) vs Hitbox2
    if ((object.x <= box.x + box.WIDTH && object.x + object.WIDTH >= box.x) && // FIND IF OBJECT X IS WITHIN BOX X
        (object.y <= box.y + box.HEIGHT && object.y + object.HEIGHT >= box.y) // FIND IF OBJECT Y IS WITHIN BOX Y
    ) 


*/
