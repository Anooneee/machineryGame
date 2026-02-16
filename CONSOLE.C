#include <linea.h>
#include <osbind.h>
#include <stdio.h>

void plot_curs(char *base, unsigned int r, unsigned int c, char fill);
void plot_char(char *base, char *font, unsigned char ch);
void scroll(char *base);

int main()
{
	char *base = Physbase();
	char *font;
	char ch;

	printf("\033E\033f\n");     /* blank the screen */
	linea0();
	font = (char *)V_FNT_AD;
	plot_curs(base, 0, 0, 0xFF);

	while ((ch = Cnecin()) != '\033')
		plot_char(base, font, ch);

	return 0;
}

void plot_curs(char *base, unsigned int r, unsigned int c, char fill)
{
	/* plots and unplots a text cursor */

	char *scrn_byte = base + c + r * 16 * 80;
	int i;

	for(i = 0; i < 16; i++)
	{
		*scrn_byte = fill;
		scrn_byte += 80;
	}
}

/* NOTE:

	- cursor doesn't blink
	- backspace over tab may not behave as expected
	- could add support for more control characters
	- could add support for some VT52 escape sequences
*/

void plot_char(char *base, char *font, unsigned char ch)
{
	static r = 0, c = 0;
	char *scrn_byte;
	char *font_byte;
	int i;

	if (ch == '\b' && c > 0)     /* backspace */
	{
		plot_curs(base, r, c, 0x00);
		c--;
		plot_curs(base, r, c, 0xFF);
	}
	else if (ch == '\r')     /* newline */
	{
		plot_curs(base, r, c, 0x00);
		r++;
		c = 0;
	}
	else if (ch == '\t')     /* tab */
	{
		plot_curs(base, r, c, 0x00);
		c += 8;
	}
	else if (ch > 31 && ch < 127)     /* printable char */
	{
		scrn_byte = base + c + r * 16 * 80;
		font_byte = font + ch;

		for(i = 0; i < 16; i++)
		{
			*scrn_byte = *font_byte;
			scrn_byte += 80;
			font_byte += 256;
		}

		c++;
	}

	if (c >= 80)     /* wrap to column 0 if necessary */
	{
		r++;
		c %= 80;
	}

	if (r == 25)     /* scroll screen if necessary */
	{
		scroll(base);
		r = 24;
	}

	plot_curs(base, r, c, 0xFF);
}

void scroll(char *base)
{
	/* scroll screen by copying text lines upwards */

	int i;
	long *l;

	for (i = 0, l = (long *)base; i < 7680; i++, l++)
		*l = *(l + 320);

	for (; i < 8000; i++, l++)
		*l = 0;
}
