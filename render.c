#include "types.h"
#include "bitmap.h"
#include "raster.h"
#include "model.h"
#include "render.h"

void init_render(UINT32* base) {
	clear_screen(base);
}

void clear_player(UINT32* base, Player* p, int x, int y) {
	clear_region(base, y, x, p->HEIGHT, p->WIDTH);
}

void clear_enemies(UINT32* base, Room* room) {
	int i;
	Enemy current;
	for (i = 0; i < room->enemy_count; i++) {
		current = room->enemies[i];
		clear_region(base, current.y, current.bound_left - 2, current.HEIGHT, (current.bound_right + current.WIDTH + 2) - current.bound_left);
	}
}

void clear_weapon(UINT32* base, Weapon* w) {
	clear_region(base, w->y, w->x, w->HEIGHT, w->WIDTH);
}

void render_player(UINT16* base, Player* p) {
	plot_16bit_bitmap(base, p->y, p->x, p->bitmap, p->HEIGHT);
}

void render_weapon(UINT32* base, Weapon* w) {
	plot_32bit_bitmap(base, w->y, w->x, w->bitmap, w->HEIGHT);
}

void render_enemies(UINT16* base, Room* r) {
	int i;

	for (i = 0; i < r->enemy_count; i++) {
		if (!r->enemies[i].dead) {
			render_enemy(base, &r->enemies[i]);
		}
	}
}

void render_enemy(UINT16* base, Enemy* e) {
	plot_16bit_bitmap(base, e->y, e->x, e->bitmap, e->HEIGHT);
}

void render_trap(UINT16* base, Trap* t) {
	plot_16bit_bitmap(base, t->y, t->x, t->bitmap, t->HEIGHT);
}

void render_exit(UINT32* base, Exit* e) {
	if (e->type == VERTICAL) {
		clear_region(base, e->y, e->x, e->size, 8);
	}
	else {
		clear_region(base, e->y, e->x, 4, e->size);
	}
}

void render_floor(UINT32* base, Floor* f) {
	int i;
	for (i = 0; i < f->size; i += 32) {
		plot_32bit_bitmap(base, f->y, f->x + i, floor_bitmap, 4);
	}
}

void render_left_wall(UINT8* base, Wall* w) {
	int i;
	for (i = 0; i < (w->size - 32); i += 32) {
		plot_8bit_bitmap(base, w->y + i, w->x, wall_L_bitmap, 32);
	}
	plot_8bit_bitmap(base, w->y + i, w->x, wall_L_bitmap, w->size & 31);
}

void render_right_wall(UINT8* base, Wall* w) {
	int i;
	for (i = 0; i < (w->size - 32); i += 32) {
		plot_8bit_bitmap(base, w->y + i, w->x, wall_R_bitmap, 32);
	}
	plot_8bit_bitmap(base, w->y + i, w->x, wall_R_bitmap, w->size & 31);	
}

void render_room(UINT32* base, Room* r) {
	int i;

	for (i = 0; i < r->floor_count; i++) {
		render_floor(base, &r->floors[i]);
		if (r->floors[i].x + r->floors[i].size & 31) {
			clear_region(base, r->floors[i].y, r->floors[i].x + r->floors[i].size, 4, ((r->floors[i].x + r->floors[i].size - 1) & ~31) + 32);
		}
	}

	for (i = 0; i < r->wall_count; i++) {
		if (r->walls[i].x > 320) {
			render_right_wall((UINT8*)base, &r->walls[i]);
		}
		else {
			render_left_wall((UINT8*)base, &r->walls[i]);
		}
	}

	for (i = 0; i < r->exit_count; i++) {
		render_exit(base, &r->exits[i]);
	}

	for (i = 0; i < r->trap_count; i++) {
		render_trap((UINT16*)base, &r->traps[i]);
	}
}

void render_timer(UINT8* base, Timer* t) {
	char timeString[5];
	if (t->display_value.min > 99) {
		timeString[0] = '9';
		timeString[1] = '9';
		timeString[2] = ':';
		timeString[3] = '9';
		timeString[4] = '9';
	}
	else {
		timeString[0] = '0' + t->display_value.min / 10;
		timeString[1] = '0' + t->display_value.min % 10;
		timeString[2] = ':';
		timeString[3] = '0' + t->display_value.sec / 10;
		timeString[4] = '0' + t->display_value.sec % 10;
	}

	plot_string(base, t->y, t->x, timeString);
}

void game_message(UINT8* base, char* message) {
	plot_string(base, 220, 300, message);
}