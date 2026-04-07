#include "raster.h"
#include "types.h"
#include "font.c"
#include "bitmap.c"

#define SCREEN_WIDTH 639
#define SCREEN_HEIGHT 399

/*for all functions assume the co-ordinates follow x first y second sturcture regardless of weather it is row or col first*/


void clear_screen(UINT32 *base){
	int i;
	int screen_size = ((SCREEN_WIDTH+1)>>5) * (SCREEN_HEIGHT+1);

	for (i = 0; i < screen_size; i++) {
		base[i] = 0;
	}
}

void clear_region(UINT32 *base, int row, int col, UINT16 length, UINT16 width){
	/*variable declaration*/
	UINT32 start_mask, end_mask;
	int end_x;	/*start and end x co-ords for clear region*/
	int i, j, blocks, steps, start_block, end_block;
	
	/*set variables*/
	/*col is the start x co-ord*/

	start_block = col >> 5; /*specify the start LW block*/

	end_x = col + width - 1;	/*specify the end x co-ord*/
	if(end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;	/*end of line guard statement*/
	end_block = end_x >> 5;
	
	
	/*0xFFFFFFFF specifies mask to be manipulated to clear edge of region*/
	start_mask = 0xFFFFFFFF << (32 - (col & 31)); /*shift for left edge of region*/
	end_mask = 0xFFFFFFFF >> (end_x & 31);

	end_mask = 0xFFFFFFFF >> ((end_x & 31) + 1); /*shift for right edge of region*/
	
	base += (row << 4) + (row << 2) + start_block;
	
	if(start_block == end_block){ 	/*clear loop if region is less than 32bit wide*/
		for(i = 0; i < length; i++){  
			*base &= (start_mask | end_mask); 
			base += 20;
		}
	}else{
		/*main clearing loop*/
		blocks = end_block - start_block - 1; /*-2 gives number of LW's between start and end exclusive*/
		steps = 20 - (blocks + 1 );
		for(i = 0; i < length; i++){ /*y-portion of the loop*/
			*base &= start_mask;
			base++;
			for(j = 0; j < blocks; j++){	/*x-portion of the loop*/
				*base &= 0x00000000;	/*mask used to empty region*/
				base++;
			}
			if (end_block > start_block){
			*base &= end_mask;
			}
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
	int dx,dy,sx,sy,error,e2;
	dx =  start_col - end_col; 
    dy = end_row - start_row;
	if(dx < 0) dx = -dx; /*absolute of dx*/
	if(dy > 0) dy = -dy; /*absolute of -(dy)*/
	sx = start_col < end_col ? 1 : -1; /*determines moving direction for x*/
	sy = start_row < end_row ? 1 : -1; /*determines moving direction for y*/
    error = dx + dy; /*will decide between 2 pixels which one to step to*/

    while (1) {
        /* Clipping guard and Plotting */
        if (start_col >= 0 && start_col < SCREEN_WIDTH && start_row >= 0 && start_row < SCREEN_HEIGHT){
            base[(start_row << 4) + (start_row << 2) + (start_col >> 5)] |= (1UL << (31 - (start_col & 31)));
        }
		/*end of line trip. 1633 makes me hate use a break like this*/
        if (start_col == end_col && start_row == end_row) break; /*would be a JMP instruction out of the loop in Assembly*/

        e2 = 2 * error;
        if (e2 >= dy){ /* step x */  
            error += dy;
            start_col += sx;
        }
        if (e2 <= dx){ /* step y */
            error += dx;
            start_row += sy;
        }
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
	
	if (row > 399) return;
	height = (row + height > 399) ? 399 - row : height;
	
	base += (row << 6) + (row << 4) + (col >> 3);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			if(col >= 0){
			*base |= (bitmap[i] >> x_shift);
			}
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
	
	UINT16 x_shift = (col & 15);
	
	if (row > 399) return;
	height = (row + height > 399) ? 399 - row : height;
	
	base += (row << 5) + (row << 3) + (col >> 4);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			if(col >= -7){
			*base |= (bitmap[i] >> x_shift);
			}
			if ((col >> 4) < 39) {
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

	if (row > 399) return;
	height = (row + height > 399) ? 399 - row : height;
	
	base += (row << 4) + (row << 2) + (col >> 5);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			*base |= bitmap[i];
		}else{
			if(col >= 0){
			*base |= (bitmap[i] >> x_shift);
			}
			if ((col >> 5) < 19) {
			*(base + 1) |= (bitmap[i] << (32 - x_shift));
			}
		}
		base += 20; 
	}
}

void save_32bit(UINT32 *base, int row, int col, UINT32 *bitmap, UINT16 height){
	int i;

	UINT32 x_shift = (col & 31);
	if (row > 399) return;

	height = (row + height > 399) ? 399 - row : height;
	base += (row << 4) + (row << 2) + (col >> 5);

	for(i = 0; i < height; i++){
		if(x_shift == 0){
			bitmap[i] |= *base;
		}else {
			if(col >= 0){
				bitmap[i] |= (*base << x_shift) | (*(base+1) >> (32 - x_shift));
			}
		}
		base += 20;
	}
	return;
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
		if (*ch > 31) {
			plot_character(base, row, col, *ch);	/*plot char to screen, if it's an actual character*/
		}
		col += 8;								/*move start point to next row*/
		ch++;
		if(col >= SCREEN_WIDTH || *ch == '\n'){
			row += 8;
			col = 0;
		}
	}
}