#include <linea.h>
#include <osbind.h>
#include <stdio.h>


void blank_screen();

int main(){
	char *base = Physbase();
	char *font;
	char ch;
	int i;
	char byte;

	blank_screen();
	linea0();                    /* initialize line-a variables */
	font = (char *)V_FNT_AD;     /* get start address of font table */
	ch = Cnecin();

	/* TO DO: plot ch to upper left of screen directly */
	font += ch;
	
	for(i = 0; i < 16; i++){ 
		byte += (i * 256);
		*(base + i * 80) |= *(font + i * 256);
	
	}
	
	Cnecin();
	return 0;
}

void blank_screen()
{
	printf("\033E\033f\n");     /* VT52: clear screen, hide cursor */
}
