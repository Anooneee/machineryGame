#ifndef BITMAP_H
#define BITMAP_H

#include "types.h"

/* Bitmap library for objects in game */
extern const UINT8 mouse_bitmap[];
extern const UINT8 ball_bitmap[]; /* N/A */
extern const UINT8 wall_R_bitmap[];
extern const UINT8 wall_L_bitmap[];
extern const UINT16 player_bitmap[]; /* Static */
extern const UINT16 enemy_bitmap[]; /* Static */
extern const UINT16 trap_bitmap[];
extern const UINT32 floor_bitmap[];
extern const UINT32 weapon_bitmap_right[];
extern const UINT32 weapon_bitmap_left[];
extern const UINT32 background[];
extern UINT32 bg_weapon[];
extern const UINT32 test_bitmap_32[];
extern const UINT16 test_bitmap_16[];

#define BITMAP_HEIGHT 8

#endif