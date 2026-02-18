#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
/*Cnecin(); to pause between tests*/

void disable_cursor();
void fill_screen(char *base, char pattern);

int main()
{
	void *base = Physbase();

	disable_cursor();
	fill_screen(base, -1);
	Cnecin();

	clear_screen(base)

	Cnecin();

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
