#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "types.h"
#include "font.h"
#include "bitmap.h"

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

	Cnecin();
	clear_region(base, 100, 200, 50, 50);
	plot_pixel(base, 100, 200);
	plot_pixel(base, 150, 250);
	
	Cnecin();
	clear_screen(base);
	
	Cnecin();
	plot_pixel(base, 0, 0);
	Cnecin();
	plot_pixel(base, 0, 639);
	Cnecin();
	plot_pixel(base, 399, 639);
	Cnecin();
	plot_pixel(base, 399, 0);
	Cnecin();
	plot_pixel(base, 0, -1);
	Cnecin();
	plot_pixel(base, -1, 0);
	Cnecin();
	plot_pixel(base, 400, 0);
	Cnecin();
	plot_pixel(base, 0, 640);
	Cnecin();
	clear_screen(base);

	Cnecin();
	plot_horizontal_line(base, 200, 20, 5);
	Cnecin();
	plot_horizontal_line(base, 20, -10, 19);
	Cnecin();
	plot_horizontal_line(base, 150, 300, 400);
	Cnecin();
	plot_horizontal_line(base, -10, 20, 40);
	Cnecin();
	plot_horizontal_line(base, 410, 20, 40);
	Cnecin();
	clear_screen(base);
	
	Cnecin();
	plot_vertical_line(base, 0, 50, 50);
	Cnecin();
	plot_vertical_line(base, 250, 100, 200);
	Cnecin();
	plot_vertical_line(base, -10, 200, 40);
	Cnecin();
	plot_vertical_line(base, 0, -10, 40);
	Cnecin();
	plot_vertical_line(base, 0, 650, 40);
	Cnecin();
	clear_screen(base);

	Cnecin();
	plot_line(base, 0, 0, 399, 400);
	Cnecin();
	plot_line(base, 50, 20, 70, 200);
	Cnecin();
	plot_line(base, 70, 20, 50, 200);
	Cnecin();
	plot_line(base, 20, 0, 49, 50);

	Cnecin();
	plot_rectangle(base, 0, 0, 200, 40); 
	Cnecin();
	plot_rectangle(base, 40, 100, 20, 400);
	Cnecin();
	clear_screen(base); 

	plot_square(base, 40, 40, 50);
	Cnecin();
	plot_square(base, 200, 320, 100);
	Cnecin();
	clear_screen(base);



	plot_triangle(base, 200, 320, 50, 100, 0);
	Cnecin();
	plot_triangle(base, 200, 320, 50, 100, 1);
	Cnecin();
	plot_triangle(base, 200, 320, 50, 100, 2);
	Cnecin();
	plot_triangle(base, 200, 320, 50, 100, 3);
	Cnecin();
	plot_triangle(base, 200, 320, 100, 50, 0);
	Cnecin();
	plot_triangle(base, 200, 320, 100, 50, 1);
	Cnecin();
	plot_triangle(base, 200, 320, 100, 50, 2);
	Cnecin();
	plot_triangle(base, 200, 320, 100, 50, 3);
	Cnecin();
	clear_screen(base);

	plot_triangle(base, 40, 60, 80, 50, 0);
	plot_triangle(base, 370, 60, 80, 50, 3);
	plot_triangle(base, 200, 20, 80, 50, 0);
	plot_triangle(base, 200, 600, 80, 50, 1);
	Cnecin();
	
	/*plot_character(base, 0, 0, 'H');
	plot_8bit_bitmap(base, 0, 10,  8);
	Cnecin();*/

	plot_8bit_bitmap(base, -4, 0, wall_L_bitmap, 32);
	Cnecin();
	clear_screen(base); 
	plot_8bit_bitmap(base, 0, 0, wall_L_bitmap, 32);
	Cnecin();
	plot_8bit_bitmap(base, 32, -3, wall_L_bitmap, 32);
	Cnecin();
	plot_8bit_bitmap(base, 380, 0, wall_L_bitmap, 32);
	Cnecin();

	plot_16bit_bitmap(base, 0, 0, player_bitmap, 32);
	Cnecin();
	clear_screen(base);
	plot_16bit_bitmap(base, -12, 0, player_bitmap, 32);
	Cnecin();
	plot_16bit_bitmap(base, 380, 0, player_bitmap, 32);
	Cnecin();
	plot_16bit_bitmap(base, 200, 630, player_bitmap, 32);
	Cnecin();
	plot_16bit_bitmap(base, 200, -5, player_bitmap, 32);
	Cnecin();

	plot_32bit_bitmap(base, 0, 0, floor_bitmap, 4);
	Cnecin();
	plot_32bit_bitmap(base, 10, -20, floor_bitmap, 4);
	Cnecin();
	plot_32bit_bitmap(base, 398, 0, floor_bitmap, 4);
	Cnecin();
	plot_32bit_bitmap(base, -1, 50, floor_bitmap, 4);
	Cnecin();
	plot_32bit_bitmap(base, 0, 620, floor_bitmap, 4);
	Cnecin();
	
	clear_screen(base);
	Cnecin();
	plot_string(base, 0, 0, "Hello world!\n");
	clear_screen(base);
	Cnecin();
	plot_string(base, 0, 0, "Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world!");
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
