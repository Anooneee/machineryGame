#ifndef ISR_H
#define ISR_H

#include "music.h"
#include "main.h"
#include "types.h"
#include "raster.h"


void trap28();

Vector install_vector(int num, Vector vector);

void disable_midi();

void enable_midi();

void install_vectors();

void uninstall_vectors();

void do_vbl();


#endif