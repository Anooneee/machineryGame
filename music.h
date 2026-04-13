#ifndef MUSIC_H
#define MUSIC_H

#include "types.h"

typedef enum {
    C = 0,
    Cs,
    D,
    Ds,
    E,
    F,
    G,
    Gs,
    A,
    As,
    B
} Note;

extern const int notes[12][8];

extern const int melody[29][3];

void start_music();

void upd_music();


#endif