#ifndef ISR_H
#define ISR_H

typedef void (*Vector)();
void trap28();
Vector install_vector(int num, Vector vector);

void do_vbl();


#endif