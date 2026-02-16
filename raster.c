#include "raster.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400




void plot_pixel(char *base, int x, int y)
{
if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
*(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
/* ------ -----
x / 8 x % 8
*/
}