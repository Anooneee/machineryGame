#include <osbind.h>
#define TRAP_28 112

int seconds;
typedef void (*Vector)();

Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}

void disable_midi() {
	long old_ssp = Super(0);
	*((volatile unsigned char*)0xFFFFFA09) &= ~(1 << 7);
	Super(old_ssp);
}

void enable_midi() {
	long old_ssp = Super(0);
	*((volatile unsigned char*)0xFFFFFA09) |= (1 << 7);
	Super(old_ssp);
}