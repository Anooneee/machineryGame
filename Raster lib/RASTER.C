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
	/*variable declaration*/
	UINT32 start_mask, clear_mask, end_mask, full_mask, start_block, end_block, offset;
	int start_x, end_x;	/*start and end x co-ords for clear region*/
	int i, j, blocks, steps;
	
	/*set variables*/
	start_x = row;	/*set the start x co-ord*/
	start_block = start_x >> 5; /*specify the start LW block*/
	
	end_x = row + width;	/*specify the end x co-ord*/
	if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;	/*end of line guard statement*/
	end_block = end_x >> 5;
	
	
	full_mask = 0xFFFFFFFF;	/*specifies mask to be manipulated to clear edge of region*/
	clear_mask = 0x00000000;	/*mask used to empty region*/
	start_mask = full_mask << (32 - (start_x & 31)); /*shift for left edge of region*/
	end_mask = full_mask >> (end_x & 31) + 1; /*shift for right edge of region*/
	blocks = end_block - start_block - 2; /*-2 gives number of LW's between start and end exclusive*/
	steps = 18 - blocks;	/*specifies number of LW left in line*/
	
	base += (col << 4) + (col << 2) + (row >> 5);
	
	if(start_block == end_block){ 	/*clear loop if region is less than 32bit wide*/
		for(i = 0; i < length; i++){  
			*base &= (start_mask & end_mask); 
			base += 20;
		}
	}else{
		/*main clearing loop*/
		for(i = 0; i <= length; i++){ /*y-portion of the loop*/
			*base &= start_mask;
			base++;
			for(j = 0; j <= blocks; j++){	/*x-portion of the loop*/
				*base &= clear_mask;
				base++;
			}
			*base &= end_mask;
			base += steps;	/*advance to next line*/
		}

	}
}

void plot_pixel(UINT8 *base, int row, int col){
	if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT) /*guard statement*/
	*(base + (col << 6) + (col << 4) + (row >> 3)) |= 1 << 7 - (row & 7);	/*plot individual pixel*/
}

void plot_horizontal_line(UINT32 *base, int row, int col, UINT16 length){
	/*variable declaration*/
	UINT32 start_mask, end_mask, full_block, start_block, end_block;
	
	int start_x, end_x;
	int i,num_blocks;

	if(row < SCREEN_WIDTH && col <= SCREEN_HEIGHT && col >= 0){ /*guard statement handles out of bounds pos*/
		end_x = row + length;	/*holds end of the line co-ords*/
		if(row < 0) row = 0;	/*handles left side clipping*/
	
		full_block = 0xFFFFFFFF;
		start_x = row;
		start_block = start_x >> 5;
	
		if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH; /*handles right side screen clipping*/
		end_block = end_x >> 5;	/*LW position offset*/

		base += ((col << 4) + (col << 2)) + (row >> 5);	/*set pos of base to start of line*/
	
		start_mask = full_block >> (start_x & 31);	/*bitshift for start block*/
		end_mask = full_block << (31 - (end_x & 31)); /*bitshift for end block*/
	
		if(start_block == end_block){	/*handles line being < LW*/
			*base |= (start_mask & end_mask);
		}else{
			*base |= start_mask;	/*sets start mask in FB*/
			base++;
			num_blocks = end_block - start_block - 1; /*-1 gives number of LW's between start and end exclusive*/
			for(i = 0; i < num_blocks; i++){	/*main line loop*/
				*base |= full_block;
				base++;
			}
			*base |= end_mask;
		}
	}
}

void plot_vertical_line(UINT32 *base, int row, int col, UINT16 length){
	/*Variable declaration*/
	int i, end_y, abs_col;
	UINT32 mask_start, mask;


	if(col < SCREEN_HEIGHT && row >= 0 && row <= SCREEN_WIDTH){ /*guard statement, handels out of bounds clipping*/
		
		if(col + length > SCREEN_HEIGHT){  /*handles bottom screen clipping*/
			end_y = SCREEN_HEIGHT - col; /*ends line at bottome*/
		}else {	
			if(col < 0){ 
			abs_col = -col;	/*handles top screen clippin*/
			end_y = length - abs_col;	/*gets full length of the line*/
			col = 0;
			}else{
				end_y = length;
			}
				
		}

		/*set the bit mask for x pos in LW*/
		mask_start = 1;	
		mask = mask_start << (31 - (row & 31));
		
		base += (col << 4) + (col << 2) + (row >> 5); /*sets FB pointer to start of line*/
	
		/*drawing the line*/
			for(i = 0; i < end_y; i++){
				*base |= mask;
				base += 20;	
			}
		}
	}


void plot_line(UINT32 *base, int start_row, int start_col, int end_row, int end_col){
	/*Bresenham's line algorithm as per wikipedia "https://en.wikipedia.org/wiki/Bresenham's_line_algorithm"
	// and geeksforgeeks "https://www.geeksforgeeks.org/dsa/bresenhams-line-generation-algorithm/"*/
	
	/*variable declaration*/
	int x,y,dx,dy,x0,y0,x1,y1,slope_error,xi,yi,abs_dx,abs_dy;
	UINT32 long_offset, mask_start;
	
	x0 = start_row;
	x1 = end_row;
	y0 = start_col;
	y1 = end_col;

	/*delta of x and y*/
	dx = x1 - x0;
	dy = y1 - y0;
	
	/*sets the absolute values of dx & dy*/
	abs_dx = dx;
	abs_dy = dy;
	if(dx < 0) abs_dx = -dx;
	if(dy < 0) abs_dy = -dy;

	/*determines the intensity of line slope*/
	if(abs_dy < abs_dx){
		/*swaps point lables so line draws from left to right*/
		if(x0 > x1){
			x0 = end_row;
			x1 = start_row;
			y0 = end_col;
			y1 = start_col;
		}
		
		/*re-initialize delta x & y*/
		dx = x1 - x0;
		dy = y1 - y0;

		/*determines +/- slope*/
		yi = 1;
		if(dy < 0){
			yi = -1;
			dy = -dy;
	}
		/*initializes slope error for bresenham's algo*/	
		slope_error = ((2 * dy) - dx);
		y = y0; /*sets start point of line*/
	
	/*low slope line drawing*/
	for(x = x0; x <= x1; x++){
		mask_start = 1; /*initializes mask to be manipulated*/
		long_offset = (y << 4) + (y << 2) + (x >> 5);	/*determines offset of pixel in LW*/
		if((0 <= y && y <= SCREEN_HEIGHT) && (0 <= x && x <= SCREEN_WIDTH)){ /*clipping guard statement*/
		base[long_offset] |= mask_start << (31 - (x & 31));	/*draw the pixel*/
		}
		
		/*adjusts slop_error for next pos and determines next pixel pos*/
		if(slope_error > 0){	
			y += yi;
			slope_error +=  (2 * (dy - dx));
		}else
			slope_error += (2 * dy);
	}

	}else{	/*handles high slope*/
		/*swaps point lables so line draws from left to right*/
		if(y0 > y1){
			x0 = end_row;
			x1 = start_row;
			y0 = end_col;
			y1 = start_col;
		}
		
		/**/
		dx = x1 - x0;
		dy = y1 - y0;
		xi = 1;
		/*determines +/- slope*/
		if(dx < 0){
			xi = -1;
			dx = -dx;
	}
	/*initializes slope with swapped x and y*/
	slope_error = ((2 * dx) - dy);
	x = x0;	/*sets start point of line*/

	/*High slope line drawing*/
	for(y = y0; y <= y1; y++){
		mask_start = 1;	/*initializes mask to be manipulated*/
		long_offset = (y << 4) + (y << 2) + (x >> 5);	/*LW pixel offset*/
		if((0 <= y && y <= SCREEN_HEIGHT) && (0 <= x && x <= SCREEN_WIDTH)){ /*clipping guard statement*/
		base[long_offset] |= mask_start << (31 - (x & 31)); /*draw the pixel gronk*/
		}
		
		/*re-adjust slope_error for next pixel pos*/
		if(slope_error > 0){
			x += xi; 
			slope_error += (2 * (dx - dy));
		}else
		slope_error += (2 * dx);
	}
	}
	
}

void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width){
	/*variable declaration*/
	int x, y, x_end, y_end;
	x = row; y = col;

	x_end = row + width;	/*find right edge of shape*/
	y_end = col + length;	/*find bottom edge of shape*/

	plot_horizontal_line(base, x, y, width);		/*plot top edge*/
	plot_vertical_line(base, x, y, length);			/*plot left edge*/
	plot_vertical_line(base, x_end, y, length);		/*plot right edge*/
	plot_horizontal_line(base, row, y_end, width);	/*plot bottom edge*/
}

void plot_square(UINT32 *base, int row, int col, UINT16 side){
	/*variable declaration*/
	int x, y;
	x = row + side;
	y = col + side;
	plot_horizontal_line(base, row, col, side);	/*plot top edge*/
	plot_vertical_line(base, row, col, side);	/*plot left edge*/
	plot_vertical_line(base, x, col, side);		/*plot right edge*/
	plot_horizontal_line(base, row, y, side);	/*plot bottom edge*/
}

void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction){
	/*variable declaration*/
	int x_base, x_height, y_base, y_height;
	y_base = col;
	x_height = row;

	/*handles drawing base line*/
	if(direction == 0 | direction == 2){ 	/*base drawn left*/
		x_base = row - triangle_base;
		plot_horizontal_line(base, x_base, col, triangle_base);
	}else{									/*base drawn right*/
		x_base = row + triangle_base - 1;
		plot_horizontal_line(base, row, col, triangle_base);
	}
	
	/*handles drawing height line*/
	if(direction == 0 | direction == 1){		/*height drawn up*/
		y_height = col - height;
		plot_vertical_line(base, row, y_height, height);
	}else{										/*base drawn down*/
		y_height = col + height;
		plot_vertical_line(base, row, col, height);
	}
	/*draws line between the 2 unconnected ends of base and height lines*/
	plot_line(base, x_base, y_base, x_height, y_height);
}

void plot_8bit_bitmap(UINT8 *base, int row, int col, const UINT8 *bitmap, UINT16 height){
	/*variable declaration*/
	int i;
	
	UINT8 x_shift = (row & 7);
	clear_region(base, row, col, 8, height);
	
	base += (col << 6) + (col << 4) + (row >> 3);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			if ((row >> 3) < 79) {
			*(base + 1) |= (bitmap[i] << (8 - x_shift));
		}
	}
		base += 80; 
	}
}

void plot_16bit_bitmap(UINT16 *base, int row, int col, const UINT16 *bitmap, UINT16 height){
	/*variable declaration*/
	int i;
	
	UINT16 x_shift = (row & 15);
	clear_region(base, row, col, 16, height);
	
	base += (col << 5) + (col << 3) + (row >> 4);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base &= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			if ((row >> 3) < 39) {
			*(base + 1) |= (bitmap[i] << (16 - x_shift));
		}
	}
		base += 40; 
	}
}

void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height){
	/*variable declaration*/
	int i;
	
	UINT32 x_shift = (row & 31);
	
	base += (col << 4) + (col << 2) + (row >> 5);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base &= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			if ((row >> 3) < 19) {
			*(base + 1) |= (bitmap[i] << (32 - x_shift));
		}
	}
		base += 20; 
	}
}

void plot_character(UINT8 *base, int row, int col, char ch){
	/*variable declaration*/
	int i;
	UINT8 x_shift = (row & 7);
	UINT8 *font_map = GLYPH_START(ch);
	base += (col << 6) + (col << 4) + (row >> 3);
	
	for(i = 0; i < 8; i++){
		if(x_shift == 0){
			*base &= *font_map;
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