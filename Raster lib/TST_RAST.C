#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "types.h"
/*Cnecin(); to pause between tests*/
#define BYTES_PER_SCREEN 32000

void disable_cursor();
void fill_screen(char *base, char pattern);

int main()
{
	void *base = Physbase();

	disable_cursor();
	fill_screen(base, -1);
	Cnecin();
	clear_screen(base);

	Cnecin();
	plot_pixel(base, 0, 0);
	Cnecin();
	plot_pixel(base, 639, 0);
	Cnecin();
	plot_pixel(base, 639, 399);
	Cnecin();
	plot_pixel(base, 0, 399);
	Cnecin();
	plot_pixel(base, 320, 200);
	Cnecin();
	plot_pixel(base, 320, 0);
	Cnecin();
	plot_pixel(base, 320, 399);
	Cnecin();
	plot_pixel(base, 0, 200);
	Cnecin();
	plot_pixel(base, 639, 200);

	clear_screen(base);

	plot_horizontal_line(base, 10, 0, 200);

	return 0;
}

void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
}

void fill_screen(char *base, char pattern)
{
	register int i = 0;
	register char *loc = base;

	while (i++ < BYTES_PER_SCREEN)
		*(loc++) = pattern;
}
