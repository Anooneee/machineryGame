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
	start_x = col;	/*set the start x co-ord*/
	start_block = start_x >> 5; /*specify the start LW block*/
	
	end_x = col + width;	/*specify the end x co-ord*/
	if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;	/*end of line guard statement*/
	end_block = end_x >> 5;
	
	
	full_mask = 0xFFFFFFFF;	/*specifies mask to be manipulated to clear edge of region*/
	clear_mask = 0x00000000;	/*mask used to empty region*/
	start_mask = full_mask << (32 - (start_x & 31)); /*shift for left edge of region*/
	end_mask = full_mask >> (end_x & 31) + 1; /*shift for right edge of region*/
	blocks = end_block - start_block - 2; /*-2 gives number of LW's between start and end exclusive*/
	steps = 18 - blocks;	/*specifies number of LW left in line*/
	
	base += (row << 4) + (row << 2) + (col >> 5);
	
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
	*(base + (row << 6) + (row << 4) + (col >> 3)) |= 1 << 7 - (col & 7);	/*plot individual pixel*/
}

void plot_horizontal_line(UINT32 *base, int row, int col, UINT16 length){
	/*variable declaration*/
	UINT32 start_mask, end_mask, full_block, start_block, end_block;
	
	int start_x, end_x;
	int i,num_blocks;

	if(col < SCREEN_WIDTH && row <= SCREEN_HEIGHT && row >= 0){ /*guard statement handles out of bounds pos*/
		end_x = col + length;	/*holds end of the line co-ords*/
		if(col < 0) col = 0;	/*handles left side clipping*/
	
		full_block = 0xFFFFFFFF;
		start_x = col;
		start_block = start_x >> 5;
	
		if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH; /*handles right side screen clipping*/
		end_block = end_x >> 5;	/*LW position offset*/

		base += ((row << 4) + (row << 2)) + (col >> 5);	/*set pos of base to start of line*/
	
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
	int i, end_y, abs_row;
	UINT32 mask_start, mask;


	if(row < SCREEN_HEIGHT && col >= 0 && col <= SCREEN_WIDTH){ /*guard statement, handels out of bounds clipping*/
		
		if(row + length > SCREEN_HEIGHT){  /*handles bottom screen clipping*/
			end_y = SCREEN_HEIGHT - col; /*ends line at bottome*/
		}else {	
			if(row < 0){ 
			abs_row = -row;	/*handles top screen clippin*/
			end_y = length - abs_row;	/*gets full length of the line*/
			row = 0;
			}else{
				end_y = length;
			}
				
		}

		/*set the bit mask for x pos in LW*/
		mask_start = 1;	
		mask = mask_start << (31 - (col & 31));
		
		base += (row << 4) + (row << 2) + (col >> 5); /*sets FB pointer to start of line*/
	
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
	
	x0 = start_col;
	x1 = end_col;
	y0 = start_row;
	y1 = end_row;

	/*delta of x and y*/
	dx = x1 - x0;
	dy = y1 - y0;
	
	/*sets the absolute values of dx & dy*/
	abs_dx = (dx < 0) ? -dx : dx;
	abs_dy = (dy < 0) ? -dy : dy;

	/*determines the intensity of line slope*/
	if(abs_dy < abs_dx){
		/*swaps point lables so line draws from left to right*/
		if(x0 > x1){
			x0 = end_col; x1 = start_col;
			y0 = end_row; y1 = start_row;
		}
		
		/*re-initialize delta x & y*/
		dx = x1 - x0;
		dy = y1 - y0;
		yi = (dy < 0) ? -1 : 1;
		if(dy < 0) dy = -dy;	/*determines +/- slope*/		
		
		/*initializes slope error for bresenham's algo*/	
		slope_error = ((2 * dy) - dx);
		y = y0; 				/*sets start point of line*/
	
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
			x0 = end_col; x1 = start_col;
			y0 = end_row; y1 = start_row;
		}
		
		/**/
		dx = x1 - x0;
		dy = y1 - y0;
		xi = (dx < 0) ? -1 : 1;
		/*determines +/- slope*/
		if(dx < 0) dx = -dx;
	}
		/*initializes slope with swapped x and y*/
		slope_error = ((2 * dx) - dy);
		x = x0;						/*sets start point of line*/

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

void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width){
	/*variable declaration*/
	int x, y, x_end, y_end;
	x = col; y = row;

	x_end = col + width;	/*find right edge of shape*/
	y_end = row + length;	/*find bottom edge of shape*/

	plot_horizontal_line(base, y, x, width);		/*plot top edge*/
	plot_vertical_line(base, y, x, length);			/*plot left edge*/
	plot_vertical_line(base, y, x_end, length);		/*plot right edge*/
	plot_horizontal_line(base, y_end, x, width);	/*plot bottom edge*/
}

void plot_square(UINT32 *base, int row, int col, UINT16 side){
	/*variable declaration*/
	int x_end = col + side;
	int y_end = row + side;
	plot_horizontal_line(base, row, col, side);	/*plot top edge*/
	plot_vertical_line(base, row, col, side);	/*plot left edge*/
	plot_vertical_line(base, row, x_end, side);		/*plot right edge*/
	plot_horizontal_line(base, y_end, col, side);	/*plot bottom edge*/
}

void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction){
	/*variable declaration*/
	int x_start, x_tip, y_start, y_tip;
	y_start = row;
	x_tip = col;

	/*handles drawing base line*/
	if(direction == 0 | direction == 2){ 	/*base drawn left*/
		x_start = col - triangle_base;
		plot_horizontal_line(base, row, x_start, triangle_base);
	}else{									/*base drawn right*/
		x_start = col + triangle_base - 1;
		plot_horizontal_line(base, row, col, triangle_base);
	}
	
	/*handles drawing height line*/
	if(direction == 0 | direction == 1){		/*height drawn up*/
		y_tip = row - height;
		plot_vertical_line(base, y_tip, col, height);
	}else{										/*base drawn down*/
		y_tip = row + height;
		plot_vertical_line(base, row, col, height);
	}
	/*draws line between the 2 unconnected ends of base and height lines*/
	plot_line(base, y_start, x_start, y_tip, x_tip);
}

void plot_8bit_bitmap(UINT8 *base, int row, int col, const UINT8 *bitmap, UINT16 height){
	/*variable declaration*/
	int i;
	
	UINT8 x_shift = (col & 7);
	UINT8 x_shift = (col & 7);
	clear_region(base, row, col, 8, height);
	
	
	base += (row << 6) + (row << 4) + (col >> 3);
	base += (row << 6) + (row << 4) + (col >> 3);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			if ((col >> 3) < 79) {
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
	
	base += (row << 5) + (row << 3) + (col >> 4);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base &= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			if ((col >> 3) < 39) {
			*(base + 1) |= (bitmap[i] << (16 - x_shift));
		}
	}
		base += 40; 
	}
}

void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height){
	/*variable declaration*/
	int i;
	
	UINT32 x_shift = (col & 31);
	
	base += (row << 4) + (row << 2) + (col >> 5);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base &= bitmap[i];
		}else{
			*base |= (bitmap[i] >> x_shift);
			if ((col >> 3) < 19) {
			*(base + 1) |= (bitmap[i] << (32 - x_shift));
		}
	}
		base += 20; 
	}
}

void plot_character(UINT8 *base, int row, int col, char ch){
	/*variable declaration*/
	int i;
	UINT8 x_shift = (col & 7);
	UINT8 *font_map = GLYPH_START(ch);
	base += (row << 6) + (row << 4) + (col >> 3);
	
	for(i = 0; i < 8; i++){
		if(x_shift == 0){
			*base = *font_map; /* Changed from &= to = or |= depending on desired transparency */
		}else{
			*base |= (*font_map >> x_shift);
			*(base + 1) |= (*font_map << (8 - x_shift));
		}
		base += 80;
		font_map++;
	}
}

void plot_string(UINT8 *base, int row, int col, char *ch){
	while(*ch != '\0'){
		plot_character(base, row, col, *ch);	/*plot char to screen*/
		col += 8;								/*move start point to next row*/
		if(col >= SCREEN_WIDTH){
			row += 8;
			col = 0;
		}
		ch++;
	}
}