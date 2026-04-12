#ifndef MAIN_H
#define MAIN_H

#include "model.h"
#include "events.h"
#include "render.h"
#include "input.h"
#include "bitmap.h"
#include "mem.h"
#include "music.h"
#include "psg.h"
#include "Sfx.h"
#include "ISR.h"

/*  Global Variables */
extern UINT32* base;
extern UINT32* back;
extern UINT32* temp;
extern UINT32* original;
extern Timer game_timer;

extern long *timer;
extern long current_time;
extern int render_req;
extern int note;
extern int render_rq;
extern int rdr_room_flag;
extern int vbl_ticks;
extern int rdr_timer_flag;
extern int rdr_sword_flag;
extern int clear_sword_flag;
extern int game_done;
extern int win_lose;
extern int next_rm;
extern int room_number;

extern Player* g_active_player;
extern Room* g_active_room;




/* Function Prototypes */
bool timer_ticked();

int main_menu();

int game();

void update_model();

int main();

#endif 