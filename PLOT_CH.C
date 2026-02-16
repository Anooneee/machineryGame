#include <linea.h>
#include <osbind.h>
#include <stdio.h>

void blank_screen();

int main()
{
	char *base = Physbase();
	char *font;
	char ch;

	blank_screen();
	linea0();                    /* initialize line-a variables */
	font = (char *)V_FNT_AD;     /* get start address of font table */
	ch = Cnecin();

	/* TO DO: plot ch to upper left of screen directly */

	Cnecin();
	return 0;
}

void blank_screen()
{
	printf("\033E\033f\n");     /* VT52: clear screen, hide cursor */
}
