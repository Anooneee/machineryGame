#include <osbind.h>
#include <stdio.h>
#include "PSG.h"
#include "types.h"

int main()
{  
    
    set_tone(0, 1357);
    set_volume(0, 0, 10);   
    enable_channel(0, 1, 0);
    stop_sound();
    Cnecin();    
    set_tone(0, 679);
    set_volume(0, 0, 10);   
    enable_channel(0, 1, 0);
    Cnecin();
    stop_sound();
    
}
