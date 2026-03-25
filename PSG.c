#include <osbind.h>


volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write = 0xFF8802;



void write_psg(int reg, UINT8 val){
    long old_ssp = Super(0);
    *PSG_reg_select = reg;
	*PSG_reg_write = val;
    Super(old_ssp);
}

UINT8 read_psg(int reg){
    UINT8 val = *reg;
    return val;
}

void set_tone(int channel, int tuning){
    UINT8 fine = (UINT8)(tuning & 0xFF);
    UINT8 course = (UINT8)((tuning >> 8) & 0x0F);
    if((channel & 0x1) != 0x1){
        if(tuning >= 0 && tuning <= 4095){
            write_psg(channel, fine);
            write_psg(channel + 1, fine >> 8);
        }
    }   
}


void set_volume(int channel, int volume){
    if(reg <= 10 && reg >= 8){
        if(volume <= 31 && volume >= 0){
            write_psg(channel, volume);
        }
    }
}

void enable_channel(int channel, int tone_on, int noise_on){
    UINT8 noise_channel_enable = 0x0;
    UINT8 tone_channel_enable = 0x0;
    
        if(tone_on < 8){
            tone_channel_enable |= tone_on;
        }
        if(noise_on < 8){
            noise_channel_enable |= noise_on;
            noise_channel_enable << 3;
        }
        tone_channel_enable |= noise_channel_enable;
    if(reg == 7){
    write_psg(channel, tone_channel_enable);
    }
}

void stop_sound(){
    write_psg(0x7, 0x0);
}