#ifndef ISR_H
#define ISR_H
#include <stdio.h>
#include <osbind.h>
#include "music.h"
#include "game.h"
#include "types.h"
#include "raster.h"

typedef void (*Vector)(); /* a function start address with no parameters and no return value */

void trap28();

void trap28_isr();

void vbl_isr();

Vector install_vector(int num, Vector vector);

void disable_midi();

void enable_midi();

void install_vectors();

void uninstall_vectors();

void do_vbl();


#endif