#include <osbind.h>
#include "types.h"


volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write = 0xFF8802;


void write_psg(int reg, UINT8 val){
    long old_ssp = Super(0);
    *PSG_reg_select = reg;
	*PSG_reg_write = val;
    Super(old_ssp);
}

UINT8 read_psg(int reg){
    UINT8 value;
    long old_ssp = Super(0);
    *PSG_reg_select = reg;
    value = *PSG_reg_write;
    Super(old_ssp);
    return value;
    
}

/*channel 0=A, 1=B, 2=C*/
void set_tone(int channel, int tuning){
    if(channel >= 0 && channel <= 2){
    UINT8 fine = (UINT8)(tuning & 0xFF);
    UINT8 course = (UINT8)((tuning >> 8) & 0x0F);
    channel = (channel << 1);
    write_psg(channel + 1, course);
    write_psg(channel, fine);
    }
}

/*channel 0=A, 1=B, 2=C*/
void set_volume(int channel, int mode, int volume){
    if(channel >= 0 && channel <= 2){
        if(mode == 0){
            if(volume >= 0 && volume <= 15){
                write_psg(channel + 8, (UINT8)volume);  
            }
        }else{
            write_psg(channel + 8, 0x10);
        }
    }
}

/*channel 0=A, 1=B, 2=C enable = 0, disable = 1*/
void enable_channel(int channel, int tone_on, int noise_on){
    UINT8 current_mixer = read_psg(7);
    UINT8 tone = (1 << channel);
    UINT8 noise = (1 << (channel + 3));
    
    if(tone_on) {
        current_mixer &= ~tone;
    }else {
        current_mixer |= tone;
    }
    if (noise_on) {
        current_mixer &= ~noise;
    } else {
        current_mixer |= noise;
    }
    
    write_psg(7, current_mixer);
    
}

void stop_sound(){
    enable_channel(0,0,0);
    enable_channel(1,0,0);
    enable_channel(2,0,0);

    set_volume(0, 0, 0);
    set_volume(1, 0, 0);
    set_volume(2, 0, 0);
}