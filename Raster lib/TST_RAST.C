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
	
	
	void *base = Physbase();

	disable_cursor();
	clear_screen(base);
	/*
	fill_screen(base, -1);
	
	Cnecin();
	clear_screen(base);
	
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
	
	Cnecin();
	plot_horizontal_line(base, 10, 0, 200);
	
	Cnecin();
	clear_screen(base);
	
	Cnecin();
	plot_vertical_line(base, 10, 10, 200);

	Cnecin();
	clear_screen();

	Cnecin();
	plot_line(base, 10, 10, 200, 200);
	
	Cnecin();
	clear_screen();*/
	
	/*	
	Cnecin();
	plot_character(base, 0, 0, 'c');
	Cnecin();
	clear_screen(base);
	/*
	Cnecin();
	plot_string(base, 0, 0, "Hello world!\n");
	clear_screen(base);
	*/
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
