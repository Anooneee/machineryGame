#ifndef PSG_H
#define PSG_H

#include "types.h"

void write_psg(int reg, UINT8 val);
/*Writes given byte value (0-255) to given PSG register (0-15)*/



UINT8 read_psg(int reg);
/*testing purposes*/

void set_tone(int channel, int tuning);
/*set the tone of each of the 3 channels, given the integer 
reg for start of the channel and the 12 bit tone value.
channel values = A = 0, B = 2, C = 4.
tuning values = 0 - 4095*/

void set_volume(int channel, int mode, int volume);
/*loads tone registers (course/fine) for the given channel 
(0=A, 1=B, 2=C) with given 12-bit tuning
volume = 0 - 31*/

void enable_channel(int channel, int tone_on, int noise_on);
/*loads the volume register for the given channel*/

void stop_sound();
/*silences all PSG sound production*/

void set_noise(int tuning);

void set_envelope(int shape, unsigned int sustain);

#endif