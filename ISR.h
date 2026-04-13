#ifndef ISR_H
#define ISR_H

#include "music.h"
#include "game.h"
#include "types.h"
#include "raster.h"


void trap28();

void vbl_isr();

Vector install_vector(int num, Vector vector);

void disable_midi();

void enable_midi();

void install_vectors();

void uninstall_vectors();

void do_vbl();


#endif