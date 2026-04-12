#ifndef ISR_H
#define ISR_H

#include "music.h"
#include "types.h"
#include "raster.h"
#include "main.h"

void trap28();
Vector install_vector(int num, Vector vector);

void install_vectors();
void uninstall_vectors();

void disable_midi();
void enable_midi();

void do_vbl();




#endif