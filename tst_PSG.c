#include <osbind.h>
#include <stdio.h>
#include "music.h"
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
	long old_ssp = Super(0);
	long now = *timer;
	while (now + time > *timer) {
	}
	Super(old_ssp);
} /* this waits [time] ticks */

int main()
{
	long now;
	int i,temp,note;
	note = 1;

	start_music();
	wait(21);
	
	for(i = 0; i < 29; i++){
		temp = upd_music(i);
        wait(temp);
		}
			
	return 0;
}