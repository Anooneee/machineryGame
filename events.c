#include "events.h"
#include "TYPES.H"
#include "model.h"

/*
Asynchronous (Input) Events
*/

/* This is lame and kinda useless function we should get rid of. I only put it here to finish the inputs but it redunant*/
Weapon user_input_x(Player *p, UINT16 bitmap){
    Weapon w = attack(p,bitmap); /* Attack still summons a weapon if the cooldown is still going because it crashes if I don't return anything (NULL dont exist). The weapon is spawn at (640,400) thought so it's offscreen */
};

void user_input_space(Player *p, Room r){
    if((*p).grounded == TRUE){
        jump_player(p);
    };
};

void user_input_d(Player *p){
    give_player_horizontal_velocity(p,RIGHT);
};

void user_input_a(Player *p){
    give_player_horizontal_velocity(p,LEFT);
};

void user_release_d_or_a(Player *p){
    (*p).horizontal_velocity = 0;
};

void user_input_ESC(){
    return; /* Quit the program */
};

/*conditional*/

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

/*
bool is_collision_between_player_and_floor_and_grounded(Player *p, Floor line){
    bool is_hit = FALSE;
    if (((*p).x + (*p).WIDTH >= line.x && (*p).x <= line.x + line.size) && 
        ((*p).y <= line.y && (*p).y + (*p).HEIGHT >= line.y)){ 
            is_hit = TRUE;
    }
    /* Player is grounded if floor is 1 pix below them 
    if (((*p).x + (*p).WIDTH >= line.x && (*p).x <= line.x + line.size) && 
        ((*p).y + (*p).HEIGHT == line.y + 1)){ 
            (*p).grounded = TRUE;
    }
    return is_hit;
};*/
bool is_collision_between_player_and_floor(Player p, Floor line){
    bool is_hit = FALSE;
    if ((p.x + p.WIDTH >= line.x && p.x <= line.x + line.size) && 
        (p.y <= line.y && p.y + p.HEIGHT >= line.y)){ 
            is_hit = TRUE;
    };
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
/**/
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
    
    /* I changed the collison between player and floor function but I'm too lazy to fix this. 
        View Synchronous events (Every movement frame()) to see the right collision check*/
    /*
    for (i=0; i < r.floor_count; i++){ /* Loop every floor in the room and test collision with the player /
        if (is_collision_between_player_and_floor_and_grounded(p , r.floors[i]) == TRUE){ /* Pass pointer to player so collsion tester can change the grounded flag if needed /
            (*p).vertical_velocity = 0;
        }
        else{
            if ((*p).grounded == FALSE){
                fall_player(p,3);
            }
        }
    }
    */
    
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


/*
Synchronous (Timed) Events
*/

/*
Every second:
- Increment Timer (every 70 ticks(frames)?)

Every movement frame (.5 seconds):
- Move player according to horizontal velocity
- Move player according to jump (vertical) velocity
- If player not on ground, make player fall according to vertical velocity
- Move enemy one step forward
- Lower Attack count down (Max is set in attack function)

Every frame: /////// I added these to every movement frame /////////////
- Check if there is a floor under the player. Set grounded value accordingly
- Check if there is a wall in front of the player according to the horizontal velocity. If so, set horizzontal velocity = 0;
*/

/* Move the contents to whereever we can calculate the ticks*/
void every_second(Timer *t){ /* 70 ticks */
    update_timer(t);
}

void every_movement_frame(Player *p, Room *r){ /* 35 ticks */
    Weapon w;
    Player player_test;
    int i;

    /* Move player according to horizonal velocity. Check walls*/
    if((*p).horizontal_velocity != 0){
        player_test = *p;
        player_test.x + player_test.horizontal_velocity; /* Give playertest the position real player would have if it moved*/
        for (i=0; i < (*r).wall_count; i++){ /* Loop every wall in the room and test collision with the test player */
            if (is_collision_between_player_and_wall(player_test , (*r).walls[i]) == TRUE){
                (*p).horizontal_velocity = 0;
            }
            else{
                (*p).x = (*p).x + (*p).horizontal_velocity;
            }
        }
    }

    /* Move player according to vertical velocity. Check grounded value and floors/roofs collisions */
    player_test = *p;
    player_test.y + player_test.vertical_velocity; /* Give playertest the position real player would have if it moved*/
    for (i=0; i < (*r).floor_count; i++){ /* Loop every floor in the room and test collision with the player */
        if (is_collision_between_player_and_floor(player_test , (*r).floors[i]) == TRUE){ 
            (*p).vertical_velocity = 0;
        } 
        else {
            (*p).y = (*p).y + (*p).vertical_velocity;
        }

        if (((*p).x + (*p).WIDTH >= (*r).floors[i].x && (*p).x <= (*r).floors[i].x + (*r).floors[i].size) && ((*p).y + (*p).HEIGHT == (*r).floors[i].y + 1)) { /* Player is grounded if floor is 1 pix below them */
            (*p).grounded = TRUE;
        }
        else{
            (*p).grounded = FALSE;
            fall_player(p,3);
        }
    }

    /* Move all enemys in the room */
    for (i=0; i < (*r).enemy_count; i++){
        move_enemy(&(*r).enemies[i]);
    }

    /* Lower attack cooldown */
    if((*p).attack_cooldown > 0){
        (*p).attack_cooldown = (*p).attack_cooldown - 5;
    }
}