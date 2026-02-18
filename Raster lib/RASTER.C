#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "types.h"
#include "font.c"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

/*for all functions assume the co-ordinates follow x first y second sturcture regardless of weather it is row or col first*/


/*void clear_screen(UINT32 *base){
	_clear_screen();
}*/

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col){
	if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT)
	*(base + (col << 6) + (col << 4) + (row >> 3)) |= 1 << 7 - (row & 7);
}

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){
	UINT32 start_mask, end_mask;
	UINT16 start_x, end_x;
	int i, blocks;
	
	start_x = row;
	end_x = row + length;
	if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;
	blocks = (end_x - start_x) >> 5;

	start_mask = 0xFFFFFFFF >> (start_x & 31);
	end_mask = 0xFFFFFFFF << (31 - (end_x & 31));
	
	base += ((col << 4)) + (row >> 5);
	if(length > 32){
		*base |= start_mask;
		base++;
	for(i = 0; i < blocks; i++){
		*base |= 0xFFFFFFFF;
		base++;
	}
	}else if(length > 16){ 
		*base |= start_mask;
		base++;
	}
	*base |= end_mask;

}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){
	int i;
	base += (col << 6) + (col << 4);
	base += (row >> 3);
	while(i < length){
		*(base) |= 1 << 7 - (row & 7);
		base += 256;
		i += 1;
	}
}

void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col){
	/*Bresenham's line algorithm as per wikipedia "https://en.wikipedia.org/wiki/Bresenham's_line_algorithm"*/
	int x_length,y_length,slope,x,y;
	x_length = end_row - start_row;
	y_length = end_col - start_col;
	slope = (y_length << 1) - x_length;
	y = start_col;
	base += (start_col << 6) + (start_col << 4) + (start_row >> 3);
	for(x=start_row; x < end_row; x++){
		*(base) |= 1 << 7 - (*base & 7);
		if(slope > 0){
			y = y + 1;
			slope = slope + ((y_length - x_length) << 1);
		}else slope = slope + (y_length << 1);
	}
}

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){
	plot_horizontal_line(base, row, col, width);
	plot_vertical_line(base, row, col, length);
	plot_vertical_line(base, row, col, length);
	plot_horizontal_line(base, row, col, length);
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side){
	plot_horizontal_line(base, row, col, side);
	plot_vertical_line(base, row, col, side);
	plot_vertical_line(base, row, col, side);
	plot_horizontal_line(base, row, col, side);
}

void plot_triangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 t_base, UINT16 height, UINT8 direction){
	
}

void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height){
	
}

void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height){

}

void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height){

}

void plot_character(UINT8 *base, UINT16 row, UINT16 col, char ch){
	int i;
	UINT8 *bit_map = GLYPH_START(ch);
	base += (col << 6) + (col << 4) + (row >> 3); /*start position of char on screen*/
	
	for(i = 0; i < 8; i++){
		*base |= *(bit_map);
		base += 80;
		bit_map++;
	}
}

void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *ch){
	while(*ch != '\n'){
		plot_character(base, row, col, *ch);	/*plot char to screen*/
		row += 8;								/*move start point to next row*/
		if(row >= SCREEN_WIDTH){
			col += 8;
			row = 0;
		}
		ch++;
	}
}