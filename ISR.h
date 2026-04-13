#ifndef ISR_H
#define ISR_H

#include "main.h"
#include "types.h"
#include "music.h"

void vbl_isr();

void trap28();

Vector install_vector(int num, Vector vector);

void disable_midi();
void enable_midi();

void do_vbl();

void upd_music();




#endif