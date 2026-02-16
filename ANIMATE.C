#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#define SOLID 0xFFFF
#define XOR   2

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode);

int main()
{
	int x = 0;

	printf("\033E\033f\n");     /* blank the screen */
	linea0();

	while (!Cconis())     /* repeat until key press... */
	{
		plot_line(x, 0, x, 399, SOLID, XOR);  /* plot vert. line at x */
		/*Vsync();*/
		plot_line(x, 0, x, 399, SOLID, XOR);  /* unplot line at x */

		x++;				      /* move right */

		if (x == 640)
			x = 0;
	}

	Cnecin();
	return 0;
}

void plot_line(unsigned short x1, unsigned short y1,
               unsigned short x2, unsigned short y2,
               short style, short mode)
{
	/* do line-a call to plot a line */

	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = style;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}
