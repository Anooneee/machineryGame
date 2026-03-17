#ifndef RENDER_H
#define RENDER_H

#include "types.h"
#include "model.h"

void init_render(UINT32* base);

void clear_player(UINT32* base, Player* p, int x, int y);
void clear_enemies(UINT32* base, Room* room);
void clear_weapon(UINT32* base, Weapon* w);

void render_player(UINT16* base, Player* p);
void render_weapon(UINT32* base, Weapon* w);

void render_enemies(UINT16* base, Room* r);
void render_enemy(UINT16* base, Enemy* e);

void render_trap(UINT16* base, Trap* t);
void render_exit(UINT32* base, Exit* e);
void render_left_wall(UINT8* base, Wall* w);
void render_right_wall(UINT8* base, Wall* w);
void render_floor(UINT32* base, Floor* f);
void render_room(UINT32* base, Room* r);

void render_timer(UINT8* base, Timer* t);

void game_message(UINT8* base, char* message);

#endif