#include "RASTER.H"
#include "TYPES.H"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400


void clear_screen(UINT32 *base){

}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){
    
}

void plot_pixel(char *base, int x, int y){
if (row >= 0 && row < SCREEN_WIDTH && col >= 0 && col < SCREEN_HEIGHT)
*(base + col * 80 + (row >> 3)) |= 1 << 7 - (row & 7);
}

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){
	if (col >= 0 && col < SCREEN_WIDTH && row >= 0 && row < SCREEN_HEIGHT)
		
}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){

}

void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col){

}

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){

}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side){

}

void plot_triangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction){

}

void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height){

}

void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height){

}

void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height){

}

void plot_character(UINT8 *base, UINT16 row, UINT16 col, char ch){
	char *base = Physbase();
	char *font;
	char ch;
	int i;
	char byte;
	font = (char *)V_FNT_AD;     /* get start address of font table */
	font += ch;
	for(i = 0; i < 16; i++){ 
		*(base + i * 80) |= *(font + i * 256);
	}
	return 0;
}

void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *ch){

}