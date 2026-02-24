#include "raster.h"
#include "types.h"
#include "font.c"
#include "bitmap.c"

#define SCREEN_WIDTH 639
#define SCREEN_HEIGHT 399

/*for all functions assume the co-ordinates follow x first y second sturcture regardless of weather it is row or col first*/


/*void clear_screen(UINT32 *base){
	_clear_screen();
}*/

void clear_region(UINT32 *base, int row, int col, UINT16 length, UINT16 width){
	UINT32 start_mask, clear_mask, end_mask, full_mask, start_block, end_block, offset;
	int start_x, end_x;
	int i, j, blocks, steps;
	
	start_x = row;
	start_block = start_x >> 5;
	end_x = row + width;
	
	if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;
	end_block = end_x >> 5;
	
	
	full_mask = 0xFFFFFFFF;
	clear_mask = 0x00000000;
	start_mask = full_mask << (32 - (start_x & 31));
	end_mask = full_mask >> (end_x & 31) + 1;
	blocks = end_block - start_block - 2; /*-1 gives number of LW's between start and end exclusive*/
	steps = 18 - blocks;
	
	if(start_block == end_block){
		for(i = 0; i < length; i++){
		*base &= (start_mask & end_mask);
		base += 20;
		}
	}else
		base += (col << 4) + (col << 2) + (row >> 5);
	for(i = 0; i <= length; i++){
		*base &= start_mask;
		base++;
		for(j = 0; j <= blocks; j++){
			*base &= clear_mask;
			base++;
		}
		*base &= end_mask;
		base += steps;
	}


}

void plot_pixel(UINT8 *base, int row, int col){
	if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT)
	*(base + (col << 6) + (col << 4) + (row >> 3)) |= 1 << 7 - (row & 7);
}

void plot_horizontal_line(UINT32 *base, int row, int col, UINT16 length){
	/*variables*/
	UINT32 start_mask, end_mask, full_block, start_block, end_block;
	int start_x, end_x;
	int i,num_blocks;
	full_block = 0xFFFFFFFF;
	
	if (row < 0 || row > SCREEN_WIDTH || col < 0 || col > SCREEN_HEIGHT)
        return;

	start_x = row;
	start_block = start_x >> 5;
	end_x = row + length;
	if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;
	end_block = end_x >> 5;
	base += ((col << 4) + (col << 2)) + (row >> 5);
	
	start_mask = full_block >> (start_x & 31);
	end_mask = full_block << (31 - (end_x & 31));
	
	if(start_block == end_block){
		*base |= (start_mask & end_mask);
	}else{
		*base |= start_mask;
		base++;

		num_blocks = end_block - start_block - 1; /*-1 gives number of LW's between start and end exclusive*/
		for(i = 0; i < num_blocks; i++){
			*base |= full_block;
			base++;
		}
		*base |= end_mask;
	}
}

void plot_vertical_line(UINT32 *base, int row, int col, UINT16 length){
	/*variables*/
	int i, end_y;
	UINT32 mask_start, mask; 

	if (row < 0 || row > SCREEN_WIDTH || col < 0 || col > SCREEN_HEIGHT)
        return;

	/*set the bit mask for x pos in LW*/
	mask_start = 1;	
	mask = mask_start << (31 - (row & 31));
	base += (col << 4) + (col << 2) + (row >> 5);
	end_y = col + length;

	if(end_y > SCREEN_HEIGHT){ 
		end_y = SCREEN_HEIGHT;
	}else {
		end_y = SCREEN_HEIGHT - col;
	}
	/*drawing the line*/
	for(i = 0; i < end_y; i++){
		*base |= mask;
		base += 20;	
	}
}

void plot_line(UINT32 *base, int start_row, int start_col, int end_row, int end_col){
	/*Bresenham's line algorithm as per wikipedia "https://en.wikipedia.org/wiki/Bresenham's_line_algorithm"
	// and geeksforgeeks "https://www.geeksforgeeks.org/dsa/bresenhams-line-generation-algorithm/"*/
	/*variables*/
	int x,y,dx,dy,x0,y0,x1,y1,slope_error,xi,yi,abs_dx,abs_dy;
	UINT32 long_offset, mask_start;
	
	x0 = start_row;
	x1 = end_row;
	y0 = start_col;
	y1 = end_col;

	dx = x1 - x0;
	dy = y1 - y0;
	
	abs_dx = dx;
	abs_dy = dy;
	if(dx < 0) abs_dx = -dx;
	if(dy < 0) abs_dy = -dy;

	if(abs_dy < abs_dx){
		if(x0 > x1){
			x0 = end_row;
			x1 = start_row;
			y0 = end_col;
			y1 = start_col;
		}
		
		dx = x1 - x0;
		dy = y1 - y0;

		yi = 1;
		if(dy < 0){
			yi = -1;
			dy = -dy;
	}
		slope_error = ((2 * dy) - dx);
		y = y0;
	
	/*low*/
	for(x = x0; x <= x1; x++){
		mask_start = 1;
		long_offset = (y << 4) + (y << 2) + (x >> 5);
		if((0 <= y && y <= SCREEN_HEIGHT) && (0 <= x && x <= SCREEN_WIDTH)){
		base[long_offset] |= mask_start << (31 - (x & 31));
		}
		if(slope_error > 0){
			y = y + yi;
			slope_error +=  (2 * (dy - dx));
		}else
			slope_error += (2 * dy);
	}

	}else{
		if(y0 > y1){
			x0 = end_row;
			x1 = start_row;
			y0 = end_col;
			y1 = start_col;
		}
		
		dx = x1 - x0;
		dy = y1 - y0;
		xi = 1;
	if(dx < 0){
		xi = -1;
		dx = -dx;
	}
	slope_error = ((2 * dx) - dy);
	x = x0;

	for(y = y0; y <= y1; y++){
		mask_start = 1;
		long_offset = (y << 4) + (y << 2) + (x >> 5);
		if((0 <= y && y <= SCREEN_HEIGHT) && (0 <= x && x <= SCREEN_WIDTH)){
		base[long_offset] |= mask_start << (31 - (x & 31));
		}
		if(slope_error > 0){
			x += xi; 
			slope_error += (2 * (dx - dy));
		}else
		slope_error += (2 * dx);
	}
	}
	
}

void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width){
	int x, y, x_end, y_end;
	x = row; y = col;
	x_end = row + width;
	y_end = col + length;
	if(0 <= y && y <= SCREEN_HEIGHT) plot_horizontal_line(base, x, y, width);
	if(0 <= x && x <= SCREEN_WIDTH) plot_vertical_line(base, x, y, length);
	if(0 <= x && x <= SCREEN_WIDTH) plot_vertical_line(base, x_end, y, length);
	if(0 <= y && y <= SCREEN_HEIGHT) plot_horizontal_line(base, row, y_end, width);
}

void plot_square(UINT32 *base, int row, int col, UINT16 side){
	int x, y;
	x = row + side;
	y = col + side;
	plot_horizontal_line(base, row, col, side);
	plot_vertical_line(base, row, col, side);
	plot_vertical_line(base, x, col, side);
	plot_horizontal_line(base, row, y, side);
}

void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction){
	int x_base, x_height, y_base, y_height;
	y_base = col;
	x_height = row;

	/*handles drawing base line*/
	if(direction == 0 | direction == 2){
		x_base = row - triangle_base;
		if(x_base <= 0) x_base = 0;
		plot_horizontal_line(base, x_base, col, triangle_base);
	}else{
		x_base = row + triangle_base - 1;
		
		plot_horizontal_line(base, row, col, triangle_base);
	}
	
	/*handles drawing height line*/
	if(direction == 0 | direction == 1){
		y_height = col - height;
		if(y_height <= 0) y_height = 0;
		plot_vertical_line(base, row, y_height, height);
	}else{
		y_height = col + height;
		plot_vertical_line(base, row, col, height);
	}

	plot_line(base, x_base, y_base, x_height, y_height);
}

void plot_bitmap_8(UINT8 *base, int row, int col, UINT16 height){
	int i;
	
	UINT8 x_shift = (row & 7);
	
	base += (col << 6) + (col << 4) + (row >> 3);

	for(i = 0; i <= height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			*(base + 1) |= (bitmap[i] << (8 - x_shift));
		}
		base += 80; 
	}
}

void plot_bitmap_16(UINT16 *base, int row, int col, UINT16 height){
	int i;
	
	UINT16 x_shift = (row & 15);
	
	base += (col << 5) + (col << 3) + (row >> 4);

	for(i = 0; i <= height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			*(base + 1) |= (bitmap[i] << (16 - x_shift));
		}
		base += 40; 
	}
}

void plot_bitmap_32(UINT32 *base, int row, int col, UINT16 height){
	int i;
	
	UINT32 x_shift = (row & 31);
	
	base += (col << 4) + (col << 2) + (row >> 5);

	for(i = 0; i <= height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			*(base + 1) |= (bitmap[i] << (32 - x_shift));
		}
		base += 20; 
	}
}

void plot_character(UINT8 *base, int row, int col, char ch){
	int i;
	UINT8 x_shift = (row & 7);
	UINT8 *font_map = GLYPH_START(ch);
	base += (col << 6) + (col << 4) + (row >> 3);
	
	for(i = 0; i < 8; i++){
		if(x_shift == 0){
			*base |= *font_map;
		}else{
			*base |= (*font_map >> x_shift);
			*(base + 1) |= (*font_map << (8 - x_shift));
		}
		base += 80;
		font_map++;
	}
}

void plot_string(UINT8 *base, int row, int col, char *ch){
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