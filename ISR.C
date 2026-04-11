#include "ISR.h"
#define TRAP_28 28
#define TRAP_KB 70


int seconds;
typedef void (*Vector)();


static Vector Org_VBL;
static Vector Org_IKBD;


Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}

void install_vectors(){
    Org_VBL = install_vector(TRAP_28, do_vbl);
    Org_IKBD = install_vector(TRAP_KB, do_kbd);
}

void do_vbl(){

}

void do_kbd(){

}