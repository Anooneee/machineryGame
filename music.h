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

/* Music note list  */
extern const int notes[12][8];

/*Format: Note, octave, time
E1M1(At Dooms Gate)*/
extern const int melody[29][3];

void start_music();

void upd_music();


#endif