#ifndef FONT_H
#define FONT_H

#include "types.h"

extern const UINT8 font[];     /* 8x8 system font */

/* Characteristics for the font table */
#define FONT_HEIGHT 8
#define CHAR_BEL    7
#define CHAR_TAB    9
#define CHAR_LF    10
#define CHAR_VT    11
#define CHAR_FF    12
#define CHAR_CR    13
#define CHAR_DEL  127

/* Used to check if the character is valid (location is within bonds of the font table)*/
#define IS_PRINTABLE(i) ((i) >= ' ' && (i) <= '~')
/* Used to identify location of a specific character */
#define GLYPH_START(i) (font + (((i) - ' ') << 3))

#endif
