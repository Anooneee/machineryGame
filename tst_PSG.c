#include <osbind.h>
#include <stdio.h>
#include "PSG.h"
#include "types.h"

#define WAIT_TIME 50

/*int main()
{  
    int i;
    long old_ssp = Super(0);

    set_tone(0, 1357);
    set_volume(0, 0, 10);   
    enable_channel(0, 1, 0);
    

for (i = 0; i < 4; i++) {
		wait(10);
		write_psg(1, 1);
		write_psg(0, 224);
		wait(10);
		write_psg(0, 175);
		wait(10);
		write_psg(0, 124);
		wait(10);
		write_psg(0, 104);
		wait(10);
		write_psg(0, 64);
		wait(10);
		write_psg(0, 28);
		wait(10);
		write_psg(1, 0);
		write_psg(0, 254);
		wait(10);
		write_psg(0, 240);
	}

    Cnecin();
    set_tone(0, 1357);
    set_volume(0, 0, 10);   
    enable_channel(0, 1, 0);
    wait(2);
   
    for(i = 0; i < 4; i++){
    set_tone(0, 339);
    wait(10);
    set_tone(0, 302);
    }
    
    Super(old_ssp);
}
*/
long *timer = (long*) 0x462;	/* TIMER!!! */

void wait(long time) {
	long now = *timer;
	while (now + time > *timer) {
	}
} /* this waits [time] ticks */

int main()
{
	long now;
	int i;

	long old_ssp = Super(0);


	set_tone(0, 250);		    /* set channel A fine tune = 248 */
	/* set channel A coarse tune = 0 */
	enable_channel(0, 1, 0);		/* enable channel A on mixer */
	set_volume(0, 0, 11);		    /* set channel A volume = 11 */

		/* Question 5: */

	wait(WAIT_TIME);

	set_tone(0, 250);
	set_volume(0, 0, 15);		/* fine pitch = 148, volume = 7 */


	wait(WAIT_TIME);


		/* Question 6: */

	set_volume(0, 0, 11);		/* volume back to 11 */


		
	for (i = 0; i < 4; i++) {
		wait(10);
		write_psg(1, 1);
		write_psg(0, 224);
		wait(10);
		write_psg(0, 175);
		wait(10);
		write_psg(0, 124);
		wait(10);
		write_psg(0, 104);
		wait(10);
		write_psg(0, 64);
		wait(10);
		write_psg(0, 28);
		wait(10);
		write_psg(1, 0);
		write_psg(0, 254);
		wait(10);
		write_psg(0, 240);
	}

		/* Question 8: */

	write_psg(7, 0x36);
	write_psg(6, 20);

	wait(WAIT_TIME);

	write_psg(7, 0x3E);

		/* Question 9: */

	write_psg(8, 0x10);

	write_psg(11, 0xF0);
	write_psg(12, 0x10);
	write_psg(13, 0x0E);

	wait(WAIT_TIME*6);

		/* Question 10: */

	write_psg(0, 224);
	write_psg(1, 1);	/* C note */
	write_psg(2, 124);
	write_psg(3, 1);	/* E note */
	write_psg(4, 64);
	write_psg(5, 1);	/* G note */

	write_psg(8, 11);
	write_psg(9, 11);
	write_psg(10, 11);	/* Turn on audio for all three channels */

	write_psg(7, 0x38);

	wait(WAIT_TIME * 2);

		/* Question 11: */

	write_psg(7, 0x37);

	write_psg(6, 15);
	write_psg(11, 0x01);
	write_psg(12, 0x20);
	write_psg(13, 0x08);

	write_psg(8, 0x10);	/* KABOOM!!!! */

	wait(WAIT_TIME);

	write_psg(8, 0);

	Super(old_ssp);
	return 0;
}