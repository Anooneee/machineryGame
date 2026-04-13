#ifndef ISR_H
#define ISR_H

#include "music.h"
#include "main.h"

typedef void (*Vector)();
void trap28();
Vector install_vector(int num, Vector vector);

void disable_midi();
void enable_midi();

void do_vbl();

void upd_music();


#endif