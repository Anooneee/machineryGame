#include "raster.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400




void plot_pixel(char *base, int x, int y)
{
if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
*(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
}


void plot_character(UINT8 *base, UINT16 row, UINT16 col, char ch){
	char *base = Physbase();
	char *font;
	char ch;
	int i;
	char byte;
	linea0();                    /* initialize line-a variables */
	font = (char *)V_FNT_AD;     /* get start address of font table */
	font += ch;
	for(i = 0; i < 16; i++){ 
		*(base + i * 80) |= *(font + i * 256);
	}
	return 0;
}