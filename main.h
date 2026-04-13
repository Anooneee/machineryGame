#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <osbind.h>

#include "model.h"
#include "events.h"
#include "render.h"
#include "raster.h" /* For getting vid base*/
#include "input.h"
#include "bitmap.h"
#include "mem.h"
#include "music.h"
#include "psg.h"
#include "Sfx.h"
#include "ISR.h"

extern int render_req;
extern int room_number;
extern int upd_timer;
extern int upd_model;


bool timer_ticked();

int main_menu();
int game();

#endif