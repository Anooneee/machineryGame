#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "types.h"
#include "font.h"

/*Cnecin(); to pause between tests*/

#define BYTES_PER_SCREEN 32000

void disable_cursor();
void fill_screen(char *base, char pattern);

int main()
{
	char ch;
	int i, x, y;
	
	
	void *base = Physbase();

	disable_cursor();
	clear_screen(base);
	
	fill_screen(base, -1);
	clear_screen(base);

	Cnecin();
	clear_region(base, 0, 0, 100, 100);
	plot_pixel(base, 0, 0);
	plot_pixel(base, 99, 99);

	clear_region(base, 200, 100, 50, 50);
	plot_pixel(base, 200, 100);
	plot_pixel(base, 250, 150);
	
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

	plot_pixel(base, 20, 31);
	plot_pixel(base, 25, 31);

	Cnecin();
	plot_horizontal_line(base, 20, 30, 5);
	Cnecin();
	plot_horizontal_line(base, 0, 20, 9);
	Cnecin();
	plot_horizontal_line(base, 0, 200, 200);
	Cnecin();
	plot_horizontal_line(base, 10, 150, 400);
	
	plot_pixel(base, 49, 0);
	plot_pixel(base, 49, 50);

	Cnecin();
	plot_vertical_line(base, 50, 0, 50);
	Cnecin();
	plot_vertical_line(base, 51, 0, 50);
	Cnecin();
	plot_vertical_line(base, 0, 0, 40);
	Cnecin();
	plot_vertical_line(base, 200, 0, 40);
	
	Cnecin();
	clear_screen(base);

	Cnecin();
	plot_line(base, 0, 0, 400, 399);
	Cnecin();
	plot_line(base, 20, 50, 200, 70);
	Cnecin();
	plot_line(base, 20, 70, 200, 50);
	Cnecin();
	plot_line(base, 0, 20, 50, 49);

	Cnecin();
	plot_rectangle(base, 0, 0, 40, 200);
	Cnecin();
	plot_rectangle(base, 0, 40, 400, 20);
	
	Cnecin();
	clear_screen(base);

	plot_square(base, 40, 40, 50);
	Cnecin();
	plot_square(base, 320, 200, 100);

	Cnecin();
	clear_screen(base);

	Cnecin();
	plot_triangle(base, 320, 200, 100, 50, 0);
	Cnecin();
	plot_triangle(base, 320, 200, 100, 50, 1);
	Cnecin();
	plot_triangle(base, 320, 200, 100, 50, 2);
	Cnecin();
	plot_triangle(base, 320, 200, 100, 50, 3);
	Cnecin();
	plot_triangle(base, 320, 200, 50, 100, 0);
	Cnecin();
	plot_triangle(base, 320, 200, 50, 100, 1);
	Cnecin();
	plot_triangle(base, 320, 200, 50, 100, 2);
	Cnecin();
	plot_triangle(base, 320, 200, 50, 100, 3);
 
	Cnecin();
	clear_screen(base);

	plot_triangle(base, 500, 40, 150, 300, 3);
	Cnecin();
	clear_screen(base);
	
	x = 0;
	Cnecin();
	for(i = 0; i < 10; i++){
	plot_character(base, x, 0, 'H');
	plot_bitmap_8(base, x, 10, 8);
	Cnecin();
	x++;
	clear_screen(base);
	}
	Cnecin();
	plot_string(base, 0, 0, "Hello world!\n");
	clear_screen(base);
	Cnecin();
	plot_string(base, 0, 0, "Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world!\n");
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
