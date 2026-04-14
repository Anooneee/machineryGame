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

/* Start music */
void start_music();


/* Called every timer tick by vbl to:
- countdown the note time for current note
- go to next note
- cycle through song on repeat
- set tone on channel A
- ensure volume is on (8)*/
void upd_music();


#endif