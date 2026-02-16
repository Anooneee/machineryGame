#include <stdio.h>
#include <osbind.h>

#define BYTES_PER_SCREEN 32000

void disable_cursor();
void fill_screen(char *base, char pattern);

int main()
{
	char *base = Physbase();

	disable_cursor();          /* hide blinking text cursor */

	fill_screen(base, -1);     /* set screen to all black */
	Cnecin();                  /* wait for key press, don't echo */

	fill_screen(base, 1);      /* set screen to all white */
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
